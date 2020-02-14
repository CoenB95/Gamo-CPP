#pragma once

#include "components/gameobjectcomponent.h"

namespace gamo {
	template<class T>
	class SpinComponent : public GameObjectComponent<T> {
	private:
		glm::vec3 radiansPerSec;

	public:
		SpinComponent(glm::vec3 degreesPerSec, std::string tag = "") : GameObjectComponent<T>(tag) {
			radiansPerSec = glm::radians(degreesPerSec);
		};

		void onUpdate(float elapsedSeconds) {
			glm::quat rotationalDelta = glm::quat(radiansPerSec * elapsedSeconds);
			this->parentObject->orientation *= rotationalDelta;
		};
	};
}