#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <iterator>

//#include <project/Square.hpp>
#include <project/LvlReader.hpp>
#include <project/Camera.hpp>
#include <project/Vertex.hpp>
#include <project/ATHStructure.hpp>

using namespace glimac;


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
    auto read = LvlReader(filename);
    std::cout << read << std::endl;
    auto lvl = read.creat_lvl(applicationPath);
    auto start_camera = lvl.get_start();

    //Camera camera((float)get<0>(start_camera), (float)get<1>(start_camera));
    std::cout << "CAMERA : " << (float)get<0>(start_camera) << " " << (float)get<1>(start_camera) << std::endl;

    Camera camera(0.f, 2.f);
    Vertex vertex;
    Texture texture;
    Square square;

    ATHProgram athProgram(applicationPath);

    glEnable(GL_DEPTH_TEST);
    // Gestion de la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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

        if(camera.movementCamera()) {
            if(windowManager.isKeyPressed(SDLK_a)) camera.turnLeft(true);      
            if(windowManager.isKeyPressed(SDLK_e)) camera.turnLeft(false);
            if(windowManager.isKeyPressed(SDLK_q)) camera.moveLeft(true);
            if(windowManager.isKeyPressed(SDLK_d)) camera.moveLeft(false);
            if(windowManager.isKeyPressed(SDLK_z)) camera.moveAhead(true);
            if(windowManager.isKeyPressed(SDLK_s)) camera.moveAhead(false);
        } 

        if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            auto mousePos = windowManager.getMousePosition();

            if(mousePos.x > widthWindow * (2.f / 3.f))
            std::cout << mousePos << std::endl;

            //camera.rotateLeft(-2*mousePosX);
            //camera.rotateUp(-2*mousePosY);
        }

        // Nettoyage des buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::mat4 globalMVMatrix = camera.getViewMatrix();
        glm::mat4 projMatrix = glm::perspective(glm::radians(90.f), (widthWindow / heightWindow), 0.1f, 3.f);
        // Ajustement de la caméra pour l'ATH

        
        vertex.bindingVAO();

        lvl.drawLevel(square.getVertexCount(), globalMVMatrix, projMatrix);

        vertex.debindingVAO();

        // Débindind de la texture principale 
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0     

        //// TEST ATH
        /*
        athProgram.mProgram.use();
        glUniform1i(athProgram.uTexture, 0);

        texture.bindingFloorTexture();
        glm::mat4 wallMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0.4f, -0.5f, -0.325f));
        wallMVMatrix = glm::scale(wallMVMatrix,     glm::vec3(0.5, 1.f, 1.f));
        //wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f));
        glUniformMatrix4fv(athProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(athProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(athProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        
        glDrawArrays(GL_TRIANGLES, 0, square.getVertexCount());
    */  

        // Update the display
        windowManager.swapBuffers();
    }

    vertex.clearData();
    lvl.clear();

    return EXIT_SUCCESS;
}
