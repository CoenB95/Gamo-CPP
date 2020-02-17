#pragma once

#include "components/gameobjectcomponent.h"

namespace gamo {
	class SpinComponent : public GameObjectComponent {
	private:
		glm::vec3 radiansPerSec;

	public:
		SpinComponent(glm::vec3 degreesPerSec, std::string tag = "") : GameObjectComponent(tag) {
			radiansPerSec = glm::radians(degreesPerSec);
		};

		void onUpdate(float elapsedSeconds) {
			glm::quat rotationalDelta = glm::quat(radiansPerSec * elapsedSeconds);
			this->parentObject->orientation *= rotationalDelta;
		};
	};
}