#pragma once

#include "shaders/vertex.h"
#include "shaders/shader.h"

namespace gamo {
	class GameObjectBase;

	template<class T>
	class GameObject;

	class GameObjectComponent {
	protected:
		GameObjectBase* parentObject = nullptr;

	public:
		const std::string tag;

		GameObjectComponent(std::string tag = "") : tag(tag) {

		};
		virtual ~GameObjectComponent() {};

		inline virtual void onAttach(GameObjectBase* newParent) {};
		inline virtual void onUpdate(float elapsedSeconds) {};
		virtual void setParent(GameObjectBase* newParent) {
			parentObject = newParent;
			onAttach(parentObject);
		};
	};

	template<class T>
	class GameObjectDrawComponent : public GameObjectComponent {
	protected:
		GameObject<T>* parentObject = nullptr;

	public:
		inline virtual void onBuild(std::vector<T>& vertices) {};
		inline virtual void onDraw(Shader<T>* shader, const glm::mat4& transform) {};

		virtual void setParent(GameObjectBase* newParent) {
			parentObject = dynamic_cast<GameObject<T>*>(newParent);
			GameObjectComponent::setParent(newParent);
		};
	};
}