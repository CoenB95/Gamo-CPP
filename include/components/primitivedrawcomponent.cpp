#include <mutex>

#include "components/primitivedrawcomponent.h"
#include "objects/gameobject.h"

namespace gamo {
	
	void ColorDrawComponent::onDraw(Shader<VertexP3N3C4>* shader, const glm::mat4& transform) {
		std::lock_guard<std::mutex> lock(parentObject->verticesMutex);

		if (parentObject->vertices.size() <= 0) {
			return;
		}

		shader->draw(parentObject->vertices, transform, DrawMode::TRIANGLES);
	}

	TextureDrawComponent::TextureDrawComponent(const std::string& fileName) : GameObjectComponent() {
		texture = Texture::loadCached(fileName, true);
	}

	void TextureDrawComponent::onDraw(Shader<VertexP3N3T2>* shader, const glm::mat4& transform) {
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
