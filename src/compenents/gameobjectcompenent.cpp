#include "components/gameobjectcomponent.h"

namespace gamo {
	GameObjectComponent::GameObjectComponent(std::string tag) : tag(tag) {

	}

	void GameObjectComponent::setParent(GameObject* newParent) {
		parentObject = newParent;
		onAttach(parentObject);
	}
}


