#include <iostream>
#include <iomanip>
#include "Contact.hpp"

void Contact::setContact() {
    std::cout << "Enter First Name: ";
    std::getline(std::cin, firstName);
    std::cout << "Enter Last Name: ";
    std::getline(std::cin, lastName);
    std::cout << "Enter Nickname: ";
    std::getline(std::cin, nickname);
    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, phoneNumber);
    std::cout << "Enter Darkest Secret: ";
    std::getline(std::cin, darkestSecret);
}

static std::string format(const std::string &s) {
    return s.length() > 10 ? s.substr(0, 9) + "." : s;
}

void Contact::displaySummary(int index) const {
    std::cout << "|" << std::setw(10) << index
              << "|" << std::setw(10) << format(firstName)
              << "|" << std::setw(10) << format(lastName)
              << "|" << std::setw(10) << format(nickname)
              << "|" << std::endl;
}

void Contact::displayDetails() const {
    std::cout << "First Name: " << firstName << std::endl;
    std::cout << "Last Name: " << lastName << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone Number: " << phoneNumber << std::endl;
    std::cout << "Darkest Secret: " << darkestSecret << std::endl;
}
