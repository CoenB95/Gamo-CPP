

namespace gamo {
    class Cubes {
    public:
        static GameObject<VertexP3N3C4>* colored(float size = 1);
        static GameObject<VertexP3N3T2>* textured(std::string filename, glm::ivec2 tileCount, glm::vec3 size, std::vector<glm::vec2> indices = { });

        static GameObject<VertexP3N3T2>* mc(float size, std::vector<glm::vec2> indices = { });
        static GameObject<VertexP3N3T2>* mcGrass(float size = 1);
        static GameObject<VertexP3N3T2>* mcPumpkin(float size = 1);
        static GameObject<VertexP3N3T2>* mcTotal(float size = 1);
    };
}