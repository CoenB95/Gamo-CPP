#pragma once

#include "components/gameobjectcomponent.h"

namespace gamo {
	class FollowComponent : public GameObjectComponent {
	private:
		GameObject* subject;
		
		const bool rotate;
		const bool scale;
		const bool translate;

	public:
		FollowComponent(GameObject* subject, bool translate = false, bool scale = false, bool rotate = false);
		
		void onUpdate(float elapsedSeconds) override;
	};
}
