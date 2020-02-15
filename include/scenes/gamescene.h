#pragma once

#include "objects/gameobject.h"

namespace gamo {
	class GameScene {
	public:
		GameObject<VertexP3C4>* colored = new GameObject<VertexP3C4>();
		GameObject<VertexP3N3T2>* textured = new GameObject<VertexP3N3T2>();

		Shader<VertexP3C4>* coloredShader;
		Shader<VertexP3N3T2>* texturedShader;

		void draw() {
			coloredShader->use();
			colored->draw(coloredShader);

			texturedShader->use();
			textured->draw(texturedShader);
		};

		void update(double elapsedSeconds) {
			// Todo: move building to a thread.
			if (colored->shouldRebuild()) {
				colored->build(true);
			}
			if (textured->shouldRebuild()) {
				textured->build(true);
			}

			colored->update(elapsedSeconds);
			textured->update(elapsedSeconds);
		}
	};
}