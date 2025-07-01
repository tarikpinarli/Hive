#include <iostream>
#include <limits>
#include "PhoneBook.hpp"

PhoneBook::PhoneBook() {
    count = 0;
    index = 0;
}

void PhoneBook::addContact() {
    if (index >= 8)
        index = 0;

    contacts[index].setContact();

    if (count < 8)
        count++;

    index++;
    std::cout << "Contact saved!\n";
}

void PhoneBook::searchContacts() const {
    if (count == 0) {
        std::cout << "No contacts to show.\n";
        return;
    }

    std::cout << "|     Index|First Name| Last Name|  Nickname|\n";
    std::cout << "--------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        contacts[i].displaySummary(i);
    }

    std::cout << "Enter index to view details (0 to " << count - 1 << "): ";
    int choice;
    std::cin >> choice;

    if (std::cin.fail() || choice < 0 || choice >= count) {
        std::cout << "Invalid index.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore();
    contacts[choice].displayDetails();
}
