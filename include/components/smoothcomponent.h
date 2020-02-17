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
        SmoothComponent(float snappyness, bool rotate = false, bool scale = false, bool translate = false) :
            GameObjectComponent(),
            snappyness(snappyness) {
            this->translate = translate;
            this->rotate = rotate;
        };

        void onAttach(GameObjectBase* newParent) override {
            previousOrientation = parentObject->orientation;
            previousPosition = parentObject->position;
            previousScale = parentObject->scale;
        }

        void onUpdate(float elapsedSeconds) override {
            if (rotate) {
                parentObject->orientation = glm::slerp(previousOrientation, parentObject->orientation, elapsedSeconds * snappyness);
            }

            if (scale) {
                parentObject->scale = glm::mix(previousScale, parentObject->scale, elapsedSeconds * snappyness);
            }

            if (translate) {
                parentObject->position = glm::mix(previousPosition, parentObject->position, elapsedSeconds * snappyness);
            }

            previousOrientation = parentObject->orientation;
            previousPosition = parentObject->position;
            previousScale = parentObject->scale;
        };
    };
}