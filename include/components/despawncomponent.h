#pragma once

#include "components/gameobjectcomponent.h"
#include "groups/gameobjectgroup.h"

namespace gamo {
	class DespawnComponent : public GameObjectComponent {
	private:
		GameObjectGroup* parentGroup;
		float secondsLeft;

	public:
		DespawnComponent(GameObjectGroup* parentGroup, float timeInSeconds, std::string tag = "") : GameObjectComponent(tag) {
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