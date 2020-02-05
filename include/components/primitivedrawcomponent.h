#pragma once

#include "components/gameobjectcomponent.h"
#include "shaders/texture.h"

namespace gamo {
	class ColorDrawComponent : public GameObjectComponent {
	public:
		void onDraw(Shader* shader, const glm::mat4& transform) override;
	};

	class TextureDrawComponent : public GameObjectComponent {
	private:
		Texture* texture;

	public:
		TextureDrawComponent(const std::string& fileName);

		void onDraw(Shader* shader, const glm::mat4& transform) override;
	};
}
