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
        stream << "Player: "
               << " | " << player.atk
               << " | " << player.def
               << " | " << player.hp
               << " | " << player.golds;
        if (player.weapon != nullptr)
            stream << " | " << *player.weapon;
        return stream;
    }

private:
    int atk;
    int def;
    int hp;
    unique_ptr<Weapon> weapon;
    int golds = 0;

public:
    Player(const int atk_,
           const int def_,
           const int hp_) : atk{atk_},
                            def{def_},
                            hp{hp_}
    {
        weapon = nullptr;
    }

    void equip(unique_ptr<Weapon> weapon_)
    {
        weapon = move(weapon_);
    }

    void monay(int golds_) { golds += golds_; }
    void hpIsLife(int hp_) { hp += hp_; }
    int attack() const { return atk + (weapon != nullptr ? weapon->getAtk() : 0); }
    void damage(int dmgTaken)
    {
        auto dmg = max(dmgTaken - def - (weapon != nullptr ? weapon->getDef() : 0), 0);
        hp -= dmg;
    }
};