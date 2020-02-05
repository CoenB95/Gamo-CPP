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

		GameObject();
		virtual ~GameObject();
		GameObject(GameObject& other);

		// Builds the object (called from worker thread)
		void build() { build(vertices); }
		virtual void build(std::vector<Vertex>& vertices);
		// Draws the object
		virtual void draw(Shader* shader, const glm::mat4& transform = glm::mat4());
		// Updates the object 
		virtual void update(float elapsedSeconds);

		void addComponent(GameObjectComponent* component);
		glm::mat4 calcModelMatrix(const glm::mat4& parentModelMatrix = glm::mat4());
		void deleteAllComponents();
		void deleteComponent(GameObjectComponent* component);	
		GameObjectComponent* findComponentByTag(std::string tag);
		glm::vec3 globalPosition();
		bool hasComponent(std::string tag) { return findComponentByTag(tag) != nullptr; };
		//Notifies that this object has become dirty and should be rebuild.
		void notifyDirty();
		void removeComponent(GameObjectComponent* component);
		inline bool shouldRebuild() { return dirty; };
	};
}