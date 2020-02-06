#include "components/primitivebuildcomponent.h"
#include "components/spincomponent.h"
#include "components/primitivedrawcomponent.h"
#include "objects/gameobject.h"

namespace gamo {
    class Cubes {
    public:
        static GameObject<VertexP3C4>* colored(double size = 1) {
            GameObject<VertexP3C4>* cube = new GameObject<VertexP3C4>();
            cube->addComponent(new SpinComponent<VertexP3C4>(10.0));
            cube->addComponent(new ColoredCubeBuildComponent(size));
            cube->addComponent(new ColorDrawComponent());
            return cube;
        };
        static GameObject<VertexP3N3T2>* textured(double size = 1) {
            GameObject<VertexP3N3T2>* cube = new GameObject<VertexP3N3T2>();
            cube->addComponent(new SpinComponent<VertexP3N3T2>(10.0));
            cube->addComponent(new TexturedCubeBuildComponent(size));
            cube->addComponent(new TextureDrawComponent("res/terrain.png"));
            return cube;
        };
    };
}