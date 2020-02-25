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
        int imageWidth;
        int imageHeight;
        int imageComponents;
        stbi_uc* imageData;
        bool loaded = false;

        bool parametersChanged = true;
        bool filterNearest = false;
        bool repeatTexture = true;

        Texture(stbi_uc* data, int imageWidth, int imageHeight, int imageComponents);
        void load();

    public:
        static Texture* empty(int width, int height, int components = 4);
        static Texture* ofCachedImage(const std::string& fileName, bool filterNearest = false, bool repeatTexture = true);
        static Texture* ofImage(const std::string& filename, bool filterNearest, bool repeatTexture);

        void bind();
        inline GLuint getHeight() { return imageHeight; };
        inline GLuint getId() { return id; };
        inline GLuint getWidth() { return imageWidth; };
        void setFilterNearest(bool nearest);
        void setRepeatTexture(bool repeat);
        void use(int index = 0);
    };
}
