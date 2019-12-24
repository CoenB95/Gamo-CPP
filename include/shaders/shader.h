#include <GL/glew.h>

#include "shaders/vertex.h"

namespace gamo {
    class Attribute {
    public:
        const string name;
        int id;
        int size;
        int type;

        int getByteCount() {
            switch (type) {
            case 0: return 4;
            default: return 0;
            }
        }

        Attribute(string name, int size, int type = 0);//gl.WebGL.FLOAT);
    };
}

 /*   virtual class Uniform<T> {
        const String name;
        gl.UniformLocation id;
        T value;
        T Function() bindValue;

        Uniform(this.name, this.value, [this.bindValue]);

        void _update(gl.RenderingContext2 gl);
    }

class Matrix4Uniform extends Uniform<Matrix4> {
  Matrix4Uniform(String name, [Matrix4 Function() valueBind]) : super(name, Matrix4.identity(), valueBind);

  @override
  void _update(gl.RenderingContext2 gl) {
    if (bindValue != null) {
      value = bindValue();
    }

    if (value != null) {
      gl.uniformMatrix4fv(id, false, value.storage);
    }
  }
}

class IntegerUniform extends Uniform<int> {
  IntegerUniform(String name, [int Function() valueBind]) : super(name, 0, valueBind);

  @override
  void _update(gl.RenderingContext2 gl) {
    if (bindValue != null) {
      value = bindValue();
    }

    if (value != null) {
      gl.uniform1i(id, value);
    }
  }
}

class ArrayBuffer {
  gl.Buffer _buffer;
  gl.RenderingContext2 _gl;
  Float32List _data;

  int get length => _data.length;

  ArrayBuffer(this._gl, [Iterable<Vertex> data]) {
    if (data != null) {
      setData(data);
    }
  }

  void _bind() {
    if (_buffer == null) {
      return;
    }
    _gl.bindBuffer(gl.WebGL.ARRAY_BUFFER, _buffer);
  }

  void setData(Iterable<Vertex> data) {
    if (data == null || data.isEmpty) {
      return;
    }
    if (_buffer == null) {
      _buffer = _gl.createBuffer();
    }
    _bind();
    _data = data.map((t) => t.storage()).reduce((l1, l2) => Float32List.fromList(l1 + l2));
    _gl.bufferData(
        gl.WebGL.ARRAY_BUFFER,
        _data,
        gl.WebGL.STATIC_DRAW);
  }

  void _draw(DrawMode mode) {
    if (_data == null || _data.isEmpty) {
      return;
    }
    switch (mode) {
      case DrawMode.points:
        _gl.drawArrays(gl.WebGL.POINTS, 0, length);
        break;
      case DrawMode.triangles:
        _gl.drawArrays(gl.WebGL.TRIANGLES, 0, length);
        break;
      case DrawMode.triangleStrip:
        _gl.drawArrays(gl.WebGL.TRIANGLE_STRIP, 0, length);
        break;
      default:
        break;
    }
  }
}

class Texture {
  gl.Texture id;

  void _bind(gl.RenderingContext2 context) {
    context.bindTexture(gl.WebGL.TEXTURE_2D, id);
  }

  void use(gl.RenderingContext2 context, int index) {
    switch (index) {
      case 1:
        context.activeTexture(gl.WebGL.TEXTURE1);
        break;
      case 0:
      default:
        context.activeTexture(gl.WebGL.TEXTURE0);
        break;
    }
    _bind(context);
  }
}

class Shader {
  Matrix4 modelMatrix = Matrix4.identity();
  Matrix4 viewMatrix = Matrix4.identity();
  Matrix4 projectionMatrix = Matrix4.identity();
  Matrix4 get modelViewMatrix => viewMatrix * modelMatrix;

  gl.RenderingContext2 _context;

  List<Attribute> _attributes = [];
  List<Uniform> _uniforms = [];
  gl.Program _program;
  gl.Shader _fragShader, _vertShader;

  Shader(this._context);

  void init(String vertSrc, String fragSrc,
      List<Attribute> attributes, List<Uniform> uniforms) {
    _attributes.addAll(attributes);
    _uniforms.addAll(uniforms);

    _fragShader = _context.createShader(gl.WebGL.FRAGMENT_SHADER);
    _context.shaderSource(_fragShader, fragSrc);
    _context.compileShader(_fragShader);

    _vertShader = _context.createShader(gl.WebGL.VERTEX_SHADER);
    _context.shaderSource(_vertShader, vertSrc);
    _context.compileShader(_vertShader);

    _program = _context.createProgram();
    _context.attachShader(_program, _vertShader);
    _context.attachShader(_program, _fragShader);
    _context.linkProgram(_program);

    if (!_context.getProgramParameter(_program, gl.WebGL.LINK_STATUS)) {
      print("Could not initialise shaders");
    }

    for (Attribute attrib in attributes) {
      int attributeLocation = _context.getAttribLocation(_program, attrib.name);
      if (attributeLocation < 0) {
        throw ArgumentError("Could not find attribute '${attrib.name}'");
      }
      _context.enableVertexAttribArray(attributeLocation);
      attrib.id = attributeLocation;
    }

    for (Uniform uniform in uniforms) {
      gl.UniformLocation uniformLocation = _context.getUniformLocation(_program, uniform.name);
      uniform.id = uniformLocation;
    }
  }

  void draw(ArrayBuffer buffer, DrawMode mode) {
    if (buffer == null) {
      return;
    }
    buffer._bind();
    _bindAttributeBuffer();
    _updateUniforms();
    buffer._draw(mode);
  }

  void _bindAttributeBuffer() {
    int attributeStride = _attributes.fold(0, (p, e) => p + e.size * e.bytes);
    int attributeOffset = 0;

    for (Attribute attribute in _attributes) {
      _context.vertexAttribPointer(attribute.id, attribute.size, gl.WebGL.FLOAT, false,
          attributeStride, attributeOffset);
      attributeOffset += attribute.size * attribute.bytes;
    }
  }

  void _updateUniforms() {
    for (Uniform uniform in _uniforms) {
      uniform._update(_context);
    }
  }

  void use() {
    _context.useProgram(_program);
  }
}*/