

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <limits>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "Student.cpp"

class DataValidInput
{
public:
    static void validateId(int id)
    {
        if (id <= 0)
        {
            throw std::invalid_argument("ID must be a positive integer.");
        }
    }
    static std::string getStringInput(const std::string &prompt)
    {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    }

    static int getIntInput(const std::string &prompt)
    {
        int input;
        std::cout << prompt;
        while (!(std::cin >> input))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
    static char getCharInput(const std::string &prompt)
    {
        char input;
        std::cout << prompt;
        while (!(std::cin >> input) || (input != 'Y' && input != 'y' && input != 'N' && input != 'n'))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter 'Y' or 'N': ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
};