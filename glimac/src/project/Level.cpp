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
    for (auto it = treasureStorages.begin(); it != treasureStorages.end(); it++) { it->second.clear(); }
    for (auto it = weaponStorage.begin(); it != weaponStorage.end(); it++)       { it->second.clear(); }
    for (auto it = monsterStorage.begin(); it != monsterStorage.end(); it++)     { it->second.clear(); }
}

bool Level::canMove(std::tuple<unsigned int, unsigned int> pos)
{
    
    if (!tunnelStorage.canMove(pos))
        return false;

    for (auto it = treasureStorages.begin(); it != treasureStorages.end(); it++)
    {
        if(!it->second.canMove(pos)) return false;
    }
    for (auto it = weaponStorage.begin(); it != weaponStorage.end(); it++)
    {
        if(!it->second.canMove(pos)) return false;
    }
    for (auto it = monsterStorage.begin(); it != monsterStorage.end(); it++)
    {
        if(!it->second.canMove(pos)) return false;
    }
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
