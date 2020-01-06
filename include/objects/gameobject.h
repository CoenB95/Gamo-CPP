#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <mutex>
#include <vector>

#include "shaders/vertex.h"
#include "shaders/shader.h"

using namespace glm;
using namespace std;

namespace gamo {
	class GameObjectComponent;
	class GameObjectGroup;

	class GameObject {
	private:
		vector<GameObjectComponent*> components;
		mutex componentsMutex;
		bool dirty = true;

	public:
		GameObjectGroup* parent;

		vec3 position;
		quat orientation;
		vec3 scale = vec3(1, 1, 1);
		vec3 pivot = vec3(0, 0, 0);
		vector<Vertex> vertices;
		mutex verticesMutex;

		GameObject();
		virtual ~GameObject();
		GameObject(GameObject& other);

		// Builds the object (called from worker thread)
		void build() { build(vertices); }
		virtual void build(vector<Vertex>& vertices);
		// Draws the object
		virtual void draw(Shader* shader, const mat4& transform = mat4());
		// Updates the object 
		virtual void update(float elapsedSeconds);

		void addComponent(GameObjectComponent* component);
		mat4 calcModelMatrix(const mat4& parentModelMatrix = mat4());
		void deleteAllComponents();
		void deleteComponent(GameObjectComponent* component);	
		GameObjectComponent* findComponentByTag(string tag);
		vec3 globalPosition();
		bool hasComponent(string tag) { return findComponentByTag(tag) != nullptr; };
		//Notifies that this object has become dirty and should be rebuild.
		void notifyDirty();
		void removeComponent(GameObjectComponent* component);
		inline bool shouldRebuild() { return dirty; };
	};
}