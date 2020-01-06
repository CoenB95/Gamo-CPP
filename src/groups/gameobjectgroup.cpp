#include <algorithm>

#include "groups/gameobjectgroup.h"

GameObjectGroup::GameObjectGroup() {

}

GameObjectGroup::~GameObjectGroup() {
	deleteAllChildren();
}

void GameObjectGroup::addChild(GameObject* object) {
	if (object == nullptr)
		return;

	lock_guard<mutex> lock(childrenMutex);
	object->parent = this;
	children.push_back(object);
}

void GameObjectGroup::build(vector<Vertex>& vertices) {
	GameObject::build(vertices);

	if (children.empty())
		return;

	vector<GameObject*> childrenCopy;
	{
		lock_guard<mutex> lock(childrenMutex);
		childrenCopy = children;
	}
	for (GameObject* child : childrenCopy) {
		if (child->shouldRebuild()) {
			child->build(vertices);
		}
	}
};

void GameObjectGroup::deleteAllChildren() {
	lock_guard<mutex> lock(childrenMutex);
	for (GameObject* child : children) {
		delete child;
	}
	children.clear();
}

void GameObjectGroup::deleteChild(GameObject* object) {
	if (object == nullptr)
		return;

	lock_guard<mutex> lock(childrenMutex);
	vector<GameObject*>::iterator it = find(children.begin(), children.end(), object);
	if (it != children.end()) {
		children.erase(it);
		delete object;
	}
}

void GameObjectGroup::draw(Shader* shader, const mat4& transform) {
	GameObject::draw(shader, transform);

	if (children.empty())
		return;

	vector<GameObject*> childrenCopy;
	{
		lock_guard<mutex> lock(childrenMutex);
		childrenCopy = children;
	}
	for (GameObject* child : childrenCopy) {
		child->draw(shader, transform * Shader::compose(position, orientation, scale));
	}
}

void GameObjectGroup::update(float elapsedSeconds) {
	GameObject::update(elapsedSeconds);

	if (children.empty())
		return;

	//Iterate on a copy so that objects can remove themselves.
	vector<GameObject*> childrenCopy;
	{
		lock_guard<mutex> lock(childrenMutex);
		childrenCopy = children;
	}
	for (GameObject* child : childrenCopy) {
		child->update(elapsedSeconds);
	}
}

void GameObjectGroup::removeChild(GameObject* object) {
	if (object == nullptr)
		return;

	lock_guard<mutex> lock(childrenMutex);
	vector<GameObject*>::iterator it = find(children.begin(), children.end(), object);
	if (it != children.end())
		children.erase(it);
}