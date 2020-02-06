#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include <vector>

namespace gamo {
    class Vertex {
    public:
        
    };
    
    struct VertexP3C4 : public Vertex {
        glm::vec3 position;
        glm::vec4 color;

        VertexP3C4() : VertexP3C4(glm::vec3(), glm::vec4()) { };
        VertexP3C4(const glm::vec3& position, const glm::vec4& color) :
            position(position),
            color(color) {
        }
    };

    struct VertexP3N3T2 : public Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;

        VertexP3N3T2() : VertexP3N3T2(glm::vec3(), glm::vec3(), glm::vec2()) { };
        VertexP3N3T2(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoord) :
            position(position),
            normal(normal),
            texCoord(texCoord) {
        }
    };

    class Attribute {
    private:
        Attribute(std::string name, GLint size, GLenum type) : name(name), size(size), type(type), bytes(calcBytes(type)) { };

        int calcBytes(GLenum type) {
            switch (type) {
            case GL_FLOAT: return sizeof(float); // 4 bytes
            default: return 0;
            }
        }

    public:
        const std::string name;
        const GLint bytes;
        const GLint size;
        const GLenum type;
        int id = -1;

        void bind() {
            glEnableVertexAttribArray(id);
        }

        inline static Attribute vec2(const std::string& name) { return Attribute(name, 2, GL_FLOAT); };
        inline static Attribute vec3(const std::string& name) { return Attribute(name, 3, GL_FLOAT); };
        inline static Attribute vec4(const std::string& name) { return Attribute(name, 4, GL_FLOAT); };
    };

    template<class T>
    class AttribArray {
    private:
        std::vector<Attribute> attributes;

    public:
        AttribArray(const std::vector<Attribute> attributes) : attributes(attributes) { };

        void bind(const std::vector<T>& vertices) {
            GLsizei stride = 0;
            int bytesOffset = 0;
            for (Attribute attrib : attributes) {
                stride += attrib.size * attrib.bytes;
            }
            for (Attribute attrib : attributes) {
                glEnableVertexAttribArray(attrib.id);
			    glVertexAttribPointer(attrib.id, attrib.size, attrib.type, false, stride, (float*)(&vertices[0]) + bytesOffset);
                bytesOffset += attrib.size;
            }
        };

        void link(GLuint programId) {
            for (Attribute& attrib : attributes) {
                GLint attributeLocation = glGetAttribLocation(programId, attrib.name.c_str());
                if (attributeLocation < 0) {
                    throw std::invalid_argument("Could not find attribute '${attrib.name}'");
                }
                attrib.id = attributeLocation;
            }
        };
    };

    class AttribArrays {
    public:
        inline static AttribArray<VertexP3C4>* p3c4(const std::string& p3, const std::string& c4) {
            return new AttribArray<VertexP3C4>({ Attribute::vec3(p3), Attribute::vec4(c4) });
        };

        inline static AttribArray<VertexP3N3T2>* p3n3t2(const std::string& p3, const std::string& n3, const std::string& t2) {
            return new AttribArray<VertexP3N3T2>({ Attribute::vec3(p3), Attribute::vec3(n3), Attribute::vec2(t2) });
        };
    };
}