#pragma once

#include <GL/glew.h>

#include "shaders/texture.h"

namespace gamo {
	class Fbo {
	private:
		GLuint id;

	public:
		Texture* texture;

		Fbo(int width, int height);

		void bind();
		void unbind();
	};
}