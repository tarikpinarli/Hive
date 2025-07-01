#include <iostream>
#include <string>
#include "PhoneBook.hpp"

int main() {
    PhoneBook phonebook;
    std::string command;

    std::cout << "Welcome to My Awesome PhoneBook!" << std::endl;
    std::cout << "Type ADD, SEARCH, or EXIT" << std::endl;

    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, command);

        if (std::cin.eof()) {
            std::cout << "\nExiting...\n";
            break;
        }

        if (command == "ADD") {
            phonebook.addContact();
        } else if (command == "SEARCH") {
            phonebook.searchContacts();
        } else if (command == "EXIT") {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown command. Use ADD, SEARCH, or EXIT." << std::endl;
        }
    }
    return 0;
}
