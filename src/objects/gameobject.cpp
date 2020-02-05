#include <algorithm>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "components/gameobjectcomponent.h"
#include "groups/gameobjectgroup.h"
#include "objects/gameobject.h"

namespace gamo {
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
		std::lock_guard<std::mutex> lock(componentsMutex);
		components.push_back(component);
	}

	void GameObject::build(std::vector<Vertex>& vertices) {
		dirty = false;

		std::vector<GameObjectComponent*> componentsCopy;
		{
			std::lock_guard<std::mutex> lock(componentsMutex);
			componentsCopy = components;
		}
		for (GameObjectComponent* component : componentsCopy) {
			component->onBuild(vertices);
		}
	}

/*void GameObject::buildEmbedded(vec3 offset) {
	build(offset + position);
}

void GameObject::buildStandalone(bool pivotAsCenter) {
	build(pivotAsCenter ? -pivot : vec3(0, 0, 0));
}*/

	void GameObject::deleteAllComponents() {
		std::lock_guard<std::mutex> lock(componentsMutex);
		for (GameObjectComponent* component : components) {
			delete component;
		}
		components.clear();
	}

	void GameObject::deleteComponent(GameObjectComponent* component) {
		if (component == nullptr) {
			return;
		}

		std::lock_guard<std::mutex> lock(componentsMutex);
		std::vector<GameObjectComponent*>::iterator it = find(components.begin(), components.end(), component);
		if (it != components.end()) {
			components.erase(it);
			delete component;
		}
	}

	void GameObject::draw(Shader* shader, const glm::mat4& transform) {
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
	}

	GameObjectComponent* GameObject::findComponentByTag(std::string tag) {
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
	}

	glm::vec3 GameObject::globalPosition() {
		return parent == nullptr ? position : parent->globalPosition() + position;
	}

	void GameObject::notifyDirty() {
		dirty = true;
		if (parent != nullptr) {
			parent->notifyDirty();
		}
	}

	void GameObject::removeComponent(GameObjectComponent* component) {
		if (component == nullptr) {
			return;
		}

		std::lock_guard<std::mutex> lock(componentsMutex);
		std::vector<GameObjectComponent*>::iterator it = find(components.begin(), components.end(), component);
		if (it != components.end()) {
			components.erase(it);
			component->setParent(nullptr);
		}
	}

	void GameObject::update(float elapsedSeconds) {
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
	}
}