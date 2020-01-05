#include <functional>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "shaders/vertex.h"

using namespace gamo;
using namespace glm;
using namespace std;

namespace gamo {
  enum DrawMode {
    POINTS,
    TRIANGLES,
    TRIANGLE_STRIP
  };

  /*class Attribute {
  public:
    const string name;
    int id;
    int size;
    int type;

    void bind() {
      glEnableVertexAttribArray(id);
    }

    int getByteCount() {
      switch (type) {
        case 0: return 4;
        default: return 0;
      }
    }

    Attribute(string name, int size, int type = GL_FLOAT);
  };

  class VertexP3AttribArray : Attribute {
  public:
    const string name;
    int id;
    int size;
    int type;

    void bind() {
      Attribute::bind();
			glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset + prevSize));
    }

    int getByteCount() {
      switch (type) {
        case 0: return 4;
        default: return 0;
      }
    }

    Attribute(string name, int size, int type = GL_FLOAT);
  };*/

  class Uniform {
  public:
    const string name;
    GLint id;

    Uniform(string name);

    virtual void update();
  };

  class Matrix4Uniform : public Uniform {
  private:
    function<mat4()> bindValue;

  public:
    Matrix4Uniform(string name, const function<mat4()>& valueBind) : Uniform(name), bindValue(valueBind) { };

    inline void update() override { glUniformMatrix4fv(id, 1, false, glm::value_ptr(bindValue())); }
  };

  class IntegerUniform : public Uniform {
  private:
    function<int()> bindValue;

  public:
    IntegerUniform(const string& name, const function<int()> valueBind) : Uniform(name), bindValue(valueBind) { };

    inline void update() override { glUniform1i(id, bindValue()); }
  };

  /*class ArrayBuffer {
  private:
    GLuint bufferId;
    vector<float> data;

  public:
    inline void bind() { glBindBuffer(GL_ARRAY_BUFFER, bufferId); };
    void draw(DrawMode mode) {
      if (data.empty()) {
        return;
      }

      switch (mode) {
        case DrawMode::POINTS:
          glDrawArrays(GL_POINTS, 0, data.size());
          break;
        case DrawMode::TRIANGLES:
          glDrawArrays(GL_TRIANGLES, 0, data.size());
          break;
        case DrawMode::TRIANGLE_STRIP:
          glDrawArrays(GL_TRIANGLE_STRIP, 0, data.size());
          break;
        default:
          break;
      }
    }

  public:
    ArrayBuffer() { };

    void setData(const vector<Vertex>& data) {
      if (data.empty()) {
        return;
      }

      bind();
      //this->data = data.map((t) => t.storage()).reduce((l1, l2) => Float32List.fromList(l1 + l2));
      glBufferData(GL_ARRAY_BUFFER, this->data, GL_STATIC_DRAW);
    }
  };*/

  class Texture {
  private:
    GLuint textureId;

    void bind() {
      glBindTexture(GL_TEXTURE_2D, textureId);
    }

    void use(int index) {
      switch (index) {
        case 1:
          glActiveTexture(GL_TEXTURE1);
          break;
        case 0:
        default:
          glActiveTexture(GL_TEXTURE0);
          break;
      }
      bind();
    }
  };

  class Shader {
  private:
    GLuint fragShaderId;
    GLuint vertShaderId;
    GLuint programId;

  public:
    mat4 modelMatrix;
    mat4 viewMatrix;
    mat4 projectionMatrix;
    AttribArray* attributeArray = nullptr;
    //vector<Attribute> attributes;
    vector<Uniform> uniforms;
    //gl.Program _program;
    //gl.Shader _fragShader, _vertShader;

    Shader() { };

    inline static mat4& Shader::compose(const vec3& position, const quat& orientation, const vec3& scale) {
	    mat4 modelMatrix = mat4();
	    modelMatrix = glm::translate(modelMatrix, position);
	    modelMatrix = glm::scale(modelMatrix, scale);
	    modelMatrix *= glm::toMat4(orientation);
	    return modelMatrix;
    };

    void initFromFiles(const string& vertShaderFileName, const string& fragShaderFileName,
        AttribArray* attributeArray, const vector<Uniform>& uniforms) {
      initFromSources(readShaderFile(vertShaderFileName), readShaderFile(fragShaderFileName), attributeArray, uniforms);
    };

    void initFromSources(const string& vertShaderSrc, const string& fragShaderSrc,
        AttribArray* attributeArray, const vector<Uniform>& uniforms) {
      //this->attributes.push_back(attributes);
      //_uniforms.addAll(uniforms);
      this->attributeArray = attributeArray;

			fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
			const char* fragSrc = fragShaderSrc.c_str();
      glShaderSource(fragShaderId, 1, &fragSrc, NULL);
      glCompileShader(fragShaderId);
			//printShaderInfoLog(fileName, shaderId);
        
      vertShaderId = glCreateShader(GL_VERTEX_SHADER);
      const char* vertSrc = vertShaderSrc.c_str();
      glShaderSource(vertShaderId, 1, &vertSrc, NULL);
      glCompileShader(vertShaderId);

      programId = glCreateProgram();
      glAttachShader(programId, vertShaderId);
      glAttachShader(programId, fragShaderId);
      glLinkProgram(programId);

      /*if (!glGetProgramParameter(_program, gl.WebGL.LINK_STATUS)) {
        print("Could not initialise shaders");
      }*/
      
      if (this->attributeArray != nullptr) {
        attributeArray->link(programId);
      }

      for (Uniform uniform : uniforms) {
        GLint uniformLocation = glGetUniformLocation(programId, uniform.name.c_str());
        uniform.id = uniformLocation;
      }
    }

    string readShaderFile(const string& fileName) {
      ifstream shaderFile(fileName);
      string data = "";
      string line;
			while (shaderFile.good() && getline(shaderFile, line)) {
        data += line + "/n";
      }
      return data;
    }

    void draw(const vector<Vertex>& vertices, const mat4& transform, DrawMode mode) {
      modelMatrix = transform;
      for (Uniform uniform : uniforms) {
        uniform.update();
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
  };
}