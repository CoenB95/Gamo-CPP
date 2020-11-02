#pragma once

#include "components/gameobjectcomponent.h"
#include "objects/gameobject.h"

namespace gamo {
	class FollowComponent : public GameObjectComponent {
	private:
		GameObjectBase* subject;
		
		const bool rotate;
		const bool scale;
		const bool translate;

	public:
		FollowComponent(GameObjectBase* subject, bool translate = false, bool scale = false, bool rotate = false) :
				GameObjectComponent(),
				subject(subject),
				translate(translate),
				scale(scale),
				rotate(rotate) {
		};
		
		void onUpdate(float elapsedSeconds) override {
			if (rotate) {
				parentObject->orientation = subject->orientation;
			}

			if (scale) {
				parentObject->scale = subject->scale;
			}

			if (translate) {
				parentObject->position = subject->position;
			}
		};
	};
}
