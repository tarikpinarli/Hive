#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB {
private:
    string name;
    Weapon* weapon;
public:
    HumanB(string name);
    void setWeapon(Weapon& weapon);
    void attack() const;
};
#endif
