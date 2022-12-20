#pragma once

#include <tuple>
#include <string>
#include <iostream>

using namespace std;

class Treasure
{
    friend std::ostream &operator<<(std::ostream &stream, const Treasure &treasure)
    {
        return stream << "Treasure: " << treasure.id
                      << " | " << get<0>(treasure.pos)
                      << " | " << get<1>(treasure.pos)
                      << " | " << treasure.name
                      << " | " << treasure.type_id;
    }

private:
    unsigned int id;
    tuple<unsigned int, unsigned int> pos;
    string name;
    int type_id;

public:
    Treasure(const unsigned int id_, tuple<unsigned int, unsigned int> pos_, const string name_, const int type_id_) : id{id_},
                                                                                                                       pos{pos_},
                                                                                                                       name{name_},
                                                                                                                       type_id{type_id_}
    {
    }

    tuple<unsigned int, unsigned int> get_pos() { return pos; };
};