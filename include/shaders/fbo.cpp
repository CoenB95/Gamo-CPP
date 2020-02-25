#include "scenes/gamescene.h"

#include "shaders/fbo.h"

namespace gamo {
	Fbo::Fbo(int width, int height) {
		// Create FBO
		glGenFramebuffers(1, &id);
		bind();
		
		// Create and attach Texture to FBO
		texture = Texture::empty(width, height);
		texture->setFilterNearest(false);
		texture->setRepeatTexture(false);
		texture->bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getId(), 0);

		// Create and attach Renderbuffer (storing depth) to FBO
		GLuint rboId;
		glGenRenderbuffers(1, &rboId);
		glBindRenderbuffer(GL_RENDERBUFFER, rboId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboId);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		unbind();
	}

	void Fbo::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void Fbo::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}