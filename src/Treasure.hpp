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
    ulong id;
    tuple<ulong, ulong> pos;
    string name;

public:
    Treasure(const ulong id_, tuple<ulong, ulong> pos_, const string name_) : id{id_},
                                                                              pos{pos_},
                                                                              name{name_}
    {
    }
};