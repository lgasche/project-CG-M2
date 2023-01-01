#pragma once

#include <tuple>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

#include "Weapon.hpp"

class Player
{
    friend std::ostream &operator<<(std::ostream &stream, const Player &player)
    {
        return stream << "Player: " << player.id
                      << " | " << get<0>(player.pos)
                      << " | " << get<1>(player.pos)
                      << " | " << player.name
                      << " | " << player.type
                      << " | " << player.atk
                      << " | " << player.def
                      << " | " << player.hp
                      << " | " << player.model;
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
    unique_ptr<Weapon> weapon;
    int golds = 0;

public:
    Player(const unsigned int id_,
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
        weapon = NULL;
    }
};