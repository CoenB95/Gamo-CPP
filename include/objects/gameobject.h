#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <mutex>
#include <vector>

#include "components/gameobjectcomponent.h"
#include "shaders/vertex.h"
#include "shaders/shader.h"

namespace gamo {
	class GameObjectBase {
	protected:
		std::vector<GameObjectBase*> children;
		std::mutex childrenMutex;
		std::vector<GameObjectComponent*> components;
		std::mutex componentsMutex;
		bool dirty = true;

		GameObjectBase(const std::string tag = "") : tag(tag) { };

	public:
		const std::string tag;
		GameObjectBase* parent = nullptr;

		glm::vec3 position = glm::vec3();
		glm::quat orientation = glm::quat(glm::vec3(0, 0, 0));
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 pivot = glm::vec3(0, 0, 0);

		virtual ~GameObjectBase() {
			deleteAllChildren();
			deleteAllComponents();
		};

		GameObjectBase(GameObjectBase& other) {
			position = other.position;
			orientation = other.orientation;
		};

		// Builds the object and its children (called from worker thread).
		virtual void build(bool standaloneChildren = false) = 0;

		// Updates the object 
		void update(float elapsedSeconds) {
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
			std::vector<GameObjectBase*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObjectBase* child : childrenCopy) {
				child->update(elapsedSeconds);
			}
		};

		void addChild(GameObjectBase* object) {
			if (object == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			object->parent = this;
			children.push_back(object);
		};

		void addChildren(std::vector<GameObjectBase*> objects) {
			std::lock_guard<std::mutex> lock(childrenMutex);
			for (GameObjectBase* object : objects) {
				if (object == nullptr) {
					continue;
				}

				object->parent = this;
				children.push_back(object);
			}
		};

		void addComponent(GameObjectComponent* component) {
			if (component == nullptr) {
				return;
			}

			component->setParent(this);
			std::lock_guard<std::mutex> lock(componentsMutex);
			components.push_back(component);
		};

		void addComponents(std::vector<GameObjectComponent*> comps) {
			std::lock_guard<std::mutex> lock(componentsMutex);
			for (GameObjectComponent* component : comps) {
				if (component == nullptr) {
					continue;
				}

				component->setParent(this);
				components.push_back(component);
			}
		};

		void deleteAllChildren() {
			std::lock_guard<std::mutex> lock(childrenMutex);
			for (GameObjectBase* child : children) {
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

		void deleteChild(GameObjectBase* object) {
			if (object == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			typename std::vector<GameObjectBase*>::iterator it = std::find(children.begin(), children.end(), object);
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
			typename std::vector<GameObjectComponent*>::iterator it = std::find(components.begin(), components.end(), component);
			if (it != components.end()) {
				components.erase(it);
				delete component;
			}
		};

		GameObjectBase* findChildByTag(std::string tag) {
			if (tag.empty()) {
				return nullptr;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			for (GameObjectBase* child : children) {
				if (child->tag == tag) {
					return child;
				}
			}

			return nullptr;
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

		void removeChild(GameObjectBase* object) {
			if (object == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(childrenMutex);
			typename std::vector<GameObjectBase*>::iterator it = std::find(children.begin(), children.end(), object);
			if (it != children.end()) {
				children.erase(it);
			}
		};

		void removeComponent(GameObjectComponent* component) {
			if (component == nullptr) {
				return;
			}

			std::lock_guard<std::mutex> lock(componentsMutex);
			typename std::vector<GameObjectComponent*>::iterator it = std::find(components.begin(), components.end(), component);
			if (it != components.end()) {
				components.erase(it);
				component->setParent(nullptr);
			}
		};

		inline bool shouldRebuild() {
			if (dirty) {
				return true;
			}

			for (GameObjectBase* child : children) {
				if (child->shouldRebuild()) {
					return true;
				}
			}

			return false;
		};
	};

	template<class T>
	class GameObject : public GameObjectBase {
	public:
		std::vector<T> vertices;
		std::mutex verticesMutex;

		GameObject(const std::string tag = "") : GameObjectBase(tag) { };

		// Builds the object and its children (called from worker thread).
		void build(bool standaloneChildren = false) override {
			vertices.clear();
			build(vertices, standaloneChildren);
		};

		void build(std::vector<T>& vertices, bool standaloneChildren = false) {
			dirty = false;

			// Build self.
			std::vector<GameObjectComponent*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent* component : componentsCopy) {
				GameObjectDrawComponent<T>* drawComponent = dynamic_cast<GameObjectDrawComponent<T>*>(component);
				if (drawComponent != nullptr) {
					drawComponent->onBuild(vertices);
				}
			}

			// Build children.
			std::vector<GameObjectBase*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObjectBase* child : childrenCopy) {
				if (child->shouldRebuild()) {
					if (standaloneChildren) {
						child->build();
					} else {
						GameObject<T>* vertexChild = dynamic_cast<GameObject<T>*>(child);
						if (vertexChild != nullptr) {
							vertexChild->build(vertices);
						}
					}
				}
			}
		};

		// Draws the object and its children.
		void draw(Shader<T>* shader, const glm::mat4& transform = glm::identity<glm::mat4>()) {
			// Draw self.
			std::vector<GameObjectComponent*> componentsCopy;
			{
				std::lock_guard<std::mutex> lock(componentsMutex);
				componentsCopy = components;
			}
			for (GameObjectComponent* component : componentsCopy) {
				GameObjectDrawComponent<T>* drawComponent = dynamic_cast<GameObjectDrawComponent<T>*>(component);
				if (drawComponent != nullptr) {
					glm::mat4 composed = Shaders::compose(position, orientation, scale);
					drawComponent->onDraw(shader, transform * composed);
				}
			}

			// Draw children.
			std::vector<GameObjectBase*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObjectBase* child : childrenCopy) {
				GameObject<T>* vertexChild = dynamic_cast<GameObject<T>*>(child);
				if (vertexChild != nullptr) {
					glm::mat4 composed = Shaders::compose(position, orientation, scale);
					vertexChild->draw(shader, transform * composed);
				}
			}
		};
	};
}