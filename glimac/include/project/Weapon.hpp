#pragma once

#include <tuple>
#include <string>
#include <iostream>

using namespace std;

class Player;

class Weapon
{
    friend std::ostream &operator<<(std::ostream &stream, const Weapon &weapon)
    {
        return stream << "Weapon: " << weapon.id
                      << " | " << get<0>(weapon.pos)
                      << " | " << get<1>(weapon.pos)
                      << " | " << weapon.name
                      << " | " << weapon.type
                      << " | " << weapon.atk
                      << " | " << weapon.def
                      << " | " << weapon.model;
    }

private:
    unsigned int id;
    tuple<unsigned int, unsigned int> pos;
    string name;
    unsigned int type;
    int atk;
    int def;
    string model;

public:
    // Weapon(const Weapon &) = delete;
    Weapon(const unsigned int id_,
           tuple<unsigned int, unsigned int> pos_,
           const string name_,
           const unsigned int type_,
           const int atk_,
           const int def_,
           const string model_) : id{id_},
                                  pos{pos_},
                                  name{name_},
                                  type{type_},
                                  atk{atk_},
                                  def{def_},
                                  model{model_}

    {
    }

    string get_model() { return model; };
    unsigned int get_type() { return type; };
    tuple<unsigned int, unsigned int> getPos() const { return pos; }
    bool action(Player &player);
    int getAtk() const { return atk; }
    int getDef() const { return def; }
};
