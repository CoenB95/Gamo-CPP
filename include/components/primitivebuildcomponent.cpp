#include <mutex>

#include "components/primitivebuildcomponent.h"
#include "objects/gameobject.h"

namespace gamo {
    TexturedCubeBuildComponent::TexturedCubeBuildComponent(glm::ivec2 textureTileCount, glm::vec3 size, std::vector<glm::vec2> indices) {
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
    }

    void TexturedCubeBuildComponent::onBuild(std::vector<VertexP3N3T2>& vertices) {
        double hw = cubeSize.x / 2;
        double hh = cubeSize.y / 2;
        double hd = cubeSize.z / 2;
        glm::vec2 ts = glm::vec2(1.0 / tileCount.x, 1.0 / tileCount.y);

        if (isInBox(topTileCoord, tileCount)) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            glm::vec2 tileCoord = topTileCoord * ts;
            vertices.insert(vertices.end(), {
              VertexP3N3T2(glm::vec3(hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, ts.y)),
              VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw,  hh, -hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw,  hh,  hd), glm::vec3(0, 1, 0), tileCoord + glm::vec2(ts.x, 0))
                });
        }
        if (isInBox(frontTileCoord, tileCount)) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            glm::vec2 tileCoord = frontTileCoord * ts;
            vertices.insert(vertices.end(), {
              VertexP3N3T2(glm::vec3(hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, ts.y)),
              VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw,  hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw, -hh,  hd), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, 0))
                });
        }
        if (isInBox(rightTileCoord, tileCount)) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            glm::vec2 tileCoord = rightTileCoord * ts;
            vertices.insert(vertices.end(), {
              VertexP3N3T2(glm::vec3(hw,  hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(hw,  hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, ts.y)),
              VertexP3N3T2(glm::vec3(hw, -hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw,  hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(hw, -hh,  hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw, -hh, -hd), glm::vec3(1, 0, 0), tileCoord + glm::vec2(ts.x, 0))
                });
        }
        if (isInBox(bottomTileCoord, tileCount)) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            glm::vec2 tileCoord = bottomTileCoord * ts;
            vertices.insert(vertices.end(), {
              VertexP3N3T2(glm::vec3(hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(-hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, ts.y)),
              VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw, -hh,  hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw, -hh, -hd), glm::vec3(0, -1, 0), tileCoord + glm::vec2(ts.x, 0))
                });
        }
        if (isInBox(backTileCoord, tileCount)) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            glm::vec2 tileCoord = backTileCoord * ts;
            vertices.insert(vertices.end(), {
              VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, ts.y)),
              VertexP3N3T2(glm::vec3(hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(-hw, -hh, -hd), glm::vec3(0, 0, -1), tileCoord + glm::vec2(ts.x, 0))
                });
        }
        if (isInBox(leftTileCoord, tileCount)) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
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
    
    TexturedPaneBuildComponent::TexturedPaneBuildComponent(glm::vec2 tileCount, glm::vec2 tileCoord, glm::vec2 paneSize) {
        this->paneSize = paneSize;
        this->tileCount = tileCount;
        this->frontTileCoord = tileCoord;
    }

    void TexturedPaneBuildComponent::onBuild(std::vector<VertexP3N3T2>& vertices) {
        double hw = paneSize.x / 2;
        double hh = paneSize.y / 2;
        glm::vec2 ts = glm::vec2(1.0 / tileCount.x, 1.0 / tileCount.y);

        if (isInBox(frontTileCoord, tileCount)) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            glm::vec2 tileCoord = frontTileCoord * ts;
            vertices.insert(vertices.end(), {
              VertexP3N3T2(glm::vec3(hw,  hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(-hw,  hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, ts.y)),
              VertexP3N3T2(glm::vec3(-hw, -hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw,  hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, ts.y)),
              VertexP3N3T2(glm::vec3(-hw, -hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(0, 0)),
              VertexP3N3T2(glm::vec3(hw, -hh,  0), glm::vec3(0, 0, 1), tileCoord + glm::vec2(ts.x, 0))
                });
        }
    }

    void ColoredCubeBuildComponent::onBuild(std::vector<VertexP3N3C4>& vertices) {
        double hw = size.x / 2;
        double hh = size.y / 2;
        double hd = size.z / 2;

        if (top) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            vertices.insert(vertices.end(), {
              VertexP3N3C4(glm::vec3(hw,  hh, -hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
              VertexP3N3C4(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
              VertexP3N3C4(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
              VertexP3N3C4(glm::vec3(hw,  hh, -hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
              VertexP3N3C4(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
              VertexP3N3C4(glm::vec3(hw,  hh,  hd), glm::vec3(0, 1, 0), glm::vec4(1, 0, 0, 1)),
                });
        }
        if (front) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            vertices.insert(vertices.end(), {
              VertexP3N3C4(glm::vec3(hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(-hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(hw,  hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(-hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(hw, -hh,  hd), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0, 1)),
                });
        }
        if (right) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            vertices.insert(vertices.end(), {
              VertexP3N3C4(glm::vec3(hw,  hh, -hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(hw,  hh,  hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(hw, -hh,  hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(hw,  hh, -hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(hw, -hh,  hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
              VertexP3N3C4(glm::vec3(hw, -hh, -hd), glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)),
                });
        }
        if (bottom) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            vertices.insert(vertices.end(), {
              VertexP3N3C4(glm::vec3(hw, -hh,  hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
              VertexP3N3C4(glm::vec3(-hw, -hh,  hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
              VertexP3N3C4(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
              VertexP3N3C4(glm::vec3(hw, -hh,  hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
              VertexP3N3C4(glm::vec3(-hw, -hh, -hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
              VertexP3N3C4(glm::vec3(hw, -hh, -hd), glm::vec3(0, -1, 0), glm::vec4(0, 1, 1, 1)),
                });
        }
        if (back) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
            vertices.insert(vertices.end(), {
              VertexP3N3C4(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
              VertexP3N3C4(glm::vec3(hw,  hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
              VertexP3N3C4(glm::vec3(hw, -hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
              VertexP3N3C4(glm::vec3(-hw,  hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
              VertexP3N3C4(glm::vec3(hw, -hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
              VertexP3N3C4(glm::vec3(-hw, -hh, -hd), glm::vec3(0, 0, -1), glm::vec4(0, 0, 1, 1)),
                });
        }
        if (left) {
            std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
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

    void ColoredPaneBuildComponent::onBuild(std::vector<VertexP3N3C4>& vertices) {
        double hw = paneSize.x / 2;
        double hh = paneSize.y / 2;

        std::lock_guard<std::mutex> lock(parentObject->verticesMutex);
        vertices.insert(vertices.end(), {
            VertexP3N3C4(glm::vec3(hw,  hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
            VertexP3N3C4(glm::vec3(-hw,  hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
            VertexP3N3C4(glm::vec3(-hw, -hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
            VertexP3N3C4(glm::vec3(hw,  hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
            VertexP3N3C4(glm::vec3(-hw, -hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1)),
            VertexP3N3C4(glm::vec3(hw, -hh, 0), glm::vec3(0, 0, 1), glm::vec4(1, 0, 1, 1))
            });
    }
}