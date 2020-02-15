#pragma once

#include "gameobject.h"

namespace gamo {
    class Panes {
    public:
        static GameObject<VertexP3N3C4>* colored(double size);
        static GameObject<VertexP3N3T2>* textured(std::string filename, glm::ivec2 tileCount, glm::vec3 size, int index);
        static GameObject<VertexP3N3T2>* mcAll();
    };
}