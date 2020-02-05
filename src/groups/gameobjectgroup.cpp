#include <algorithm>

#include "groups/gameobjectgroup.h"

namespace gamo {
	GameObjectGroup::GameObjectGroup() {

	}

	GameObjectGroup::~GameObjectGroup() {
		deleteAllChildren();
	}

	void GameObjectGroup::addChild(GameObject* object) {
		if (object == nullptr) {
			return;
		}

		std::lock_guard<std::mutex> lock(childrenMutex);
		object->parent = this;
		children.push_back(object);
	}

	void GameObjectGroup::build(std::vector<Vertex>& vertices) {
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
	}

	void GameObjectGroup::deleteAllChildren() {
		std::lock_guard<std::mutex> lock(childrenMutex);
		for (GameObject* child : children) {
			delete child;
		}
		children.clear();
	}

	void GameObjectGroup::deleteChild(GameObject* object) {
		if (object == nullptr) {
			return;
		}

		std::lock_guard<std::mutex> lock(childrenMutex);
		std::vector<GameObject*>::iterator it = find(children.begin(), children.end(), object);
		if (it != children.end()) {
			children.erase(it);
			delete object;
		}
	}

	void GameObjectGroup::draw(Shader* shader, const glm::mat4& transform) {
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
	}

	void GameObjectGroup::update(float elapsedSeconds) {
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
	}

	void GameObjectGroup::removeChild(GameObject* object) {
		if (object == nullptr) {
			return;
		}

		std::lock_guard<std::mutex> lock(childrenMutex);
		std::vector<GameObject*>::iterator it = find(children.begin(), children.end(), object);
		if (it != children.end()) {
			children.erase(it);
		}
	}
}