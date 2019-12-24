#pragma once

#include "components/gameobjectcomponent.h"
#include "groups/gameobjectgroup.h"

namespace gamo {
	class DespawnComponent : public GameObjectComponent {
	private:
		GameObjectGroup* parentGroup;
		float secondsLeft;

	public:
		DespawnComponent(GameObjectGroup* parentGroup, float timeInSeconds, string tag = "");

		void onUpdate(float elapsedSeconds);
	};
}