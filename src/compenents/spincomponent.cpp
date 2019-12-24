#include <glm/glm.hpp>

#include "components/spincomponent.h"

SpinComponent::SpinComponent(float degreesPerSec, string tag) : GameObjectComponent(tag),
degreesPerSec(degreesPerSec) {

}

void SpinComponent::onUpdate(float elapsedSeconds) {
	quat rotationalDelta = quat(vec3(0.0f, glm::radians(degreesPerSec * elapsedSeconds), 0.0f));
	parentObject->orientation *= rotationalDelta;
}