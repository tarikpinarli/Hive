#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
    cout << GREEN << endl;
    {
        Weapon sword = Weapon("sword");
        HumanA bob("Bob", sword);
        bob.attack();
        sword.setType("knife");
        bob.attack();
    }
    cout << BLUE << endl;
    {
        Weapon bow = Weapon("bow");
        HumanB jim("Jim");
        jim.setWeapon(bow);
        jim.attack();
        bow.setType("gun");
        jim.attack();
    }
    cout << RED << endl;
    {
        Weapon axe = Weapon("axe");
        HumanB Jon("Jon");
        Jon.attack();
        Jon.setWeapon(axe);
        Jon.attack();
        axe.setType("stick");
        Jon.attack();
    }
    cout << RESET << endl;
    return 0;
}

