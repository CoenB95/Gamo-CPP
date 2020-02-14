#include "components/gameobjectcomponent.h"

namespace gamo {
    class TexturedCubeBuildComponent : public GameObjectComponent<VertexP3N3T2> {
    private:
        glm::vec3 cubeSize;
        glm::ivec2 tileCount;

    public:
        int topIndex = -1;
        int leftIndex = -1;
        int frontIndex = -1;
        int rightIndex = -1;
        int backIndex = -1;
        int bottomIndex = -1;

        TexturedCubeBuildComponent(glm::ivec2 textureTileCount, glm::vec3 size, std::vector<int> indices = { }) {
            cubeSize = size;
            tileCount = textureTileCount;
            if (indices.size() == 6) {
                topIndex = indices[0];
                leftIndex = indices[1];
                frontIndex = indices[2];
                rightIndex = indices[3];
                backIndex = indices[4];
                bottomIndex = indices[5];
            }
        };

        void onBuild(std::vector<VertexP3N3T2>& vertices) override {
            double hw = cubeSize.x / 2;
            double hh = cubeSize.y / 2;
            double hd = cubeSize.z / 2;
            glm::vec2 ts = glm::vec2(1.0 / tileCount.x, 1.0 / tileCount.y);

            if (topIndex >= 0) {
                glm::vec2 tileCoord = glm::vec2(topIndex % tileCount.x, topIndex / tileCount.x) * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, ts.y))
                    });
            }
            if (frontIndex >= 0) {
                glm::vec2 tileCoord = glm::vec2(frontIndex % tileCount.x, frontIndex / tileCount.x) * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y))
                    });
            }
            if (rightIndex >= 0) {
                glm::vec2 tileCoord = glm::vec2(rightIndex % tileCount.x, rightIndex / tileCount.x) * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3( hw,  hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw, -hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, ts.y))
                    });
            }
            if (bottomIndex >= 0) {
                glm::vec2 tileCoord = glm::vec2(bottomIndex % tileCount.x, bottomIndex / tileCount.x) * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, ts.y))
                    });
            }
            if (backIndex >= 0) {
                glm::vec2 tileCoord = glm::vec2(backIndex % tileCount.x, backIndex / tileCount.x) * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, ts.y))
                    });
            }
            if (leftIndex >= 0) {
                glm::vec2 tileCoord = glm::vec2(leftIndex % tileCount.x, leftIndex / tileCount.x) * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(ts.x, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(ts.x, ts.y))
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
            
            if (top) {
                vertices.insert(vertices.end(), {
                  VertexP3C4(glm::vec3( hw,  hh, -hd), glm::vec4(1, 0, 0, 1)),
                  VertexP3C4(glm::vec3(-hw,  hh, -hd), glm::vec4(1, 0, 0, 1)),
                  VertexP3C4(glm::vec3(-hw,  hh,  hd), glm::vec4(1, 0, 0, 1)),
                  VertexP3C4(glm::vec3( hw,  hh, -hd), glm::vec4(1, 0, 0, 1)),
                  VertexP3C4(glm::vec3(-hw,  hh,  hd), glm::vec4(1, 0, 0, 1)),
                  VertexP3C4(glm::vec3( hw,  hh,  hd), glm::vec4(1, 0, 0, 1)),
                    });
            }
            if (front) {
                vertices.insert(vertices.end(), {
                  VertexP3C4(glm::vec3( hw,  hh,  hd), glm::vec4(1, 1, 0, 1)),
                  VertexP3C4(glm::vec3(-hw,  hh,  hd), glm::vec4(1, 1, 0, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh,  hd), glm::vec4(1, 1, 0, 1)),
                  VertexP3C4(glm::vec3( hw,  hh,  hd), glm::vec4(1, 1, 0, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh,  hd), glm::vec4(1, 1, 0, 1)),
                  VertexP3C4(glm::vec3( hw, -hh,  hd), glm::vec4(1, 1, 0, 1)),
                    });
            }
            if (right) {
                vertices.insert(vertices.end(), {
                  VertexP3C4(glm::vec3( hw,  hh, -hd), glm::vec4(0, 1, 0, 1)),
                  VertexP3C4(glm::vec3( hw,  hh,  hd), glm::vec4(0, 1, 0, 1)),
                  VertexP3C4(glm::vec3( hw, -hh,  hd), glm::vec4(0, 1, 0, 1)),
                  VertexP3C4(glm::vec3( hw,  hh, -hd), glm::vec4(0, 1, 0, 1)),
                  VertexP3C4(glm::vec3( hw, -hh,  hd), glm::vec4(0, 1, 0, 1)),
                  VertexP3C4(glm::vec3( hw, -hh, -hd), glm::vec4(0, 1, 0, 1)),
                    });
            }
            if (bottom) {
                vertices.insert(vertices.end(), {
                  VertexP3C4(glm::vec3( hw, -hh,  hd), glm::vec4(0, 1, 1, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh,  hd), glm::vec4(0, 1, 1, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh, -hd), glm::vec4(0, 1, 1, 1)),
                  VertexP3C4(glm::vec3( hw, -hh,  hd), glm::vec4(0, 1, 1, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh, -hd), glm::vec4(0, 1, 1, 1)),
                  VertexP3C4(glm::vec3( hw, -hh, -hd), glm::vec4(0, 1, 1, 1)),
                    });
            }
            if (back) {
                vertices.insert(vertices.end(), {
                  VertexP3C4(glm::vec3(-hw,  hh, -hd), glm::vec4(0, 0, 1, 1)),
                  VertexP3C4(glm::vec3( hw,  hh, -hd), glm::vec4(0, 0, 1, 1)),
                  VertexP3C4(glm::vec3( hw, -hh, -hd), glm::vec4(0, 0, 1, 1)),
                  VertexP3C4(glm::vec3(-hw,  hh, -hd), glm::vec4(0, 0, 1, 1)),
                  VertexP3C4(glm::vec3( hw, -hh, -hd), glm::vec4(0, 0, 1, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh, -hd), glm::vec4(0, 0, 1, 1)),
                    });
            }
            if (left) {
                vertices.insert(vertices.end(), {
                  VertexP3C4(glm::vec3(-hw,  hh,  hd), glm::vec4(1, 0, 1, 1)),
                  VertexP3C4(glm::vec3(-hw,  hh, -hd), glm::vec4(1, 0, 1, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh, -hd), glm::vec4(1, 0, 1, 1)),
                  VertexP3C4(glm::vec3(-hw,  hh,  hd), glm::vec4(1, 0, 1, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh, -hd), glm::vec4(1, 0, 1, 1)),
                  VertexP3C4(glm::vec3(-hw, -hh,  hd), glm::vec4(1, 0, 1, 1))
                    });
            }
        }
    };
}