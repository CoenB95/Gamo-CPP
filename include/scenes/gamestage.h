#pragma once

#include <map>

#include "scenes/gamescene.h"
#include "shaders/fbo.h"

namespace gamo
{
    class GameStageGL;
    
    class GameStageGL
    {
    private:
        static GameStageGL* instance;

        GameScene* scene = nullptr;
        Fbo* fbo = nullptr;
        GameObjectBase* camera = nullptr;
        GameObjectBase* player = nullptr;
        int lastTimeMillis = 0;
        glm::mat4 projectionMatrix {};
        glm::mat4 viewMatrix {};

        std::map<char, bool> keys {};
        glm::ivec2 screenSize {};

        Shader<VertexP3N3T2>* postShader = nullptr;
        GameObject<VertexP3N3T2>* postProcessingPane = nullptr;

        GameStageGL();

        void build();
        void reshape(int newWidth, int newHeight);
        void keyboardUp(unsigned char key, int x, int y);
        void keyboard(unsigned char key, int x, int y);
        void display();
        void displayScene(GLsizei w, GLsizei h);
        void displaySceneTexture(GLsizei w, GLsizei h);
        void update();
    
    public:
        static GameStageGL* getInstance();

        float_t getElapsedTime() const;
        const glm::mat4& getProjectionMatrix() const;
        const glm::mat4& getViewMatrix() const;
        GameScene* getScene();
        void setScene(GameScene* scene);
        void start();
        void init(int argc, char* argv[]);
    };
}