#include "components/primitivebuildcomponent.h"
#include "components/primitivedrawcomponent.h"
#include "components/spincomponent.h"

#include "objects/pane.h"

namespace gamo {
    GameObject<VertexP3N3C4>* Panes::colored(double size) {
        GameObject<VertexP3N3C4>* cube = new GameObject<VertexP3N3C4>();
        cube->addComponent(new SpinComponent<VertexP3N3C4>(glm::vec3(0.0, 40.0, 0.0)));
        cube->addComponent(new ColoredPaneBuildComponent(glm::vec3(size)));
        cube->addComponent(new ColorDrawComponent());
        return cube;
    }

    GameObject<VertexP3N3T2>* Panes::textured(std::string filename, glm::ivec2 tileCount, glm::vec3 size, int index) {
        GameObject<VertexP3N3T2>* cube = new GameObject<VertexP3N3T2>();
        cube->addComponent(new SpinComponent<VertexP3N3T2>(glm::vec3(40.0, 0.0, 0.0)));
        cube->addComponent(new TexturedPaneBuildComponent(tileCount, glm::vec3(size), index));
        cube->addComponent(new TextureDrawComponent(filename));
        return cube;
    }

    GameObject<VertexP3N3T2>* Panes::mcAll() {
        return textured("libs/gamo/res/terrain.png", glm::ivec2(1, 1), glm::vec3(1, 1, 1), 0);
    }
}