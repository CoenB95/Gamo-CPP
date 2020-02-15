

namespace gamo {
    class Cubes {
    public:
        static GameObject<VertexP3N3C4>* colored(double size = 1);
        static GameObject<VertexP3N3T2>* textured(std::string filename, glm::ivec2 tileCount, glm::vec3 size, std::vector<int> indices = { });

        static GameObject<VertexP3N3T2>* mc(double size, std::vector<int> indices = { });
        static GameObject<VertexP3N3T2>* mcGrass(double size = 1);
        static GameObject<VertexP3N3T2>* mcPumpkin(double size = 1);
        static GameObject<VertexP3N3T2>* mcTotal(double size = 1);
    };
}