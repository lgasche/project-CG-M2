#include <project/Weapon.hpp>
#include <project/Player.hpp>

bool Weapon::action(Player &player)
{
    player.equip(make_unique<Weapon>(*this));
    std::cout << "Weapon equip." << std::endl;
    return true;
}
