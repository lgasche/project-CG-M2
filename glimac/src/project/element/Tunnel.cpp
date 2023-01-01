#include <project/element/Tunnel.hpp>

glm::mat4 Tunnel::drawNorthWall(glm::mat4 globalMVMatrix)
{
    matrix = glm::translate(globalMVMatrix, glm::vec3((float)get<0>(pos), 0.f, (float)get<1>(pos) + 1.f)); // Translation (décalage de 1 en X a cause de la rotation)
    matrix = glm::rotate(matrix, glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));                      // Translation * Rotation
    return matrix;
}

glm::mat4 Tunnel::drawEastWall(glm::mat4 globalMVMatrix)
{
    matrix = glm::translate(globalMVMatrix, glm::vec3((float)get<0>(pos) + 1.f, 0.f, (float)get<1>(pos) + 1.f)); // Translation (décalage de 1 en X et en Y a cause de la rotation)
    matrix = glm::rotate(matrix, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));                           // Translation * Rotation
    return matrix;
}


glm::mat4 Tunnel::drawSouthWall(glm::mat4 globalMVMatrix)
{
    matrix = glm::translate(globalMVMatrix, glm::vec3((float)get<0>(pos) + 1.f, 0.f, (float)get<1>(pos))); // Translation (décalage de 1 en X a cause de la rotation)
    matrix = glm::rotate(matrix, glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f));                     // Translation * Rotation
    return matrix;
}


glm::mat4 Tunnel::drawWestWall(glm::mat4 globalMVMatrix)
{
    matrix = glm::translate(globalMVMatrix, glm::vec3((float)get<0>(pos), 0.f, (float)get<1>(pos))); // Translation
    return matrix;
}


glm::mat4 Tunnel::drawFloor(glm::mat4 globalMVMatrix)
{
    matrix = glm::translate(globalMVMatrix, glm::vec3(get<0>(pos), 0.f, get<1>(pos) + 1.f)); // Translation
    matrix = glm::rotate(matrix, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));                // Translation * Rotation
    return matrix;
}

glm::mat4 Tunnel::drawRoof(glm::mat4 globalMVMatrix)
{
    matrix = glm::translate(globalMVMatrix, glm::vec3(get<0>(pos), 1.f, get<1>(pos))); // Translation
    matrix = glm::rotate(matrix, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));            // Translation * Rotation
    return matrix;
}
