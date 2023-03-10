#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <iterator>

#include <project/LevelReader.hpp>
#include <project/Camera.hpp>
#include <project/Vertex.hpp>
#include <project/ATH.hpp>

using namespace glimac;

#define TIME_ACTION 0.5f

int main(int argc, char **argv)
{
    // Initialize SDL and open a window
    float heightWindow = 650.f;
    float widthWindow = heightWindow + (heightWindow / 2.f);
    SDLWindowManager windowManager(widthWindow, heightWindow, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);

    // Init Lvl.
    std::string filename = argv[1];
    auto read = LevelReader(filename);
    std::cout << read << std::endl;
    auto level = read.creat_lvl(applicationPath);
    auto start_camera = level.get_start();

    Camera camera((float)get<0>(start_camera), (float)get<1>(start_camera));
    std::cout << "CAMERA : " << (float)get<0>(start_camera) << " " << (float)get<1>(start_camera) << std::endl;

    Vertex vertex;
    Texture texture;
    Square square;
    ATH ath(applicationPath);

    glEnable(GL_DEPTH_TEST);
    // Gestion de la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // VBO - VAO
    vertex.sendData(square.getVertexCount(), square.getDataPointer());
    vertex.indicationVertices();

    ATHBouton boutonValue;

    // Application loop:
    bool done = false;
    float time = windowManager.getTime();
    while (!done)
    {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true; // Leave the loop after this iteration
            }
        }

        // Detection of the click and update camera
        ath.update(camera.update());
        if (camera.movementCamera() && windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT))
        {
            boutonValue = ath.clickCoordinate(windowManager.getMousePosition(), widthWindow, heightWindow);
            if (level.canMove(camera.prediction(boutonValue)))
            {
                switch (boutonValue)
                {
                case HighLeft: camera.turnLeft(true); break;
                case HighMiddle: camera.moveAhead(true);break;
                case HighRight: camera.turnLeft(false); break;
                case LowLeft: camera.moveLeft(true); break;
                case LowMiddle: camera.moveAhead(false); break;
                case LowRight: camera.moveLeft(false); break;
                case Base:
                    if ((windowManager.getTime() - time) >= TIME_ACTION)
                    {
                        level.action(camera);
                        time = windowManager.getTime();
                    } break;
                }
            }
        }

        // Nettoyage des buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 globalMVMatrix = camera.getViewMatrix();
        glm::mat4 projMatrix = glm::perspective(glm::radians(90.f), (widthWindow / heightWindow), 0.1f, 100.f);
        // Ajustement de la cam??ra pour l'ATH
        glViewport(-(widthWindow - heightWindow) / 2.f, 0.f, widthWindow, heightWindow);

        vertex.bindingVAO();

        // LEVEL
        level.drawLevel(square.getVertexCount(), globalMVMatrix, projMatrix, camera.getPosition());
        // Correction de la cam??ra pour draw l'ATH
        glViewport(0.f, 0.f, widthWindow, heightWindow);
        // ATH
        ath.drawATH(square.getVertexCount(), projMatrix);

        vertex.debindingVAO();

        // D??bindind de la texture principale
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); // d??bind sur l'unit?? GL_TEXTURE0
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0); // d??bind sur l'unit?? GL_TEXTURE1

        // Update the display
        windowManager.swapBuffers();
    }

    vertex.clearData();
    level.clear();
    ath.clear();

    return EXIT_SUCCESS;
}
