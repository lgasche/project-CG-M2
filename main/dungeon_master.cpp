#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <iterator>

#include <project/Square.hpp>
#include <project/LvlReader.hpp>
#include <project/Camera.hpp>
#include <project/Vertex.hpp>
#include <project/BasicStructure.hpp>
#include <project/Texture.hpp>

using namespace glimac;

// A METTRE DANS LE FICHIER "Tunnel"
void drawWalls(float x, float y, int vertex, BasicProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix, bool wall_west, bool wall_north, bool wall_east, bool wall_south)
{
    glm::mat4 wallMVMatrix;
    // Draw wall
    if (wall_west)
    {
        wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3(x, 0.f, y)); // Translation
        glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glDrawArrays(GL_TRIANGLES, 0, vertex);
    }

    if (wall_east)
    {
        wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3(x + 1.f, 0.f, y + 1.f));         // Translation (décalage de 1 en X et en Y a cause de la rotation)
        wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f)); // Translation * Rotation
        glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glDrawArrays(GL_TRIANGLES, 0, vertex);
    }

    if (wall_north)
    {
        wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3(x + 1.f, 0.f, y));               // Translation (décalage de 1 en X a cause de la rotation)
        wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f)); // Translation * Rotation
        glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glDrawArrays(GL_TRIANGLES, 0, vertex);
    }

    if (wall_south)
    {
        wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3(x, 0.f, y + 1.f));              // Translation (décalage de 1 en X a cause de la rotation)
        wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f)); // Translation * Rotation
        glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glDrawArrays(GL_TRIANGLES, 0, vertex);
    }
}

// A METTRE DANS LE FICHIER "Tunnel"
void drawFloor(float x, float y, int vertex, BasicProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix)
{
    glm::mat4 wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3(x + 0.f, 0.f, y + 1.f)); // Translation
    wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));   // Translation * Rotation
    glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
    glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
    glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
    glDrawArrays(GL_TRIANGLES, 0, vertex);
}

// A METTRE DANS LE FICHIER "Tunnel"
void drawCreature(float x, float y, int vertex, BasicProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix)
{
    glm::mat4 wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3(x + 0.5f, 0.f, y)); // Translation
    wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f));
    glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
    glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
    glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
    glDrawArrays(GL_TRIANGLES, 0, vertex);
}

int main(int argc, char **argv)
{
    // Initialize SDL and open a window
    float widthWindow = 800., heightWindow = 600.;
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

    // Init Lvl.
    std::string filename = argv[1];
    auto read = LvlReader(filename);
    std::cout << read << std::endl;
    auto lvl = read.creat_lvl();
    auto start_camera = lvl.get_start();

    Camera camera((float)get<0>(start_camera), (float)get<1>(start_camera));
    std::cout << "CAMERA : " << (float)get<0>(start_camera) << " " << (float)get<1>(start_camera) << std::endl;
    Vertex vertex;
    Square square;
    Texture texture;

    // Chargement des shaders
    FilePath applicationPath(argv[0]);
    BasicProgram squareProgam(applicationPath);

    glEnable(GL_DEPTH_TEST);
    // Gestion de la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Chargement des textures
    texture.loadWall("../assets/textures/WallMap.png");
    texture.loadCreature("../assets/textures/Creature_1.png");
    texture.loadFloor("../assets/textures/FloorMap.png");

    // VBO - VAO
    vertex.sendData(square.getVertexCount(), square.getDataPointer());
    vertex.indicationVertices();

    // Application loop:
    bool done = false;
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

        if (camera.movementCamera())
        {
            if (windowManager.isKeyPressed(SDLK_a))
                camera.turnLeft(true);
            if (windowManager.isKeyPressed(SDLK_e))
                camera.turnLeft(false);
            if (windowManager.isKeyPressed(SDLK_q))
                camera.moveLeft(true);
            if (windowManager.isKeyPressed(SDLK_d))
                camera.moveLeft(false);
            if (windowManager.isKeyPressed(SDLK_z))
                camera.moveAhead(true);
            if (windowManager.isKeyPressed(SDLK_s))
                camera.moveAhead(false);
        }

        /*
        glm::ivec2 mousePos = glm::ivec2(0.0);
        if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            mousePos = windowManager.getMousePosition();

            //std::cout << mousePos << std::endl;

            float mousePosX = mousePos.x/widthWindow - 0.5;
            float mousePosY = mousePos.y/heightWindow - 0.5;

            //camera.rotateLeft(-2*mousePosX);
            //camera.rotateUp(-2*mousePosY);
        }
        */

        // Nettoyage des buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        squareProgam.mProgram.use();
        glUniform1i(squareProgam.uTexture, 0);

        // Envoie des informations aux shaders
        glm::mat4 globalMVMatrix = camera.getViewMatrix(); // glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
        glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), (widthWindow / heightWindow), 0.1f, 100.f);

        glUniform3f(squareProgam.uKd, 0.3f, 0.3f, 0.3f);       // Intensité de la lumiètre globale
        glUniform3f(squareProgam.uKs, 0.001f, 0.001f, 0.001f); // Intensité du centre lumineux
        glUniform1f(squareProgam.uShininess, 4.f);             // Taille du centre lumineux
        glm::vec4 LightPos = globalMVMatrix * glm::vec4(0.0, 0.0, 0.0, 0.0);
        glUniform3f(squareProgam.uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
        glUniform3f(squareProgam.uLightIntensity, 1.f, 1.f, 1.f);

        vertex.testBindingVAO();

        // Binding des textures
        texture.bindingWallTexture();
        drawWalls(0.f, 0.f, square.getVertexCount(), &squareProgam, globalMVMatrix, projMatrix, true, false, true, false);
        drawWalls(1.f, 0.f, square.getVertexCount(), &squareProgam, globalMVMatrix, projMatrix, true, false, true, false);
        drawWalls(2.f, 0.f, square.getVertexCount(), &squareProgam, globalMVMatrix, projMatrix, true, false, true, false);

        /////////////////////////////////////////////////////////////
        texture.bindingFloorTexture();
        drawFloor(0.f, 0.f, square.getVertexCount(), &squareProgam, globalMVMatrix, projMatrix);
        drawFloor(1.f, 0.f, square.getVertexCount(), &squareProgam, globalMVMatrix, projMatrix);
        drawFloor(2.f, 0.f, square.getVertexCount(), &squareProgam, globalMVMatrix, projMatrix);

        ///////////////////////////////////////////////////////
        texture.bindingCreatureTexture();
        drawCreature(1.f, 0.f, square.getVertexCount(), &squareProgam, globalMVMatrix, projMatrix);

        // Débindind du VAO
        glBindVertexArray(0); // A RETIRER SI JAMAIS LE BINDING EST AILLEURS

        // Débindind de la première textures
        texture.debindingTexture();

        // Update the display
        windowManager.swapBuffers();
    }

    vertex.clearData();
    texture.clearTexture();

    return EXIT_SUCCESS;
}
