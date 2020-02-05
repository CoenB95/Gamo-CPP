#pragma once

#include "components/gameobjectcomponent.h"

namespace gamo {
    class SmoothComponent : public GameObjectComponent {
    private:
        glm::quat previousOrientation;
	    glm::vec3 previousPosition;
        glm::vec3 previousScale;
	    
	    bool rotate;
        bool scale;
	    bool translate;
        
	    float snappyness;

    public:
        SmoothComponent(float snappyness, bool rotate = false, bool scale = false, bool translate = false);

	    void onUpdate(float elapsedSeconds) override;
    };
}