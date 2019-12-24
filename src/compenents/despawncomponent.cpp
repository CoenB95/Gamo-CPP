#include "components/despawncomponent.h"

DespawnComponent::DespawnComponent(GameObjectGroup* parentGroup, float timeInSeconds, string tag) : GameObjectComponent(tag) {
	this->parentGroup = parentGroup;
	this->secondsLeft = timeInSeconds;
}

void DespawnComponent::onUpdate(float elapsedSeconds) {
	secondsLeft -= elapsedSeconds;
	if (secondsLeft <= 0 && parentGroup != nullptr) {
			parentGroup->deleteChild(parentObject);
	}
}