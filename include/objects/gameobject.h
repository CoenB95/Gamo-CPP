#pragma once

#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <mutex>
#include <vector>

#include "components/gameobjectcomponent.h"
#include "shaders/vertex.h"
#include "shaders/shader.h"

namespace gamo {
	class GameObject {
	private:
		std::vector<GameObject*> children;
		std::mutex childrenMutex;
		std::vector<GameObjectComponent*> components;
		std::mutex componentsMutex;
		bool dirty = true;

	public:
		GameObject* parent = nullptr;

		glm::vec3 position = glm::vec3();
		glm::quat orientation = glm::quat();
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 pivot = glm::vec3(0, 0, 0);
		std::vector<Vertex> vertices;
		std::mutex verticesMutex;

		GameObject() { };
		virtual ~GameObject() {
			deleteAllChildren();
			deleteAllComponents();
		};

		GameObject(GameObject& other) {
			position = other.position;
			orientation = other.orientation;
		};

		// Builds the object (called from worker thread)
		void build() {
			vertices.clear();
			build(vertices);
		}

		virtual void build(std::vector<Vertex>& vertices) {
			dirty = false;

			// Build self.
			std::vector<GameObjectComponent*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent* component : componentsCopy) {
				component->onBuild(vertices);
			}

			// Build children.
			std::vector<GameObject*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObject* child : childrenCopy) {
				if (child->shouldRebuild()) {
					child->build(vertices);
				}
			}
		};

		// Draws the object
		virtual void draw(Shader* shader, const glm::mat4& transform = glm::mat4()) {
			// Draw self.
			std::vector<GameObjectComponent*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent* component : componentsCopy) {
				component->onDraw(shader, transform * Shader::compose(position, orientation, scale));
			}

			// Draw children.
			std::vector<GameObject*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObject* child : childrenCopy) {
				child->draw(shader, transform * Shader::compose(position, orientation, scale));
			}
		};

		// Updates the object 
		virtual void update(float elapsedSeconds) {
			// Update self. Iterate on a copy so that they can remove themselves.
			std::vector<GameObjectComponent*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent* component : componentsCopy) {
				component->onUpdate(elapsedSeconds);
			}

			// Update children. Iterate on a copy so that they can remove themselves.
			std::vector<GameObject*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObject* child : childrenCopy) {
				child->update(elapsedSeconds);
			}
		};

		void addChild(GameObject* object) {
			if (object == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			object->parent = this;
			children.push_back(object);
		};

		void addComponent(GameObjectComponent* component) {
			component->setParent(this);
			std::lock_guard<std::mutex> lock(componentsMutex);
			components.push_back(component);
		};

		void deleteAllChildren() {
			std::lock_guard<std::mutex> lock(childrenMutex);
			for (GameObject* child : children) {
				delete child;
			}
			children.clear();
		};
		
		void deleteAllComponents() {
			std::lock_guard<std::mutex> lock(componentsMutex);
			for (GameObjectComponent* component : components) {
				delete component;
			}
			components.clear();
		};

		void deleteChild(GameObject* object) {
			if (object == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			std::vector<GameObject*>::iterator it = find(children.begin(), children.end(), object);
			if (it != children.end()) {
				children.erase(it);
				delete object;
			}
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

		// Notifies that this object has become dirty and should be rebuild.
		void notifyDirty() {
			dirty = true;
			if (parent != nullptr) {
				parent->notifyDirty();
			}
		};

		void removeChild(GameObject* object) {
			if (object == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			std::vector<GameObject*>::iterator it = find(children.begin(), children.end(), object);
			if (it != children.end()) {
				children.erase(it);
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