#include "components/smoothcomponent.h"

SmoothComponent::SmoothComponent(float snappyness, bool rotate, bool scale, bool translate) :
        GameObjectComponent(),
        snappyness(snappyness) {
	this->translate = translate;
	this->rotate = rotate;
}

void SmoothComponent::onUpdate(float elapsedSeconds) {
    previousOrientation = parentObject->orientation;
    previousPosition = parentObject->position;
	previousScale = parentObject->scale;

    if (rotate) {
		parentObject->orientation = glm::slerp(previousOrientation, parentObject->orientation, snappyness);
	}

    if (scale) {
		parentObject->scale = glm::mix(previousScale, parentObject->scale, snappyness);
	}

	if (translate) {
		parentObject->position = glm::mix(previousPosition, parentObject->position, snappyness);
	}
}
