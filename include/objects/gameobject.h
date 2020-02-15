#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <mutex>
#include <vector>

#include "components/gameobjectcomponent.h"
#include "shaders/vertex.h"
#include "shaders/shader.h"

namespace gamo {
	template<class T>
	class GameObject {
	private:
		std::vector<GameObject<T>*> children;
		std::mutex childrenMutex;
		std::vector<GameObjectComponent<T>*> components;
		std::mutex componentsMutex;
		bool dirty = true;

	public:
		const std::string tag;
		GameObject<T>* parent = nullptr;

		glm::vec3 position = glm::vec3();
		glm::quat orientation = glm::quat(glm::vec3(0, 0, 0));
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 pivot = glm::vec3(0, 0, 0);
		std::vector<T> vertices;
		std::mutex verticesMutex;

		GameObject(const std::string tag = "") : tag(tag) { };

		virtual ~GameObject() {
			deleteAllChildren();
			deleteAllComponents();
		};

		GameObject(GameObject& other) {
			position = other.position;
			orientation = other.orientation;
		};

		// Builds the object (called from worker thread)
		void build(bool standaloneChildren = false) {
			vertices.clear();
			build(vertices, standaloneChildren);
		}

		void build(std::vector<T>& vertices, bool standaloneChildren = false) {
			dirty = false;

			// Build self.
			std::vector<GameObjectComponent<T>*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent<T>* component : componentsCopy) {
				component->onBuild(vertices);
			}

			// Build children.
			std::vector<GameObject<T>*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObject<T>* child : childrenCopy) {
				if (child->shouldRebuild()) {
					if (standaloneChildren) {
						child->build();
					} else {
						child->build(vertices);
					}
				}
			}
		};

		// Draws the object
		virtual void draw(Shader<T>* shader, const glm::mat4& transform = glm::identity<glm::mat4>()) {
			// Draw self.
			std::vector<GameObjectComponent<T>*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent<T>* component : componentsCopy) {
				glm::mat4 composed = Shaders::compose(position, orientation, scale);
				component->onDraw(shader, transform * composed);
			}

			// Draw children.
			std::vector<GameObject<T>*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObject<T>* child : childrenCopy) {
				glm::mat4 composed = Shaders::compose(position, orientation, scale);
				child->draw(shader, transform * composed);
			}
		};

		// Updates the object 
		virtual void update(float elapsedSeconds) {
			// Update self. Iterate on a copy so that they can remove themselves.
			std::vector<GameObjectComponent<T>*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent<T>* component : componentsCopy) {
				component->onUpdate(elapsedSeconds);
			}

			// Update children. Iterate on a copy so that they can remove themselves.
			std::vector<GameObject<T>*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObject<T>* child : childrenCopy) {
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

		void addChildren(std::vector<GameObject*> objects) {
			std::lock_guard<std::mutex> lock(childrenMutex);
			for (GameObject* object : objects) {
				if (object == nullptr) {
					continue;
				}

				object->parent = this;
				children.push_back(object);
			}
		};

		void addComponent(GameObjectComponent<T>* component) {
			if (component == nullptr) {
				return;
			}

			component->setParent(this);
			std::lock_guard<std::mutex> lock(componentsMutex);
			components.push_back(component);
		};

		void addComponents(std::vector<GameObjectComponent<T>*> comps) {
			std::lock_guard<std::mutex> lock(componentsMutex);
			for (GameObjectComponent<T>* component : comps) {
				if (component == nullptr) {
					continue;
				}

				component->parent = this;
				children.push_back(component);
			}
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
			for (GameObjectComponent<T>* component : components) {
				delete component;
			}
			components.clear();
		};

		void deleteChild(GameObject<T>* object) {
			if (object == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			typename std::vector<GameObject<T>*>::iterator it = std::find(children.begin(), children.end(), object);
			if (it != children.end()) {
				children.erase(it);
				delete object;
			}
		};

		void deleteComponent(GameObjectComponent<T>* component) {
			if (component == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(componentsMutex);
			typename std::vector<GameObjectComponent<T>*>::iterator it = std::find(components.begin(), components.end(), component);
			if (it != components.end()) {
				components.erase(it);
				delete component;
			}
		};

		GameObjectComponent<T>* findComponentByTag(std::string tag) {
			if (tag.empty()) {
				return nullptr;
			}

			std::lock_guard<std::mutex> lock(componentsMutex);
			for (GameObjectComponent<T>* component : components) {
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

		void removeChild(GameObject<T>* object) {
			if (object == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			typename std::vector<GameObject<T>*>::iterator it = std::find(children.begin(), children.end(), object);
			if (it != children.end()) {
				children.erase(it);
			}
		};

		void removeComponent(GameObjectComponent<T>* component) {
			if (component == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(componentsMutex);
			typename std::vector<GameObjectComponent<T>*>::iterator it = std::find(components.begin(), components.end(), component);
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