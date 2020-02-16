#pragma once

#include "objects/gameobject.h"

namespace gamo {
	class ShaderObjectPairBase {
	public:
		virtual void build() = 0;
		virtual void draw() = 0;
		virtual bool shouldRebuild() = 0;
		virtual void update(double elapsedSeconds) = 0;
	};

	template<class T>
	class ShaderObjectPair : public ShaderObjectPairBase {
	public:
		GameObject<T>* group;
		Shader<T>* shader;

		ShaderObjectPair(GameObject<T>* group, Shader<T>* shader) : group(group), shader(shader) { };

		void build() override {
			if (group->shouldRebuild()) {
				group->build(true);
			}
		};

		void draw() override {
			if (shader == nullptr) {
				std::cout << "Warning: GameObjectGroup '" << group->tag << "' has no shader to draw with." << std::endl;
				return;
			}

			shader->use();
			group->draw(shader);
		};

		bool shouldRebuild() override {
			return group->shouldRebuild();
		};

		void update(double elapsedSeconds) override {
			group->update(elapsedSeconds);
		};
	};

	class GameScene {
	public:
		std::vector<ShaderObjectPairBase*> pairs;

		void build() {
			for (ShaderObjectPairBase* pair : pairs) {
				pair->build();
			}
		};

		void draw() {
			for (ShaderObjectPairBase* pair : pairs) {
				pair->draw();
			}
		};

		bool shouldRebuild() {
			for (ShaderObjectPairBase* pair : pairs) {
				if (pair->shouldRebuild()) {
					return true;
				}
			}
			return false;
		};

		void update(double elapsedSeconds) {
			for (ShaderObjectPairBase* pair : pairs) {
				pair->update(elapsedSeconds);
			}
		};
	};
}