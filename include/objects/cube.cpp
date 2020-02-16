#include "components/primitivebuildcomponent.h"
#include "components/spincomponent.h"
#include "components/primitivedrawcomponent.h"
#include "objects/gameobject.h"

#include "objects/cube.h"

#define p(x, y) glm::vec2(x, y)

namespace gamo {
    GameObject<VertexP3N3C4>* Cubes::colored(double size) {
        GameObject<VertexP3N3C4>* cube = new GameObject<VertexP3N3C4>();
        cube->addComponent(new SpinComponent<VertexP3N3C4>(glm::vec3(0.0, 40.0, 0.0)));
        cube->addComponent(new ColoredCubeBuildComponent(glm::vec3(size)));
        cube->addComponent(new ColorDrawComponent());
        return cube;
    }

    GameObject<VertexP3N3T2>* Cubes::mc(double size, std::vector<glm::vec2> indices) {
        return textured("libs/gamo/res/terrain.png", glm::ivec2(16, 16), glm::vec3(size), indices);
    }

    GameObject<VertexP3N3T2>* Cubes::textured(std::string filename, glm::ivec2 tileCount, glm::vec3 size, std::vector<glm::vec2> indices) {
        GameObject<VertexP3N3T2>* cube = new GameObject<VertexP3N3T2>();
        cube->addComponent(new SpinComponent<VertexP3N3T2>(glm::vec3(40.0, 0.0, 0.0)));
        cube->addComponent(new TexturedCubeBuildComponent(tileCount, glm::vec3(size), indices));
        cube->addComponent(new TextureDrawComponent(filename));
        return cube;
    }

    GameObject<VertexP3N3T2>* Cubes::mcGrass(double size) {
        return mc(size, { p(0, 15), p(3, 15), p(3, 15), p(3, 15), p(3, 15), p(2, 15) });
    }

    GameObject<VertexP3N3T2>* Cubes::mcPumpkin(double size) {
        return mc(size, { p(6, 9), p(6, 8), p(7, 8), p(6, 8), p(6, 8), p(6, 8) });
    }

    GameObject<VertexP3N3T2>* Cubes::mcTotal(double size) {
        return textured("libs/gamo/res/terrain.png", glm::ivec2(1, 1), glm::vec3(size), { p(0, 0), p(0, 0), p(0, 0), p(0, 0), p(0, 0), p(0, 0) });
    }
}