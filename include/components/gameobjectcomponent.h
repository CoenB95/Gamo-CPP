#pragma once

#include "shaders/vertex.h"
#include "shaders/shader.h"

namespace gamo {
	template<class T>
	class GameObject;

	template<class T>
	class GameObjectComponent {
	protected:
		GameObject<T>* parentObject = nullptr;

	public:
		const std::string tag;

		GameObjectComponent(std::string tag = "") : tag(tag) {

		};
		virtual ~GameObjectComponent() {};

		inline virtual void onAttach(GameObject<T>* newParent) {};
		inline virtual void onBuild(std::vector<T>& vertices) {};
		inline virtual void onDraw(Shader<T>* shader, const glm::mat4& transform) {};
		inline virtual void onUpdate(float elapsedSeconds) {};
		void setParent(GameObject<T>* newParent) {
			parentObject = newParent;
			onAttach(parentObject);
		};
	};
}