#include "components/gameobjectcomponent.h"

namespace gamo {
    class TexturedCubeBuildComponent : public GameObjectComponent<VertexP3N3T2> {
    private:
        double width;
        double height;
        double depth;

        bool top = true;
        bool left = true;
        bool front = true;
        bool right = true;
        bool back = true;
        bool bottom = true;

    public:
        TexturedCubeBuildComponent(double width = 1, double height = 1, double depth = 1) :
            width(width), height(height), depth(depth) { };

        void onBuild(std::vector<VertexP3N3T2>& vertices) override {
            double hw = width / 2;
            double hh = height / 2;
            double hd = depth / 2;
            if (front) {
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3(hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec2(1, 1)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec2(0, 1)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec2(1, 1)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec2(1, 0))
                    });
            }
        }
    };

    class ColoredCubeBuildComponent : public GameObjectComponent<VertexP3C4> {
    private:
        double width;
        double height;
        double depth;

        bool top = true;
        bool left = true;
        bool front = true;
        bool right = true;
        bool back = true;
        bool bottom = true;

    public:
        ColoredCubeBuildComponent(double width = 1, double height = 1, double depth = 1) :
            width(width), height(height), depth(depth) {
        };

        void onBuild(std::vector<VertexP3C4>& vertices) override {
            double hw = width / 2;
            double hh = height / 2;
            double hd = depth / 2;
            if (true) {
                vertices.insert(vertices.end(), {
                    VertexP3C4(glm::vec3( hw,  hh,  hd), glm::vec4(1, 0, 0, 1)),
                    VertexP3C4(glm::vec3(-hw,  hh,  hd), glm::vec4(0, 1, 0, 1)),
                    VertexP3C4(glm::vec3(-hw, -hh,  hd), glm::vec4(0, 0, 1, 1)),
                    VertexP3C4(glm::vec3( hw,  hh,  hd), glm::vec4(1, 1, 0, 1)),
                    VertexP3C4(glm::vec3(-hw, -hh,  hd), glm::vec4(0, 1, 1, 1)),
                    VertexP3C4(glm::vec3( hw, -hh,  hd), glm::vec4(1, 0, 1, 1)),
                });
            } else if (false) {
                vertices.insert(vertices.end(), {
                    VertexP3C4(glm::vec3(-1, -1, 0), glm::vec4(1, 1, 0, 1)),
                    VertexP3C4(glm::vec3(1, -1, 0), glm::vec4(0, 1, 1, 1)),
                    VertexP3C4(glm::vec3(-1, 1, 0), glm::vec4(1, 0, 1, 1))
                });
            }
        }
    };
}