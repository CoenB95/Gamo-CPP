#pragma once

#include "components/gameobjectcomponent.h"
#include "shaders/texture.h"

namespace gamo {
	class ColorDrawComponent : public GameObjectComponent<VertexP3C4> {
	public:
		void onDraw(Shader<VertexP3C4>* shader, const glm::mat4& transform) override {
			std::lock_guard<std::mutex> lock(parentObject->verticesMutex);

			if (parentObject->vertices.size() <= 0) {
				return;
			}
			
			shader->draw(parentObject->vertices, transform, DrawMode::TRIANGLES);
		};
	};

	class TextureDrawComponent : public GameObjectComponent<VertexP3N3T2> {
	private:
		Texture* texture;

	public:
		TextureDrawComponent(const std::string& fileName) : GameObjectComponent() {
			texture = Texture::loadCached(fileName, true);
		};

		void onDraw(Shader<VertexP3N3T2>* shader, const glm::mat4& transform) override {
			std::lock_guard<std::mutex> lock(parentObject->verticesMutex);

			if (parentObject->vertices.size() <= 0) {
				return;
			}

			if (texture == nullptr) {
				return;
			}

			texture->use();
			shader->draw(parentObject->vertices, transform, DrawMode::TRIANGLES);
		};
	};
}
