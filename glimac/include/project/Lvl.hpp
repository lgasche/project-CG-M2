#pragma once

#include <iostream>
#include <map>
#include <memory>

using namespace std;

#include <project/Treasure.hpp>
#include <project/Monster.hpp>
#include <project/Tunnel.hpp>
#include <project/Texture.hpp>
#include <project/Vertex.hpp>
#include <project/Square.hpp>

class Lvl
{
    friend std::ostream &operator<<(std::ostream &stream, const Lvl &lvl)
    {
        return stream;
    }

public:
    Lvl(const map<tuple<unsigned int, unsigned int>, Tunnel> map_lvl_,
              map<tuple<unsigned int, unsigned int>, Treasure> treasures_,
              map<tuple<unsigned int, unsigned int>, Monster> monsters_,
              tuple<unsigned int, unsigned int> start_) : map_lvl{map_lvl_},
                                                          treasures{treasures_},
                                                          monsters{monsters_},
                                                          start{start_}
    {
    }

    tuple<unsigned int, unsigned int> get_start() { return start; }

    void clear();
    void drawLevel(BasicProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
    void initialization();

private:
    map<tuple<unsigned int, unsigned int>, Tunnel> map_lvl;
    int nb_treasures;

    map<tuple<unsigned int, unsigned int>, Treasure> treasures;
    int nb_monsters;

    map<tuple<unsigned int, unsigned int>, Monster> monsters;

    tuple<unsigned int, unsigned int> start;
    ////////////////////////////
    Texture texture;
    Vertex vertex;
    Square square;

};