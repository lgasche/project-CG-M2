#pragma once

#include <tuple>
#include <string>
#include <iostream>

using namespace std;

class Treasure
{
    friend std::ostream &operator<<(std::ostream &stream, const Treasure &treasure)
    {
        return stream << "Treasure: " << treasure.id << " | " << get<0>(treasure.pos) << " | " << get<1>(treasure.pos)
                      << " | " << treasure.name;
    }

private:
    unsigned int id;
    tuple<unsigned int, unsigned int> pos;
    string name;

public:
    Treasure(const unsigned int id_, tuple<unsigned int, unsigned int> pos_, const string name_) : id{id_},
                                                                                                   pos{pos_},
                                                                                                   name{name_}
    {
    }
};