#pragma once

#include "objects/gameobject.h"

namespace gamo {
	class GameObjectGroup : public GameObject {
	private:
		std::vector<GameObject*> children;
		std::mutex childrenMutex;

	public:
		GameObjectGroup() { };

		~GameObjectGroup() {
			deleteAllChildren();
		};

		virtual void build(std::vector<Vertex>& vertices) override {
			GameObject::build(vertices);

			if (children.empty()) {
				return;
			}

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

		virtual void draw(Shader* shader, const glm::mat4& transform) override {
			GameObject::draw(shader, transform);

			if (children.empty()) {
				return;
			}

			std::vector<GameObject*> childrenCopy;
			{
				std::lock_guard<std::mutex> lock(childrenMutex);
				childrenCopy = children;
			}
			for (GameObject* child : childrenCopy) {
				child->draw(shader, transform * Shader::compose(position, orientation, scale));
			}
		};

		virtual void update(float elapsedSeconds) override {
			GameObject::update(elapsedSeconds);

			if (children.empty()) {
				return;
			}

			//Iterate on a copy so that objects can remove themselves.
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

		void deleteAllChildren() {
			std::lock_guard<std::mutex> lock(childrenMutex);
			for (GameObject* child : children) {
				delete child;
			}
			children.clear();
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
	};
}