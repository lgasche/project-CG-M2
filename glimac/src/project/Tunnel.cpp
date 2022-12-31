#include <project/Tunnel.hpp>

void Tunnel::drawWalls(int vertex, LevelProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix)
{
    glm::mat4 wallMVMatrix;
    // Draw wall
    if (wall_west)
    {
        wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)get<0>(pos), 0.f, (float)get<1>(pos))); // Translation
        glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glDrawArrays(GL_TRIANGLES, 0, vertex);
    }

    if (wall_east)
    {
        wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)get<0>(pos) + 1.f, 0.f, (float)get<1>(pos) + 1.f)); // Translation (décalage de 1 en X et en Y a cause de la rotation)
        wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));                           // Translation * Rotation
        glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glDrawArrays(GL_TRIANGLES, 0, vertex);
    }

    if (wall_south)
    {
        wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)get<0>(pos) + 1.f, 0.f, (float)get<1>(pos))); // Translation (décalage de 1 en X a cause de la rotation)
        wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f));                     // Translation * Rotation
        glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glDrawArrays(GL_TRIANGLES, 0, vertex);
    }

    if (wall_north)
    {
        wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)get<0>(pos), 0.f, (float)get<1>(pos) + 1.f)); // Translation (décalage de 1 en X a cause de la rotation)
        wallMVMatrix = glm::rotate(wallMVMatrix, glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));                      // Translation * Rotation
        glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glDrawArrays(GL_TRIANGLES, 0, vertex);
    }
}

void Tunnel::drawFloor(int vertex, LevelProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix)
{
    glm::mat4 floorMVMatrix = glm::translate(globalMVMatrix, glm::vec3(get<0>(pos), 0.f, get<1>(pos) + 1.f)); // Translation
    floorMVMatrix = glm::rotate(floorMVMatrix, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));                // Translation * Rotation
    glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * floorMVMatrix));
    glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(floorMVMatrix));
    glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(floorMVMatrix))));
    glDrawArrays(GL_TRIANGLES, 0, vertex);
}

void Tunnel::drawRoof(int vertex, LevelProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix)
{
    glm::mat4 roofMVMatrix = glm::translate(globalMVMatrix, glm::vec3(get<0>(pos), 1.f, get<1>(pos))); // Translation
    roofMVMatrix = glm::rotate(roofMVMatrix, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));            // Translation * Rotation
    glUniformMatrix4fv(squareProgam->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * roofMVMatrix));
    glUniformMatrix4fv(squareProgam->uMVMatrix, 1, GL_FALSE, glm::value_ptr(roofMVMatrix));
    glUniformMatrix4fv(squareProgam->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(roofMVMatrix))));
    glDrawArrays(GL_TRIANGLES, 0, vertex);
}
