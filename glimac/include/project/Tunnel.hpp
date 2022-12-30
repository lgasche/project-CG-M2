#pragma once

#include <tuple>
#include <string>
#include <iostream>

#include <glimac/glm.hpp>
#include <project/LevelStructure.hpp>

using namespace std;

class Tunnel
{
    friend std::ostream &operator<<(std::ostream &stream, const Tunnel &tunnel)
    {
        return stream << "Tunnel: "
                      << " | " << get<0>(tunnel.pos)
                      << " | " << get<1>(tunnel.pos)
                      << " || " << tunnel.wall_north
                      << " | " << tunnel.wall_east
                      << " | " << tunnel.wall_south
                      << " | " << tunnel.wall_west;
    }


private:
    tuple<unsigned int, unsigned int> pos;
    // Bool for presences.
    bool wall_north;
    bool wall_east;
    bool wall_south;
    bool wall_west;

public:
    Tunnel(const tuple<unsigned int, unsigned int> pos_, const bool wall_north_, const bool wall_east_, const bool wall_south_, const bool wall_west_) : pos{pos_},
                                                                                                                                                         wall_north{wall_north_},
                                                                                                                                                         wall_east{wall_east_},
                                                                                                                                                         wall_south{wall_south_},
                                                                                                                                                         wall_west{wall_west_}

    {
        // TODO init datas textures.
    }

    tuple<unsigned int, unsigned int> get_pos() { return pos; };

    void drawWalls(int vertex, LevelProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
    void drawFloor(int vertex, LevelProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
    void  drawRoof(int vertex, LevelProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
};