#pragma once

#include <tuple>
#include <string>
#include <iostream>

using namespace std;

class Monster
{
    friend std::ostream &operator<<(std::ostream &stream, const Monster &monster)
    {
        return stream << "Treasure: " << monster.id
                      << " | " << get<0>(monster.pos)
                      << " | " << get<1>(monster.pos)
                      << " | " << monster.name;
    }

private:
    unsigned int id;
    tuple<unsigned int, unsigned int> pos;
    string name;

public:
    Monster(const unsigned int id_, tuple<unsigned int, unsigned int> pos_, const string name_) : id{id_},
                                                                                                  pos{pos_},
                                                                                                  name{name_}
    {
    }
};