#pragma once

#include "objects/gameobject.h"

namespace gamo {
	class GameObjectGroup : public GameObject {
	private:
		std::vector<GameObject*> children;
		std::mutex childrenMutex;

	public:
		GameObjectGroup();
		~GameObjectGroup();

		virtual void build(std::vector<Vertex>& vertices) override;
		virtual void draw(Shader* shader, const glm::mat4& parentModelMatrix) override;
		virtual void update(float elapsedSeconds) override;

		void addChild(GameObject* object);
		void deleteAllChildren();
		void deleteChild(GameObject* object);
		void removeChild(GameObject* object);
	};
}