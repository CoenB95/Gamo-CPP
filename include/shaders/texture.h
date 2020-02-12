#pragma once

#include "stb_image.h"

#include <GL/glew.h>
#include <map>
#include <string>

namespace gamo {
    class Texture {
    private:
        static std::map<std::string, Texture*> cache;

        GLuint id = 0;
        stbi_uc* data;

        Texture(stbi_uc* data, int imageWidth, int imageHeight, int imageComponents);;

    public:
        void bind();
        void use(int index = 0);
        static Texture* loadCached(const std::string& fileName, bool filterNearest = false, bool repeatTexture = true);
        static Texture* loadImage(const std::string& filename, bool filterNearest, bool repeatTexture);
        void setFilterNearest(bool nearest);
        void setRepeatTexture(bool repeat);
    };
}
