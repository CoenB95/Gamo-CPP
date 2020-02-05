#pragma once

#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <mutex>
#include <vector>

#include "shaders/vertex.h"
#include "shaders/shader.h"

namespace gamo {
	class GameObjectComponent;
	class GameObjectGroup;

	class GameObject {
	private:
		std::vector<GameObjectComponent*> components;
		std::mutex componentsMutex;
		bool dirty = true;

	public:
		GameObjectGroup* parent;

		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 pivot = glm::vec3(0, 0, 0);
		std::vector<Vertex> vertices;
		std::mutex verticesMutex;

		GameObject() { };
		virtual ~GameObject() {
			deleteAllComponents();
		};

		GameObject(GameObject& other) {
			position = other.position;
			orientation = other.orientation;
		};

		// Builds the object (called from worker thread)
		void build() {
			build(vertices);
		}

		virtual void build(std::vector<Vertex>& vertices) {
			dirty = false;

			std::vector<GameObjectComponent*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent* component : componentsCopy) {
				component->onBuild(vertices);
			}
		};

		// Draws the object
		virtual void draw(Shader* shader, const glm::mat4& transform = glm::mat4()) {
			if (components.empty()) {
				return;
			}

			std::vector<GameObjectComponent*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent* component : componentsCopy) {
				component->onDraw(shader, transform * Shader::compose(position, orientation, scale));
			}
		};

		// Updates the object 
		virtual void update(float elapsedSeconds) {
			if (components.empty()) {
				return;
			}

			//Iterate on a copy so that components can remove themselves.
			std::vector<GameObjectComponent*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent* component : componentsCopy) {
				component->onUpdate(elapsedSeconds);
			}
		};

		void addComponent(GameObjectComponent* component) {
			component->setParent(this);
			std::lock_guard<std::mutex> lock(componentsMutex);
			components.push_back(component);
		};
		
		glm::mat4 calcModelMatrix(const glm::mat4& parentModelMatrix = glm::mat4());
		void deleteAllComponents() {
			std::lock_guard<std::mutex> lock(componentsMutex);
			for (GameObjectComponent* component : components) {
				delete component;
			}
			components.clear();
		};

		void deleteComponent(GameObjectComponent* component) {
			if (component == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(componentsMutex);
			std::vector<GameObjectComponent*>::iterator it = find(components.begin(), components.end(), component);
			if (it != components.end()) {
				components.erase(it);
				delete component;
			}
		};

		GameObjectComponent* findComponentByTag(std::string tag) {
			if (tag.empty()) {
				return nullptr;
			}

			std::lock_guard<std::mutex> lock(componentsMutex);
			for (GameObjectComponent* component : components) {
				if (component->tag == tag) {
					return component;
				}
			}

			return nullptr;
		};

		glm::vec3 globalPosition() {
			return parent == nullptr ? position : parent->globalPosition() + position;
		};

		bool hasComponent(std::string tag) {
			return findComponentByTag(tag) != nullptr;
		};

		//Notifies that this object has become dirty and should be rebuild.
		void notifyDirty() {
			dirty = true;
			if (parent != nullptr) {
				parent->notifyDirty();
			}
		};

		void removeComponent(GameObjectComponent* component) {
			if (component == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(componentsMutex);
			std::vector<GameObjectComponent*>::iterator it = find(components.begin(), components.end(), component);
			if (it != components.end()) {
				components.erase(it);
				component->setParent(nullptr);
			}
		};

		inline bool shouldRebuild() {
			return dirty;
		};
	};
}