#pragma once

#include "objects/gameobject.h"

namespace gamo {
	class ShaderObjectPairBase {
	public:
		virtual void draw() = 0;
		virtual void update(double elapsedSeconds) = 0;
	};

	template<class T>
	class ShaderObjectPair : public ShaderObjectPairBase {
	public:
		GameObject<T>* group;
		Shader<T>* shader;

		ShaderObjectPair(GameObject<T>* group, Shader<T>* shader) : group(group), shader(shader) { };
		void draw() override {
			if (shader == nullptr) {
				std::cout << "Warning: GameObjectGroup '" << group->tag << "' has no shader to draw with." << std::endl;
				return;
			}

			shader->use();
			group->draw(shader);
		};

		void update(double elapsedSeconds) override {
			// Todo: move building to a thread.
			if (group->shouldRebuild()) {
				group->build(true);
			}

			group->update(elapsedSeconds);
		};
	};

	class GameScene {
	public:
		std::vector<ShaderObjectPairBase*> pairs;

		void draw() {
			for (ShaderObjectPairBase* pair : pairs) {
				pair->draw();
			}
		};

		void update(double elapsedSeconds) {
			for (ShaderObjectPairBase* pair : pairs) {
				pair->update(elapsedSeconds);
			}
		};
	};
}