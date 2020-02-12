

namespace gamo {
    class Cubes {
    public:
        static GameObject<VertexP3C4>* colored(double size = 1);
        static GameObject<VertexP3N3T2>* textured(double size = 1);
    };
}