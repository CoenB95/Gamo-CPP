#pragma once

#include "objects/gameobject.h"

namespace gamo {
	class GameObjectGroup : public GameObject {
	private:
		vector<GameObject*> children;
		mutex childrenMutex;

	public:
		GameObjectGroup();
		~GameObjectGroup();

		virtual void build(vector<Vertex>& vertices) override;
		virtual void draw(Shader* shader, const mat4& parentModelMatrix) override;
		virtual void update(float elapsedSeconds) override;

		void addChild(GameObject* object);
		void deleteAllChildren();
		void deleteChild(GameObject* object);
		void removeChild(GameObject* object);
	};
}