#pragma once

#include <tuple>
#include <string>
#include <iostream>

using namespace std;

class Monster
{
    friend std::ostream &operator<<(std::ostream &stream, const Monster &monster)
    {
        return stream << "Monster: " << monster.id
                      << " | " << get<0>(monster.pos)
                      << " | " << get<1>(monster.pos)
                      << " | " << monster.name
                      << " | " << monster.type
                      << " | " << monster.atk
                      << " | " << monster.def
                      << " | " << monster.hp
                      << " | " << monster.model;
    }

private:
    unsigned int id;
    tuple<unsigned int, unsigned int> pos;
    string name;
    unsigned int type;
    int atk;
    int def;
    int hp;
    string model;

public:
    Monster(const unsigned int id_,
            tuple<unsigned int, unsigned int> pos_,
            const string name_,
            const unsigned int type_,
            const int atk_,
            const int def_,
            const int hp_,
            const string model_) : id{id_},
                                   pos{pos_},
                                   name{name_},
                                   type{type_},
                                   atk{atk_},
                                   def{def_},
                                   hp{hp_},
                                   model{model_}

    {
    }
};
