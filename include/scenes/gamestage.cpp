#define _USE_MATH_DEFINES

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <math.h>

#include "objects/gameobject.h"
#include "components/followcomponent.h"
#include "components/primitivebuildcomponent.h"
#include "components/primitivedrawcomponent.h"
#include "components/smoothcomponent.h"
#include "scenes/gamestage.h"

#ifdef WIN32
void GLAPIENTRY onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
#else
void onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
#endif
{
	std::cout << message << std::endl;
}

namespace gamo
{
    GameStageGL* GameStageGL::instance = nullptr;

    GameStageGL* GameStageGL::getInstance()
    {
        if (instance == nullptr)
        {
            instance = new GameStageGL();
        }
        return instance;
    }

    GameStageGL::GameStageGL()
    {
        
    }

    void GameStageGL::init(int argc, char* argv[])
    {
        glutInit(&argc, argv);
        glutInitWindowSize(800, 450);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow("Visualisatietechnieken");

        glutDisplayFunc([](){ GameStageGL::getInstance()->display(); });
        glutReshapeFunc([](int w, int h){ GameStageGL::getInstance()->reshape(w, h); });
        glutKeyboardFunc([](uint8_t key, int x, int y){ GameStageGL::getInstance()->keyboard(key, x, y); });
        glutKeyboardUpFunc([](uint8_t key, int x, int y){ GameStageGL::getInstance()->keyboardUp(key, x, y); });
        glutPassiveMotionFunc([](int x, int y){ GameStageGL::getInstance()->mouse(x, y); });
        glutIdleFunc([](){ GameStageGL::getInstance()->update(); });

        lastTimeMillis = glutGet(GLUT_ELAPSED_TIME);

        glewInit();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        // glEnable(GL_CULL_FACE);

        fbo = new Fbo(4096, 4096);
        
        player = new GameObject<VertexP3N3C4>();
        camera = new GameObject<VertexP3N3C4>();
        camera->addComponent(new FollowComponent(player, true, false, true));
        camera->addComponent(new SmoothComponent(0.1f, false, false, true));
        camera->addComponent(new SmoothComponent(0.8f, true, false, false));

        postProcessingPane = new GameObject<VertexP3N3T2>();
        postProcessingPane->addComponent(new TexturedPaneBuildComponent(glm::vec2(1, 1), glm::vec2(3, 3)));
        postProcessingPane->addComponent(new TextureDrawComponent(fbo->texture));
        postProcessingPane->build();

        if (glDebugMessageCallback) {
            glDebugMessageCallback(&onDebug, NULL);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
            glEnable(GL_DEBUG_OUTPUT);
        }
    }

    void GameStageGL::build() {
        while (true) {
            if (scene->shouldRebuild()) {
                std::cout << "Building started.." << std::endl;
                scene->build();
                std::cout << "Done building!" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void GameStageGL::display() {
        if (postShader == nullptr)
        {
            displayScene(screenSize.x, screenSize.y);
        }
        else
        {
            fbo->bind();
            displayScene(fbo->texture->getWidth(), fbo->texture->getHeight());
            fbo->unbind();
            displaySceneTexture(screenSize.x, screenSize.y);
        }

        glutSwapBuffers();
    }

    void GameStageGL::displayScene(GLsizei w, GLsizei h) {
        glViewport(0, 0, w, h);
        glClearColor(0.3f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        projectionMatrix = glm::perspective(80.0f, screenSize.x / (float)screenSize.y, 0.01f, 100.0f);
        viewMatrix = glm::lookAt(camera->position, camera->position + camera->orientation * glm::vec3(0, 0, -1), glm::vec3(0, -1, 0));

        scene->draw();
    }

    void GameStageGL::displaySceneTexture(GLsizei w, GLsizei h) {
        glViewport(0, 0, w, h);
        glClearColor(0.3f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        projectionMatrix = glm::perspective(80.0f, screenSize.x / (float)screenSize.y, 0.01f, 100.0f);
        viewMatrix = glm::lookAt(camera->position, camera->position + camera->orientation * glm::vec3(0, 0, -1), glm::vec3(0, -1, 0));

        postShader->use();
        postProcessingPane->draw(postShader);
    }

    float GameStageGL::getElapsedTime() const
    {
        return lastTimeMillis / 1000.0f;
    }

    const glm::mat4& GameStageGL::getProjectionMatrix() const
    {
        return projectionMatrix;
    }

    const glm::mat4& GameStageGL::getViewMatrix() const
    {
        return viewMatrix;
    }

    void GameStageGL::mouse(int x, int y)
    {
        if (wrap)
        {
            int dx = x - screenSize.x / 2;
            int dy = y - screenSize.y / 2;
            std::cout << "MOUSE " << dx << ", " << dy;
            mouseVal += glm::vec2(dx * 0.004f, dy * 0.003f);
            player->orientation = glm::quat(glm::vec3((-mouseVal.y), (-mouseVal.x), 0));
            glutWarpPointer(screenSize.x / 2, screenSize.y / 2);
        }
    }

    void GameStageGL::setScene(GameScene* scene)
    {
        this->scene = scene;
    }

    void GameStageGL::start()
    {
        std::thread buildThread([this](){ build(); });
        glutMainLoop();
    }

    void GameStageGL::reshape(int newWidth, int newHeight) {
        screenSize.x = newWidth;
        screenSize.y = newHeight;
        glutPostRedisplay();
    }

    void GameStageGL::keyboardUp(unsigned char key, int x, int y) {
        keys[key] = false;
    }

    void GameStageGL::keyboard(unsigned char key, int x, int y) {
        keys[key] = true;

        if (key == VK_ESCAPE)
            glutLeaveMainLoop();
    }

    void GameStageGL::update() {
        int timeMillis = glutGet(GLUT_ELAPSED_TIME);
        int elapsedMillis = timeMillis - lastTimeMillis;
        lastTimeMillis = timeMillis;
        
        glm::vec3 veloc(0, 0, 0);
        bool fast = false;
        auto dir = player->orientation;
        if (keys['w'])
            veloc += dir * glm::vec3(0, 0, -1);

        if (keys['a'])
            veloc += dir * glm::vec3(-1, 0, 0);

        if (keys['s'])
            veloc += dir * glm::vec3(0, 0, 1);

        if (keys['d'])
            veloc += dir * glm::vec3(1, 0, 0);

        if (keys['z'])
            veloc += glm::vec3(0, -1, 0);

        if (keys['q'])
            wrap = !wrap;
        
        if (keys['e'])
            fast = true;

        if (keys[VK_SPACE])
            veloc += glm::vec3(0, 1, 0);

        glm::normalize(veloc);
        veloc *= 0.1;
        player->position += (fast ? veloc * 3.0f : veloc);

        scene->update(elapsedMillis / 1000.0f);
        camera->update(elapsedMillis / 1000.0f);

        glutPostRedisplay();
    }
}