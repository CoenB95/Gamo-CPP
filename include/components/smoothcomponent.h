#pragma once

#include "components/gameobjectcomponent.h"

namespace gamo {
    template<class T>
    class SmoothComponent : public GameObjectComponent<T> {
    private:
        glm::quat previousOrientation;
	    glm::vec3 previousPosition;
        glm::vec3 previousScale;
	    
	    bool rotate;
        bool scale;
	    bool translate;
        
	    float snappyness;

    public:
        SmoothComponent(float snappyness, bool rotate = false, bool scale = false, bool translate = false) :
                GameObjectComponent(),
                snappyness(snappyness) {
            this->translate = translate;
            this->rotate = rotate;
        };

	    void onUpdate(float elapsedSeconds) override {
            previousOrientation = parentObject->orientation;
            previousPosition = parentObject->position;
            previousScale = parentObject->scale;

            if (rotate) {
                parentObject->orientation = glm::slerp(previousOrientation, parentObject->orientation, snappyness);
            }

            if (scale) {
                parentObject->scale = glm::mix(previousScale, parentObject->scale, snappyness);
            }

            if (translate) {
                parentObject->position = glm::mix(previousPosition, parentObject->position, snappyness);
            }
        };
    };
}