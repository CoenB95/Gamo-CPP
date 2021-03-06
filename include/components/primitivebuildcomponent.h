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

    class TexturedPaneBuildComponent : public GameObjectComponent<VertexP3N3T2> {
    private:
        glm::vec2 paneSize;
        glm::ivec2 tileCount;

    public:
        int tileIndex = -1;

        TexturedPaneBuildComponent(glm::ivec2 textureTileCount, glm::vec2 size, int index = -1) {
            paneSize = size;
            tileCount = textureTileCount;
            tileIndex = index;
        };

        void onBuild(std::vector<VertexP3N3T2>& vertices) override {
            double hw = paneSize.x / 2;
            double hh = paneSize.y / 2;
            glm::vec2 ts = glm::vec2(1.0 / tileCount.x, 1.0 / tileCount.y);

            if (tileIndex >= 0) {
                glm::vec2 tileCoord = glm::vec2(tileIndex % tileCount.x, tileIndex / tileCount.x) * ts;
                vertices.insert(vertices.end(), {
                    VertexP3N3T2(glm::vec3( hw,  hh, 0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, 0)),
                    VertexP3N3T2(glm::vec3(-hw,  hh, 0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
                    VertexP3N3T2(glm::vec3(-hw, -hh, 0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, ts.y)),
                    VertexP3N3T2(glm::vec3( hw,  hh, 0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, 0)),
                    VertexP3N3T2(glm::vec3(-hw, -hh, 0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, ts.y)),
                    VertexP3N3T2(glm::vec3( hw, -hh, 0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y))
                });
            }
        }
    };

    class ColoredCubeBuildComponent : public GameObjectComponent<VertexP3N3C4> {
    private:
        glm::vec3 size;

        bool top = true;
        bool left = true;
        bool front = true;
        bool right = true;
        bool back = true;
        bool bottom = true;

    public:
        ColoredCubeBuildComponent(glm::vec3 size) :
            size(size) {
        };

        void onBuild(std::vector<VertexP3N3C4>& vertices) override {
            double hw = size.x / 2;
            double hh = size.y / 2;
            double hd = size.z / 2;
            
            if (top) {
                vertices.insert(vertices.end(), {
                  VertexP3N3C4(glm::vec3( hw,  hh, -hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
                  VertexP3N3C4(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
                  VertexP3N3C4(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw,  hh, -hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
                  VertexP3N3C4(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw,  hh,  hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
                    });
            }
            if (front) {
                vertices.insert(vertices.end(), {
                  VertexP3N3C4(glm::vec3( hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
                    });
            }
            if (right) {
                vertices.insert(vertices.end(), {
                  VertexP3N3C4(glm::vec3( hw,  hh, -hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw,  hh,  hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw, -hh,  hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw,  hh, -hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw, -hh,  hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
                  VertexP3N3C4(glm::vec3( hw, -hh, -hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
                    });
            }
            if (bottom) {
                vertices.insert(vertices.end(), {
                  VertexP3N3C4(glm::vec3( hw, -hh,  hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh,  hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
                  VertexP3N3C4(glm::vec3( hw, -hh,  hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
                  VertexP3N3C4(glm::vec3( hw, -hh, -hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
                    });
            }
            if (back) {
                vertices.insert(vertices.end(), {
                  VertexP3N3C4(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3( hw,  hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3( hw, -hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3( hw, -hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
                    });
            }
            if (left) {
                vertices.insert(vertices.end(), {
                  VertexP3N3C4(glm::vec3(-hw,  hh,  hd), glm::vec3(-1, 0, 0), glm::vec4(1, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw,  hh, -hd), glm::vec3(-1, 0, 0), glm::vec4(1, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh, -hd), glm::vec3(-1, 0, 0), glm::vec4(1, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw,  hh,  hd), glm::vec3(-1, 0, 0), glm::vec4(1, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh, -hd), glm::vec3(-1, 0, 0), glm::vec4(1, 0, 1, 1)),
                  VertexP3N3C4(glm::vec3(-hw, -hh,  hd), glm::vec3(-1, 0, 0), glm::vec4(1, 0, 1, 1))
                    });
            }
        }
    };

    class ColoredPaneBuildComponent : public GameObjectComponent<VertexP3N3C4> {
    private:
        glm::vec2 paneSize;

    public:
        ColoredPaneBuildComponent(glm::vec2 size) {
            paneSize = size;
        };

        void onBuild(std::vector<VertexP3N3C4>& vertices) override {
            double hw = paneSize.x / 2;
            double hh = paneSize.y / 2;

            vertices.insert(vertices.end(), {
                VertexP3N3C4(glm::vec3( hw,  hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
                VertexP3N3C4(glm::vec3(-hw,  hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
                VertexP3N3C4(glm::vec3(-hw, -hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
                VertexP3N3C4(glm::vec3( hw,  hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
                VertexP3N3C4(glm::vec3(-hw, -hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
                VertexP3N3C4(glm::vec3( hw, -hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1))
                });
        }
    };
}