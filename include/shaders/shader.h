#pragma once

#include <functional>
#include <fstream>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/type_ptr.hpp>
#include <string>

#include <iostream>

#include "shaders/vertex.h"

namespace gamo {
    enum class DrawMode {
        POINTS,
        TRIANGLES,
        TRIANGLE_STRIP
    };

    class Uniform {
    public:
        const std::string name;
        GLint id = -1;

        Uniform(std::string name) : name(name) { };

        virtual void update() = 0;
    };

    class Matrix4Uniform : public Uniform {
    private:
        std::function<const glm::mat4 & ()> bindValue;

    public:
        Matrix4Uniform(std::string name, const std::function<const glm::mat4 & ()>& valueBind) : Uniform(name), bindValue(valueBind) { };

        inline void update() override { glUniformMatrix4fv(id, 1, false, glm::value_ptr(bindValue())); }
    };

    class IntegerUniform : public Uniform {
    private:
        std::function<int()> bindValue;

    public:
        IntegerUniform(const std::string& name, const std::function<int()> valueBind) : Uniform(name), bindValue(valueBind) { };

        inline void update() override { glUniform1i(id, bindValue()); }
    };

    class FloatUniform : public Uniform {
    private:
        std::function<float()> bindValue;

    public:
        FloatUniform(const std::string& name, const std::function<float()> valueBind) : Uniform(name), bindValue(valueBind) { };

        inline void update() override { glUniform1f(id, bindValue()); }
    };

    bool checkShaderErrors(GLuint shaderId)
    {
        GLint status;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);					//kijk of het compileren is gelukt
        if (status == GL_FALSE)
        {
            int length, charsWritten;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);				//haal de lengte van de foutmelding op
            char* infolog = new char[length + 1];
            memset(infolog, 0, length + 1);
            glGetShaderInfoLog(shaderId, length, &charsWritten, infolog);		//en haal de foutmelding zelf op
            std::cout << "Error compiling shader:\n" << infolog << std::endl;
            delete[] infolog;
            return true;
        }
        return false;
    }

    template<class T>
    class Shader {
    private:
        GLuint fragShaderId = 0;
        GLuint vertShaderId = 0;
        GLuint programId = 0;

    public:
        glm::mat4 modelMatrix = glm::mat4();
        glm::mat4 viewMatrix = glm::mat4();
        glm::mat4 projectionMatrix = glm::mat4();
        AttribArray<T>* attributeArray = nullptr;
        std::vector<Uniform*> uniforms;

        Shader() { };

        void initFromFiles(const std::string& vertShaderFileName, const std::string& fragShaderFileName,
            AttribArray<T>* attributeArray, const std::vector<Uniform*>& uniforms) {
            initFromSources(readShaderFile(vertShaderFileName), readShaderFile(fragShaderFileName), attributeArray, uniforms);
        };

        void initFromSources(const std::string& vertShaderSrc, const std::string& fragShaderSrc,
            AttribArray<T>* attributeArray, const std::vector<Uniform*>& uniforms) {
            this->attributeArray = attributeArray;
            this->uniforms.insert(this->uniforms.end(), uniforms.begin(), uniforms.end());

            fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
            const char* fragSrc = fragShaderSrc.c_str();
            glShaderSource(fragShaderId, 1, &fragSrc, NULL);
            glCompileShader(fragShaderId);
            if (checkShaderErrors(fragShaderId))
            {
                glDeleteProgram(programId);
                programId = -1;
                throw std::invalid_argument("Could not find attribute '${attrib.name}'");
            }

            vertShaderId = glCreateShader(GL_VERTEX_SHADER);
            const char* vertSrc = vertShaderSrc.c_str();
            glShaderSource(vertShaderId, 1, &vertSrc, NULL);
            glCompileShader(vertShaderId);
            if (checkShaderErrors(vertShaderId))
            {
                glDeleteProgram(programId);
                programId = -1;
                throw std::invalid_argument("Could not find attribute '${attrib.name}'");
            }

            programId = glCreateProgram();
            glAttachShader(programId, vertShaderId);
            glAttachShader(programId, fragShaderId);
            glLinkProgram(programId);

            if (this->attributeArray != nullptr) {
                this->attributeArray->link(programId);
            }

            for (Uniform* uniform : uniforms) {
                GLint uniformLocation = glGetUniformLocation(programId, uniform->name.c_str());
                uniform->id = uniformLocation;
            }
        }

        std::string readShaderFile(const std::string& fileName) {
            std::ifstream shaderFile(fileName);
            std::string data = "";
            std::string line;
            while (shaderFile.good() && getline(shaderFile, line)) {
                data += line + "\n";
            }
            return data;
        }

        void draw(const std::vector<T>& vertices, const glm::mat4& transform, DrawMode mode) {
            modelMatrix = transform;
            for (Uniform* uniform : uniforms) {
                uniform->update();
            }
            attributeArray->bind(vertices);

            switch (mode) {
            case DrawMode::POINTS:
                glDrawArrays(GL_POINTS, 0, vertices.size());
                break;
            case DrawMode::TRIANGLES:
                glDrawArrays(GL_TRIANGLES, 0, vertices.size());
                break;
            case DrawMode::TRIANGLE_STRIP:
                glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
                break;
            default:
                break;
            }
        }

        void use() {
            glUseProgram(programId);
        }
    };

    class Shaders {
    public:
        inline static glm::mat4& Shaders::compose(const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale) {
            glm::mat4 modelMatrix = glm::identity<glm::mat4>();
            modelMatrix = glm::translate(modelMatrix, position);
            modelMatrix = glm::scale(modelMatrix, scale);
            modelMatrix *= glm::toMat4(orientation);
            return modelMatrix;
        };
    };
}