#pragma once

#include "gameobject.h"

namespace gamo {
	class GameScene {
	private:
		std::vector<GameObject*> objects;

	public:
		GameScene() { };
		void addObject(GameObject* object) {
			objects.push_back(object);
		};
	};
}