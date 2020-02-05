#include <glm/glm.hpp>

#include "components/spincomponent.h"

namespace gamo {
	SpinComponent::SpinComponent(float degreesPerSec, std::string tag) : GameObjectComponent(tag),
			degreesPerSec(degreesPerSec) {

	}

	void SpinComponent::onUpdate(float elapsedSeconds) {
		glm::quat rotationalDelta = glm::quat(glm::vec3(0.0f, glm::radians(degreesPerSec * elapsedSeconds), 0.0f));
		parentObject->orientation *= rotationalDelta;
	}
}