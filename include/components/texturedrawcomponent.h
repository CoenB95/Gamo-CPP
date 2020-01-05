#pragma once

#include "components/gameobjectcomponent.h"
#include "shaders/texture.h"

namespace gamo {
	class TextureDrawComponent : public GameObjectComponent {
	private:
		Texture* texture;

	public:
		TextureDrawComponent(const string& fileName);

		void onDraw(Shader* shader, const mat4& transform) override;
	};
}
