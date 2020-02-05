#include "gamescene.h"

namespace gamo {
	GameScene::GameScene() {

	}

	void GameScene::addObject(GameObject* object) {
		objects.push_back(object);
	}
}