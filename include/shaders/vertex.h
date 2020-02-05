#pragma once

#include <GL/glew.h>
#include <glm.hpp>

namespace gamo {
    class Vertex {
    public:
        virtual void bindAttribArray(const std::vector<Vertex>& vertices);
    };
    
    struct VertexP3C4 : public Vertex {
        const glm::vec3 position;
        const glm::vec4 color;

        VertexP3C4() : VertexP3C4(glm::vec3(), glm::vec4()) { };
        VertexP3C4(const glm::vec3& position, const glm::vec4& color) :
            position(position),
            color(color) {
        }
        inline void bindAttribArray(const std::vector<Vertex>& vertices) override {
            GLsizei stride = 3 * sizeof(float) + 4 * sizeof(float);
            glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(&vertices + 0));
            glEnableVertexAttribArray(1);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (void*)(&vertices + 3 * sizeof(float)));
        }
    };

    struct VertexP3N3T2 : public Vertex {
        const glm::vec3 position;
        const glm::vec3 normal;
        const glm::vec2 texCoord;

        VertexP3N3T2() : VertexP3N3T2(glm::vec3(), glm::vec3(), glm::vec2()) { };
        VertexP3N3T2(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoord) :
            position(position),
            normal(normal),
            texCoord(texCoord) {
        }
        inline void bindAttribArray(const std::vector<Vertex>& vertices) override {
            GLsizei stride = 3 * sizeof(float) + 3 * sizeof(float) + 2 * sizeof(float);
            glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(&vertices + 0));
            glEnableVertexAttribArray(1);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(&vertices + 3 * sizeof(float)));
            glEnableVertexAttribArray(2);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)(&vertices + 3 * sizeof(float) + 3 * sizeof(float)));
        }
    };

    class Attribute {
    public:
        const std::string name;
        const GLint size;
        const GLenum type;
        int id;

        void bind() {
            glEnableVertexAttribArray(id);
        }

        int getByteCount() {
            switch (type) {
                case GL_FLOAT: return sizeof(float); // 4 bytes
                default: return 0;
            }
        }

        Attribute(std::string name, GLint size, GLenum type) : name(name), size(size), type(type) { };
        inline static Attribute vec2(const std::string& name) { return Attribute(name, 2, GL_FLOAT); };
        inline static Attribute vec3(const std::string& name) { return Attribute(name, 3, GL_FLOAT); };
        inline static Attribute vec4(const std::string& name) { return Attribute(name, 4, GL_FLOAT); };
    };

    class AttribArray {
    private:
        const std::vector<Attribute> attributes;

    public:
        AttribArray() { };
        AttribArray(const std::vector<Attribute> attributes) : attributes(attributes) { };
        void bind(const std::vector<Vertex>& vertices) {
            GLsizei stride = 0;
            int bytesOffset = 0;
            for (Attribute attrib : attributes) {
                stride += attrib.getByteCount();
            }
            for (Attribute attrib : attributes) {
                glEnableVertexAttribArray(attrib.id);
			    glVertexAttribPointer(attrib.id, attrib.size, attrib.type, GL_FALSE, stride, (void*)(&vertices + bytesOffset));
                bytesOffset += attrib.getByteCount();
            }
        };
        void link(GLuint programId) {
            for (Attribute attrib : attributes) {
                GLint attributeLocation = glGetAttribLocation(programId, attrib.name.c_str());
                if (attributeLocation < 0) {
                    throw std::invalid_argument("Could not find attribute '${attrib.name}'");
                }
                attrib.id = attributeLocation;
            }
        };

        inline static AttribArray* p3n3t2(const std::string& p3, const std::string& n3, const std::string& t2) {
            return new AttribArray({Attribute::vec3(p3), Attribute::vec3(n3), Attribute::vec2(t2)});
        };
    };
}