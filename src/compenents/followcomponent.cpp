#include "components/followcomponent.h"

namespace gamo {
	FollowComponent::FollowComponent(GameObject* subject, bool translate, bool scale, bool rotate) :
			GameObjectComponent(),
			subject(subject),
			translate(translate),
			scale(scale),
			rotate(rotate) {
	}

	void FollowComponent::onUpdate(float elapsedSeconds) {
		if (rotate) {
			parentObject->orientation = subject->orientation;
		}

		if (scale) {
			parentObject->scale = subject->scale;
		}

		if (translate) {
			parentObject->position = subject->position;
		}
	}
}