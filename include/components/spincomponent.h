#pragma once

#include "components/gameobjectcomponent.h"

namespace gamo {
	class SpinComponent : public GameObjectComponent {
	private:
		float degreesPerSec;
		float value;

	public:
		SpinComponent(float degreesPerSec, std::string tag = "");

		void onUpdate(float elapsedSeconds);
	};
}