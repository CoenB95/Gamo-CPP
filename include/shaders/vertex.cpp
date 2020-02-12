#include "shaders/vertex.h"

namespace gamo {

    VertexP3C4::VertexP3C4() : VertexP3C4(glm::vec3(), glm::vec4()) {

    };

    VertexP3C4::VertexP3C4(const glm::vec3& position, const glm::vec4& color) :
        position(position),
        color(color) {
    }


    VertexP3N3T2::VertexP3N3T2() : VertexP3N3T2(glm::vec3(), glm::vec3(), glm::vec2()) { };
    VertexP3N3T2::VertexP3N3T2(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoord) :
        position(position),
        normal(normal),
        texCoord(texCoord) {
    }


    Attribute::Attribute(std::string name, GLint size, GLenum type) : name(name), size(size), type(type), bytes(calcBytes(type)) {

    };

    int Attribute::calcBytes(GLenum type) {
        switch (type) {
        case GL_FLOAT: return sizeof(float); // 4 bytes
        default: return 0;
        }
    }


    void Attribute::bind() {
        glEnableVertexAttribArray(id);
    }
}