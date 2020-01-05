#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "components/gameobjectcomponent.h"
#include "groups/gameobjectgroup.h"
#include "objects/gameobject.h"

using namespace std;

GameObject::GameObject() {
	
}

GameObject::~GameObject() {
	deleteAllComponents();
}

GameObject::GameObject(GameObject& other) {
	position = other.position;
	orientation = other.orientation;
}

void GameObject::addComponent(GameObjectComponent* component) {
	component->setParent(this);
	lock_guard<mutex> lock(componentsMutex);
	components.push_back(component);
}

void GameObject::build(vec3 offset) {
	dirty = false;

	vector<GameObjectComponent*> componentsCopy;
	{
		lock_guard<mutex> lock(componentsMutex);
		componentsCopy = components;
	}
	for (GameObjectComponent* component : componentsCopy) {
		component->onBuild(offset);
	}
}

void GameObject::buildEmbedded(vec3 offset) {
	build(offset + position);
}

void GameObject::buildStandalone(bool pivotAsCenter) {
	build(pivotAsCenter ? -pivot : vec3(0, 0, 0));
}

void GameObject::deleteAllComponents() {
	lock_guard<mutex> lock(componentsMutex);
	for (GameObjectComponent* component : components) {
		delete component;
	}
	components.clear();
}

void GameObject::deleteComponent(GameObjectComponent* component) {
	if (component == nullptr)
		return;

	lock_guard<mutex> lock(componentsMutex);
	vector<GameObjectComponent*>::iterator it = find(components.begin(), components.end(), component);
	if (it != components.end()) {
		components.erase(it);
		delete component;
	}
}

void GameObject::draw(Shader* shader, const mat4& transform) {
	if (components.empty())
		return;

	vector<GameObjectComponent*> componentsCopy;
	{
		lock_guard<mutex> lock(componentsMutex);
		componentsCopy = components;
	}
	for (GameObjectComponent* component : componentsCopy) {
		component->onDraw(shader, transform * Shader::compose(position, orientation, scale));
	}
}

GameObjectComponent* GameObject::findComponentByTag(string tag) {
	if (tag.empty())
		return nullptr;

	lock_guard<mutex> lock(componentsMutex);
	for (GameObjectComponent* component : components) {
		if (component->tag == tag)
			return component;
	}

	return nullptr;
}

vec3 GameObject::globalPosition() {
	return parent == nullptr ? position : parent->globalPosition() + position;
};

void GameObject::notifyDirty() {
	dirty = true;
	if (parent != nullptr)
		parent->notifyDirty();
};

void GameObject::removeComponent(GameObjectComponent* component) {
	if (component == nullptr)
		return;

	lock_guard<mutex> lock(componentsMutex);
	vector<GameObjectComponent*>::iterator it = find(components.begin(), components.end(), component);
	if (it != components.end()) {
		components.erase(it);
		component->setParent(nullptr);
	}
}

void GameObject::update(float elapsedSeconds) {
	if (components.empty())
		return;

	//Iterate on a copy so that components can remove themselves.
	vector<GameObjectComponent*> componentsCopy;
	{
		lock_guard<mutex> lock(componentsMutex);
		componentsCopy = components;
	}
	for (GameObjectComponent* component : componentsCopy) {
		component->onUpdate(elapsedSeconds);
	}
}
