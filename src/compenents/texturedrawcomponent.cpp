#include "components/gameobjectcomponent.h"
#include "shaders/shader.h"

#include "components/texturedrawcomponent.h"

TextureDrawComponent::TextureDrawComponent(const string& fileName) : GameObjectComponent() {
	texture = Texture::loadCached(fileName, true);
}

void TextureDrawComponent::onDraw(Shader* shader, const mat4& transform) {
	lock_guard<mutex> lock(parentObject->verticesMutex);

	if (parentObject->vertices.size() <= 0)
		return;

	if (texture == nullptr)
		return;

	texture->use();
    shader->draw(parentObject->vertices, transform, DrawMode::TRIANGLES);
}
