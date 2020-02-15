#include "components/primitivebuildcomponent.h"
#include "components/spincomponent.h"
#include "components/primitivedrawcomponent.h"
#include "objects/gameobject.h"

#include "objects/cube.h"

namespace gamo {
    GameObject<VertexP3N3C4>* Cubes::colored(double size) {
        GameObject<VertexP3N3C4>* cube = new GameObject<VertexP3N3C4>();
        cube->addComponent(new SpinComponent<VertexP3N3C4>(glm::vec3(0.0, 40.0, 0.0)));
        cube->addComponent(new ColoredCubeBuildComponent(glm::vec3(size)));
        cube->addComponent(new ColorDrawComponent());
        return cube;
    }

    GameObject<VertexP3N3T2>* Cubes::mc(double size, std::vector<int> indices) {
        return textured("libs/gamo/res/terrain.png", glm::ivec2(16, 16), glm::vec3(size), indices);
    }

    GameObject<VertexP3N3T2>* Cubes::textured(std::string filename, glm::ivec2 tileCount, glm::vec3 size, std::vector<int> indices) {
        GameObject<VertexP3N3T2>* cube = new GameObject<VertexP3N3T2>();
        cube->addComponent(new SpinComponent<VertexP3N3T2>(glm::vec3(40.0, 0.0, 0.0)));
        cube->addComponent(new TexturedCubeBuildComponent(tileCount, glm::vec3(size), indices));
        cube->addComponent(new TextureDrawComponent(filename));
        return cube;
    }

    GameObject<VertexP3N3T2>* Cubes::mcGrass(double size) {
        return mc(size, { 0, 3, 3, 3, 3, 2 });
    }

    GameObject<VertexP3N3T2>* Cubes::mcPumpkin(double size) {
        return mc(size, { 102, 118, 119, 118, 118, 118 });
    }

    GameObject<VertexP3N3T2>* Cubes::mcTotal(double size) {
        return textured("libs/gamo/res/terrain.png", glm::ivec2(1, 1), glm::vec3(size), { 0, 0, 0, 0, 0, 0 });
    }
}