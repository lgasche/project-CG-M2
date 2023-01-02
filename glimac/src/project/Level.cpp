#include <project/Level.hpp>

void Level::drawLevel(int squareVertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glm::vec3 playerPos)
{
    tunnelStorage.drawTunnels(squareVertex, globalMVMatrix, projMatrix, out);
    progam.mProgram.use();
    drawEntity(squareVertex, globalMVMatrix, projMatrix, playerPos, treasureStorages);
    drawEntity(squareVertex, globalMVMatrix, projMatrix, playerPos, weaponStorage);
    drawEntity(squareVertex, globalMVMatrix, projMatrix, playerPos, monsterStorage);
}

void Level::clear()
{
    tunnelStorage.clear();
}

bool Level::canMove(std::tuple<unsigned int, unsigned int> pos)
{
    // std::cout << get<0>(pos) << " " << get<1>(pos) << std::endl;
    if (!tunnelStorage.canMove(pos))
        return false;
    return true;
}

template <typename Item>
bool browseStorage(std::tuple<unsigned int, unsigned int> pos, map<unsigned int, Storage<Item>> &storages, Player &player)
{
    for (auto it = storages.begin(); it != storages.end(); it++)
    {
        auto &storage = it->second;
        if (storage.triggerAction(pos, player))
            return true;
    }
    return false;
}

/**
 * Action on clic.
 *
 * @param camera
 */
void Level::action(Camera camera)
{
    auto targetPosition = camera.prediction(HighMiddle);
    if (browseStorage(targetPosition, treasureStorages, player) || browseStorage(targetPosition, weaponStorage, player) || browseStorage(targetPosition, monsterStorage, player))
    {
        std::cout << "Tu es sorcier harry" << std::endl;
    }
    std::cout << player << std::endl;
}
