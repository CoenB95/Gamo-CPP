#include "components/primitivebuildcomponent.h"
#include "components/spincomponent.h"
#include "components/texturedrawcomponent.h"
#include "objects/gameobject.h"

namespace gamo {
  class Cube : public GameObject {
  private:
    Cube() { };

  public:
    static Cube* textured(double size = 1) {
      Cube* cube = new Cube();
      cube->addComponent(new SpinComponent(10.0));
      cube->addComponent(new TexturedCubeBuildComponent(size));
      cube->addComponent(new TextureDrawComponent("res/terrain.png"));
    }
  };
}