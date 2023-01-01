#pragma once

#include <iostream>
#include <map>
#include <memory>

using namespace std;

#include <project/Treasure.hpp>
#include <project/Weapon.hpp>
#include <project/Monster.hpp>
#include <project/TunnelStorage.hpp>
#include <project/Texture.hpp>
#include <project/Square.hpp>
#include <project/LevelStructure.hpp>

class Level
{
    friend std::ostream &operator<<(std::ostream &stream, const Level &lvl)
    {
        return stream;
    }

public:
    Level(const map<tuple<unsigned int, unsigned int>, Tunnel> map_lvl_,
          map<tuple<unsigned int, unsigned int>, Treasure> treasures_,
          map<tuple<unsigned int, unsigned int>, Monster> monsters_,
          tuple<unsigned int, unsigned int> start_,
          tuple<unsigned int, unsigned int> out_,
          const FilePath &applicationPath) : treasures{treasures_},
                                             monsters{monsters_},
                                             start{start_},
                                             out{out_}
    {
        tunnelStorage = TunnelStorage(map_lvl_, applicationPath);
        // Chargement des textures
        // textureWall.loadTexture("../assets/textures/Wall_1.png");
        // textureRoof.loadTexture("../assets/textures/Roof_1.png");
        // textureFloor.loadTexture("../assets/textures/Floor_1.png");
        textureCreature.loadTexture("../assets/textures/Creature_1.png");
    }

    tuple<unsigned int, unsigned int> get_start() { return start; }

    void clear();
    void drawLevel(int squareVertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);

private:
    TunnelStorage tunnelStorage;
    // map<tuple<unsigned int, unsigned int>, Tunnel> map_lvl;

    map<tuple<unsigned int, unsigned int>, Treasure> treasures;

    map<tuple<unsigned int, unsigned int>, unique_ptr<Weapon>> weapons;

    map<tuple<unsigned int, unsigned int>, Monster> monsters;

    tuple<unsigned int, unsigned int> start; // Start coordinate.
    tuple<unsigned int, unsigned int> out;   // Exit coordinate.

    ////////////////////////////
    // Texture textureWall;
    // Texture textureRoof;
    // Texture textureFloor;
    Texture textureCreature;

    // LevelProgram squareProgam;
};