#pragma once

#include <tuple>
#include <string>
#include <iostream>

using namespace std;

#include <project/Player.hpp>

class Treasure
{
    friend std::ostream &operator<<(std::ostream &stream, const Treasure &treasure)
    {
        return stream << "Treasure: " << treasure.id
                      << " | " << get<0>(treasure.pos)
                      << " | " << get<1>(treasure.pos)
                      << " | " << treasure.name
                      << " | " << treasure.type
                      << " | " << treasure.stats
                      << " | " << treasure.model;
    }

private:
    unsigned int id;
    tuple<unsigned int, unsigned int> pos;
    string name;
    unsigned int type;
    int stats;
    string model;

public:
    Treasure(const unsigned int id_,
             tuple<unsigned int, unsigned int> pos_,
             const string name_,
             const unsigned int type_,
             const int stats_,
             const string model_) : id{id_},
                                    pos{pos_},
                                    name{name_},
                                    type{type_},
                                    stats{stats_},
                                    model{model_}
    {
    }

    string get_model() { return model; };
    unsigned int get_type() { return type; };
    tuple<unsigned int, unsigned int> getPos() const { return pos; }
    bool action(Player &player);
};