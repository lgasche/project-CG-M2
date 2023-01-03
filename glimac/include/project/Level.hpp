#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <tuple>

using namespace std;

#include <project/Treasure.hpp>
#include <project/Weapon.hpp>
#include <project/Monster.hpp>
#include <project/TunnelStorage.hpp>
#include <project/Storage.hpp>
#include <project/Texture.hpp>
#include <project/Square.hpp>
#include <project/ATH.hpp>
#include <project/Camera.hpp>
#include <project/Player.hpp>

class Level
{
    friend std::ostream &operator<<(std::ostream &stream, const Level &lvl)
    {
        return stream;
    }

public:
    Level(const map<tuple<unsigned int, unsigned int>, Tunnel> map_lvl_,
          map<unsigned int, Storage<Treasure>> treasureStorages_,
          map<unsigned int, Storage<Weapon>> weaponStorage_,
          map<unsigned int, Storage<Monster>> monsterStorage_,
          tuple<unsigned int, unsigned int> start_,
          tuple<unsigned int, unsigned int> out_,
          const FilePath &applicationPath) : treasureStorages{treasureStorages_},
                                             weaponStorage{weaponStorage_},
                                             monsterStorage{monsterStorage_},
                                             start{start_},
                                             out{out_}
    {
        tunnelStorage = TunnelStorage(map_lvl_, applicationPath);
        progam.loadBasicProgram(applicationPath);
    }

    tuple<unsigned int, unsigned int> get_start() { return start; };

    void clear();
    void drawLevel(int squareVertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glm::vec3 playerPos);
    bool canMove(std::tuple<unsigned int, unsigned int> pos);

    void action(Camera camera);

private:
    TunnelStorage tunnelStorage;
    map<unsigned int, Storage<Treasure>> treasureStorages;
    map<unsigned int, Storage<Weapon>> weaponStorage;
    map<unsigned int, Storage<Monster>> monsterStorage;

    tuple<unsigned int, unsigned int> start;    // Start coordinate.
    tuple<unsigned int, unsigned int> out;      // Exit coordinate.

    Player player{20, 10, 10};

    LevelProgram progam;

    template <typename Item>
    void drawEntity(int squareVertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glm::vec3 playerPos, map<unsigned int, Storage<Item>> storage)
    {
        for (auto &pair : storage)
        {
            pair.second.drawEntity(squareVertex, globalMVMatrix, projMatrix, std::make_tuple(playerPos.x, playerPos.z), progam);
        }
    }
};