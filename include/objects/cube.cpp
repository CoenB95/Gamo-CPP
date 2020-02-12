#include "components/primitivebuildcomponent.h"
#include "components/spincomponent.h"
#include "components/primitivedrawcomponent.h"
#include "objects/gameobject.h"

#include "objects/cube.h"

namespace gamo {
    GameObject<VertexP3C4>* Cubes::colored(double size) {
        GameObject<VertexP3C4>* cube = new GameObject<VertexP3C4>();
        cube->addComponent(new SpinComponent<VertexP3C4>(40.0));
        cube->addComponent(new ColoredCubeBuildComponent(size));
        cube->addComponent(new ColorDrawComponent());
        return cube;
    }

    GameObject<VertexP3N3T2>* Cubes::textured(double size) {
        GameObject<VertexP3N3T2>* cube = new GameObject<VertexP3N3T2>();
        cube->addComponent(new SpinComponent<VertexP3N3T2>(40.0));
        cube->addComponent(new TexturedCubeBuildComponent(size));
        cube->addComponent(new TextureDrawComponent("libs/gamo/res/terrain.png"));
        return cube;
    }
}