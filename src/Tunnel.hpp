#pragma once

#include <tuple>
#include <string>
#include <iostream>

using namespace std;

class Tunnel
{
    friend std::ostream &operator<<(std::ostream &stream, const Tunnel &tunnel)
    {
        return stream << "Tunnel: "
                      << " | " << get<0>(tunnel.pos)
                      << " | " << get<1>(tunnel.pos);
    }

private:
    tuple<unsigned int, unsigned int> pos;
    // Bool for presences.
    bool wall_north;
    bool wall_east;
    bool wall_west;
    bool wall_south;
    // Datas for textures.
    Wall wall;
    Floor floor;
    Roof roof;

public:
    Tunnel(const tuple<unsigned int, unsigned int> pos_, const bool wall_north_, const bool wall_east_, const bool wall_west_, const bool wall_south_) : pos{pos_},
                                                                                                                                                         wall_north{wall_north_},
                                                                                                                                                         wall_east{wall_east_},
                                                                                                                                                         wall_west{wall_west_},
                                                                                                                                                         wall_south{wall_south_}
    {
        // TODO init datas textures.
    }

    tuple<unsigned int, unsigned int> get_pos() { return pos; };
};