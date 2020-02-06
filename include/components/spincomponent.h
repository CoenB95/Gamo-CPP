#pragma once

#include "components/gameobjectcomponent.h"

namespace gamo {
	template<class T>
	class SpinComponent : public GameObjectComponent<T> {
	private:
		float degreesPerSec;
		float value;

	public:
		SpinComponent(float degreesPerSec, std::string tag = "") : GameObjectComponent<T>(tag),
				degreesPerSec(degreesPerSec) {

		};

		void onUpdate(float elapsedSeconds) {
			glm::quat rotationalDelta = glm::quat(glm::vec3(0.0f, glm::radians(degreesPerSec * elapsedSeconds), 0.0f));
			parentObject->orientation *= rotationalDelta;
		};
	};
}