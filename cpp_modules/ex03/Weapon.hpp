#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <string>

#define RED   "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE  "\033[0;34m"
#define RESET "\033[0m"

using std::string;
using std::endl;
using std::cout;

class Weapon {
private:
    string type;
public:
    Weapon(string WeaponType);
    const string& getType() const;
    void    setType(string newType);
};

#endif
