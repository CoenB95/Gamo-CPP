#pragma once

#include "components/gameobjectcomponent.h"

namespace gamo {
	template<class T>
	class DespawnComponent : public GameObjectComponent<T> {
	private:
		GameObject<T>* parentGroup;
		float secondsLeft;

	public:
		DespawnComponent(GameObject<T>* parentGroup, float timeInSeconds, std::string tag = "") : GameObjectComponent<T>(tag) {
			this->parentGroup = parentGroup;
			this->secondsLeft = timeInSeconds;
		};

		void onUpdate(float elapsedSeconds) {
			secondsLeft -= elapsedSeconds;
			if (secondsLeft <= 0 && parentGroup != nullptr) {
				parentGroup->deleteChild(parentObject);
			}
		};
	};
}