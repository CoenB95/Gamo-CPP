#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <iostream>
#include <map>
#include <string>
#include "stb_image.h"

using namespace std;

namespace gamo {
  class Texture {
  private:
    static map<string, Texture*> cache;

    GLuint id = -1;
    stbi_uc* data;

    Texture(stbi_uc* data, int imageWidth, int imageHeight, int imageComponents) : data(data) {
      GLenum imageFormat;
		  switch (imageComponents) {
		    case 3:
			    imageFormat = GL_RGB;
			    break;
        default:
		    case 4:
			    imageFormat = GL_RGBA;
			    break;
		  }

      bind();
      glTexImage2D(GL_TEXTURE_2D,
			  0,					      //level
			  GL_RGBA,			    //internal format
			  imageWidth,		    //width
			  imageHeight,    	//height
			  0,					      //border
			  imageFormat,	  	//data format
			  GL_UNSIGNED_BYTE,	//data type
			  data);				    //data
    };
    void createIfNeeded() {
      if (id < 0) {
        glGenTextures(1, &id);
      }
    };

  public:
    void bind() {
      createIfNeeded();
      glBindTexture(GL_TEXTURE_2D, id);
    }

    void use(int index = 0) {
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

    static Texture* loadCached(const string& fileName, bool filterNearest = false, bool repeatTexture = true) {
		  if (cache.find(fileName) == cache.end()) {
			  Texture* tex = loadImage(fileName, filterNearest, repeatTexture);
        if (tex != nullptr) {
          cache[fileName] = tex;
        }
      }
      
		  return cache[fileName];
	  }

    static Texture* loadImage(const std::string &filename, bool filterNearest, bool repeatTexture) {
			int width = -1;
			int height = -1;
			int depth = -1;
			stbi_uc* data = stbi_load(filename.c_str(), &width, &height, &depth, 4);
			
      if (data == nullptr) {
				const char* err = stbi_failure_reason();
				cout << "Error loading file " << filename << endl;
				cout << err << endl;
				return nullptr;
			}

      Texture* texture = new Texture(data, width, height, depth);
      texture->setFilterNearest(filterNearest);
      texture->setRepeatTexture(repeatTexture);
      return texture;
		}

    void Texture::setFilterNearest(bool nearest) {
      bind();
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, nearest ? GL_NEAREST : GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, nearest ? GL_NEAREST : GL_LINEAR);
	  }

	  void Texture::setRepeatTexture(bool repeat) {
		  bind();
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	  }
  };
}