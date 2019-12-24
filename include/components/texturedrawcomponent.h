#pragma once

#include "components/gameobjectcomponent.h"

using namespace gamo {
	class TextureDrawComponent : public GameObjectComponent {
	private:
		vrlib::Texture* texture;

	public:
		TextureDrawComponent(const string& fileName);

		void onDraw() override;
	};
}
