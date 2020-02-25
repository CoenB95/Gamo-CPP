#include <mutex>

#include "components/gameobjectcomponent.h"

namespace gamo {
    inline bool isInBox(glm::vec2 coord, glm::vec2 box) {
        if (coord.x < 0 || coord.y < 0 || coord.x > box.x || coord.y >= box.y) {
            return false;
        }
        return true;
    }

    class TexturedCubeBuildComponent : public GameObjectDrawComponent<VertexP3N3T2> {
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

        TexturedCubeBuildComponent(glm::ivec2 textureTileCount, glm::vec3 size, std::vector<glm::vec2> indices = { });

        void onBuild(std::vector<VertexP3N3T2>& vertices) override;
    };

    class TexturedPaneBuildComponent : public GameObjectDrawComponent<VertexP3N3T2> {
    private:
        glm::vec2 paneSize;
        glm::vec2 tileCount;

    public:
        glm::vec2 frontTileCoord = glm::vec2(-1, -1);

        TexturedPaneBuildComponent(glm::vec2 tileCount) : TexturedPaneBuildComponent(tileCount, glm::vec2(0, 0), glm::vec2(1, 1)) { };
        TexturedPaneBuildComponent(glm::vec2 tileCount, glm::vec2 paneSize) : TexturedPaneBuildComponent(tileCount, glm::vec2(), paneSize) { };
        TexturedPaneBuildComponent(glm::vec2 tileCount, glm::vec2 tileCoord, glm::vec2 paneSize);

        void onBuild(std::vector<VertexP3N3T2>& vertices) override;
    };

    class ColoredCubeBuildComponent : public GameObjectDrawComponent<VertexP3N3C4> {
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

        void onBuild(std::vector<VertexP3N3C4>& vertices) override;
    };

    class ColoredPaneBuildComponent : public GameObjectDrawComponent<VertexP3N3C4> {
    private:
        glm::vec2 paneSize;

    public:
        ColoredPaneBuildComponent(glm::vec2 size) {
            paneSize = size;
        };

        void onBuild(std::vector<VertexP3N3C4>& vertices) override;
    };
}