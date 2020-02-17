#pragma once

#include "components/gameobjectcomponent.h"
#include "shaders/texture.h"

namespace gamo {
	class ColorDrawComponent : public GameObjectDrawComponent<VertexP3N3C4> {
	public:
		void onDraw(Shader<VertexP3N3C4>* shader, const glm::mat4& transform) override;
	};

	class TextureDrawComponent : public GameObjectDrawComponent<VertexP3N3T2> {
	private:
		Texture* texture;

	public:
		TextureDrawComponent(const std::string& fileName, bool filterNearest = true , bool repeatTexture = false);

		void onDraw(Shader<VertexP3N3T2>* shader, const glm::mat4& transform) override;
	};
}
