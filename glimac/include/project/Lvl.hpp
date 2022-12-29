#pragma once

#include <iostream>
#include <map>
#include <memory>

using namespace std;

#include "Treasure.hpp"

class Lvl
{
    friend std::ostream &operator<<(std::ostream &stream, const Lvl &lvl)
    {
        return stream;
    }

public:
    // Todo add 2 other map.
    Lvl(const map<tuple<unsigned int, unsigned int>, unique_ptr<Treasure>> treasures_) : treasures{treasures_}
    {
    }

private:
    int nb_treasures;
    map<tuple<unsigned int, unsigned int>, unique_ptr<Treasure>> treasures;
    int nb_monsters;
    // map<tuple<unsigned int, unsigned int>, Monster> monsters;
    // map<tuple<unsigned int, unsigned int>, unique_ptr<Deco>> map;
};