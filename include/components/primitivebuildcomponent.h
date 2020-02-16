#include "components/gameobjectcomponent.h"

namespace gamo {
    inline bool isInBox(glm::vec2 coord, glm::vec2 box) {
        if (coord.x < 0 || coord.y < 0 || coord.x > box.x || coord.y >= box.y) {
            return false;
        }
        return true;
    }

    class TexturedCubeBuildComponent : public GameObjectComponent<VertexP3N3T2> {
    private:
        glm::vec3 cubeSize;
        glm::ivec2 tileCount;

    public:
        glm::vec2 topTileCoord;
        glm::vec2 leftTileCoord;
        glm::vec2 frontTileCoord;
        glm::vec2 rightTileCoord;
        glm::vec2 backTileCoord;
        glm::vec2 bottomTileCoord;

        TexturedCubeBuildComponent(glm::ivec2 textureTileCount, glm::vec3 size, std::vector<glm::vec2> indices = { }) {
            cubeSize = size;
            tileCount = textureTileCount;
            if (indices.size() == 6) {
                topTileCoord = indices[0];
                leftTileCoord = indices[1];
                frontTileCoord = indices[2];
                rightTileCoord = indices[3];
                backTileCoord = indices[4];
                bottomTileCoord = indices[5];
            }
        };

        void onBuild(std::vector<VertexP3N3T2>& vertices) override {
            double hw = cubeSize.x / 2;
            double hh = cubeSize.y / 2;
            double hd = cubeSize.z / 2;
            glm::vec2 ts = glm::vec2(1.0 / tileCount.x, 1.0 / tileCount.y);

            if (isInBox(topTileCoord, tileCount)) {
                glm::vec2 tileCoord = topTileCoord * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, 0))
                    });
            }
            if (isInBox(frontTileCoord, tileCount)) {
                glm::vec2 tileCoord = frontTileCoord * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, 0))
                    });
            }
            if (isInBox(rightTileCoord, tileCount)) {
                glm::vec2 tileCoord = rightTileCoord * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3( hw,  hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, 0))
                    });
            }
            if (isInBox(bottomTileCoord, tileCount)) {
                glm::vec2 tileCoord = bottomTileCoord * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, 0))
                    });
            }
            if (isInBox(backTileCoord, tileCount)) {
                glm::vec2 tileCoord = backTileCoord * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3( hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3( hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3( hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, 0))
                    });
            }
            if (isInBox(leftTileCoord, tileCount)) {
                glm::vec2 tileCoord = leftTileCoord * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(-1, 0, 0), tileCoord + glm::vec2(ts.x, 0))
                    });
            }
        }
    };

    class TexturedPaneBuildComponent : public GameObjectComponent<VertexP3N3T2> {
    private:
        glm::vec2 paneSize;
        glm::vec2 tileCount;

    public:
        glm::vec2 frontTileCoord = glm::vec2(-1, -1);

        TexturedPaneBuildComponent(glm::vec2 tileCount) : TexturedPaneBuildComponent(tileCount, glm::vec2(-1, -1), glm::vec2(1, 1)) { };
        TexturedPaneBuildComponent(glm::vec2 tileCount, glm::vec2 paneSize) : TexturedPaneBuildComponent(tileCount, glm::vec2(), paneSize) { };

        TexturedPaneBuildComponent(glm::vec2 tileCount, glm::vec2 tileCoord, glm::vec2 paneSize) {
            this->paneSize = paneSize;
            this->tileCount = tileCount;
            this->frontTileCoord = tileCoord;
        };

        void onBuild(std::vector<VertexP3N3T2>& vertices) override {
            double hw = paneSize.x / 2;
            double hh = paneSize.y / 2;
            glm::vec2 ts = glm::vec2(1.0 / tileCount.x, 1.0 / tileCount.y);

            if (isInBox(frontTileCoord, tileCount)) {
                glm::vec2 tileCoord = frontTileCoord * ts;
                vertices.insert(vertices.end(), {
                  VertexP3N3T2(glm::vec3( hw,  hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw,  hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw,  hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y)),
                  VertexP3N3T2(glm::vec3(-hw, -hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
                  VertexP3N3T2(glm::vec3( hw, -hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, 0))
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