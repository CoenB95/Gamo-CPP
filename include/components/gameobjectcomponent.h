#pragma once

#include "objects/gameobject.h"

namespace gamo {
	class GameObjectComponent {
	protected:
		GameObject* parentObject;

	public:
		const string tag;

		GameObjectComponent(string tag = "");
		virtual ~GameObjectComponent() {};

		inline virtual void onAttach(GameObject* newParent) {};
		inline virtual void onBuild(vec3 offset) {};
		inline virtual void onDraw() {};
		inline virtual void onUpdate(float elapsedSeconds) {};
		void setParent(GameObject* object);
	};
}