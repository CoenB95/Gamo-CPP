#include "components/gameobjectcomponent.h"
#include "shaders/shader.h"

#include "components/texturedrawcomponent.h"

namespace gamo {
	TextureDrawComponent::TextureDrawComponent(const std::string& fileName) : GameObjectComponent() {
		texture = Texture::loadCached(fileName, true);
	}

	void TextureDrawComponent::onDraw(Shader* shader, const glm::mat4& transform) {
		std::lock_guard<std::mutex> lock(parentObject->verticesMutex);

		if (parentObject->vertices.size() <= 0) {
			return;
		}

		if (texture == nullptr) {
			return;
		}

		texture->use();
    	shader->draw(parentObject->vertices, transform, DrawMode::TRIANGLES);
	}
}
