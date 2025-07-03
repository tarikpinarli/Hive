#include "Weapon.hpp"

const string& Weapon::getType() const{
    return this->type;
}

void Weapon::setType(string newType) {
    this->type = newType;
}

Weapon::Weapon(string Weapon) {
    this->type = Weapon;
}
