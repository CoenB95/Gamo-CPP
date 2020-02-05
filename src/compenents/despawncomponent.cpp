#include "components/despawncomponent.h"

namespace gamo {
	DespawnComponent::DespawnComponent(GameObjectGroup* parentGroup, float timeInSeconds, std::string tag) : GameObjectComponent(tag) {
		this->parentGroup = parentGroup;
		this->secondsLeft = timeInSeconds;
	}

	void DespawnComponent::onUpdate(float elapsedSeconds) {
		secondsLeft -= elapsedSeconds;
		if (secondsLeft <= 0 && parentGroup != nullptr) {
			parentGroup->deleteChild(parentObject);
		}
	}
}