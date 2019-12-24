#pragma once

#include <glm/glm.hpp>

namespace gamo {
    struct VertexP3C4 {
        const glm::vec3 position;
        const glm::vec4 color;

        VertexP3C4() : VertexP3C4(glm::vec3(), glm::vec4()) { };
        VertexP3C4(const glm::vec3& position, const glm::vec4& color) :
            position(position),
            color(color) {
        }
    };

    struct VertexP3N3T2 {
        const glm::vec3 position;
        const glm::vec3 normal;
        const glm::vec2 texCoord;

        VertexP3N3T2() : VertexP3N3T2(glm::vec3(), glm::vec3(), glm::vec2()) { };
        VertexP3N3T2(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoord) :
            position(position),
            normal(normal),
            texCoord(texCoord) {
        }
    };
}