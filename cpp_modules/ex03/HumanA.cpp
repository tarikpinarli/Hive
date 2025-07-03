#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& weapon)
    : weapon(weapon)
{
    this->name = name;
}

void HumanA::attack() const{
    cout << this->name << " attacks with their " << this->weapon.getType() << endl;
}
