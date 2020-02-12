#pragma once

#include "components/gameobjectcomponent.h"
#include "shaders/texture.h"

namespace gamo {
	class ColorDrawComponent : public GameObjectComponent<VertexP3C4> {
	public:
		void onDraw(Shader<VertexP3C4>* shader, const glm::mat4& transform) override;
	};

	class TextureDrawComponent : public GameObjectComponent<VertexP3N3T2> {
	private:
		Texture* texture;

	public:
		TextureDrawComponent(const std::string& fileName);

		void onDraw(Shader<VertexP3N3T2>* shader, const glm::mat4& transform) override;
	};
}
