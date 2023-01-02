using namespace std;

#include <project/Treasure.hpp>

bool Treasure::action(Player &player)
{
    switch (type)
    {

    case 1: // Argent.
        player.monay(stats);
        std::cout << "Le fric c'est chic." << std::endl;
        return true;

    case 2: // Fiole.
        player.hpIsLife(stats);
        std::cout << "Hp is life.. gloup.. gloup.." << std::endl;
        return true;

    default:
        std::cout << "action Treasure error type : " << type << std::endl;
        return false;
    }
}
