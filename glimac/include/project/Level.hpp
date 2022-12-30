#pragma once

#include <iostream>
#include <map>
#include <memory>

using namespace std;

#include <project/Treasure.hpp>
#include <project/Monster.hpp>
#include <project/Tunnel.hpp>
#include <project/Texture.hpp>
#include <project/Square.hpp>

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
              tuple<unsigned int, unsigned int> start_, const FilePath& applicationPath) : map_lvl{map_lvl_},
                                                                                           treasures{treasures_},
                                                                                           monsters{monsters_},
                                                                                           start{start_}
    {   
        squareProgam.loadBasicProgram(applicationPath);
        // Chargement des textures
        textureWall.loadTexture("../assets/textures/Wall_1.png");
        textureRoof.loadTexture("../assets/textures/Roof_1.png");
        textureFloor.loadTexture("../assets/textures/Floor_1.png");
        textureCreature.loadTexture("../assets/textures/Creature_1.png");
    }

    tuple<unsigned int, unsigned int> get_start() { return start; }

    void clear();
    void addLight(glm::mat4 globalMVMatrix);
    void drawLevel(int squareVertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);

private:
    map<tuple<unsigned int, unsigned int>, Tunnel> map_lvl;
    int nb_treasures;

    map<tuple<unsigned int, unsigned int>, Treasure> treasures;
    int nb_monsters;

    map<tuple<unsigned int, unsigned int>, Monster> monsters;

    tuple<unsigned int, unsigned int> start;

    ////////////////////////////
    Texture textureWall;
    Texture textureRoof;
    Texture textureFloor;
    Texture textureCreature;

    LevelProgram squareProgam;

};