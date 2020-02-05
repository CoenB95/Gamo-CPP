#pragma once

#include "objects/gameobject.h"

namespace gamo {
	class GameObjectComponent {
	protected:
		GameObject* parentObject;

	public:
		const std::string tag;

		GameObjectComponent(std::string tag = "") : tag(tag) {

		};
		virtual ~GameObjectComponent() {};

		inline virtual void onAttach(GameObject* newParent) {};
		inline virtual void onBuild(std::vector<Vertex>& vertices) {};
		inline virtual void onDraw(Shader* shader, const glm::mat4& transform) {};
		inline virtual void onUpdate(float elapsedSeconds) {};
		void setParent(GameObject* newParent) {
			parentObject = newParent;
			onAttach(parentObject);
		};
	};
}