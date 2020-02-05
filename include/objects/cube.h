#include "components/primitivebuildcomponent.h"
#include "components/spincomponent.h"
#include "components/primitivedrawcomponent.h"
#include "objects/gameobject.h"

namespace gamo {
  class Cube : public GameObject {
  private:
    Cube() { };

  public:
      static Cube* colored(double size = 1) {
          Cube* cube = new Cube();
          cube->addComponent(new SpinComponent(10.0));
          cube->addComponent(new ColoredCubeBuildComponent(size));
          cube->addComponent(new ColorDrawComponent());
          return cube;
      };
      static Cube* textured(double size = 1) {
          Cube* cube = new Cube();
          cube->addComponent(new SpinComponent(10.0));
          cube->addComponent(new TexturedCubeBuildComponent(size));
          cube->addComponent(new TextureDrawComponent("res/terrain.png"));
          return cube;
      };
  };
}