#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "StudentManager.cpp"
#include "DataValidInput.cpp"

class StudentApplication
{
private:
    static void displayMenu()
    {
        std::cout << "\nSTUDENT MANAGER MENU: (Version 1.1.0)\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. View Students\n";
        std::cout << "3. Update Student\n";
        std::cout << "4. Delete Student\n";
        std::cout << "5. Back to Main Menu\n\n";
    }

public:
    static void run()
    {
        StudentManager manager;
        int choice;

        bool done = false;
        while (!done)
        {
            displayMenu();
            choice = DataValidInput::getIntInput("Enter your choice: ");
            std::cout << std::endl;
            try
            {
                switch (choice)
                {
                case 1:
                {
                    bool addMore = true; // Declaration of addMore
                    while (addMore)
                    {
                        std::string name;
                        int id;
                        int type;
                        std::cout << "1. Add Student" << std::endl;
                        id = DataValidInput::getIntInput("Enter student ID: ");
                        name = DataValidInput::getStringInput("Enter student name: ");
                        DataValidInput::validateId(id);
                        type = DataValidInput::getIntInput("Enter 1 for Part-Time, 2 for Full-Time: ");
                        manager.addStudent(id, name, type);

                        // Ask user a question to add more or not
                        char more;
                        more = DataValidInput::getCharInput("Do you want to add more students? (Y/N): ");
                        std::cout << std::endl;

                        if (more == 'N' || more == 'n')
                        {
                            addMore = false;
                        }
                    }

                    break;
                }
                case 2:
                    manager.viewStudents();
                    break;
                case 3:
                {
                    int id;
                    std::cout << "3. Update Student" << std::endl;
                    std::cout << "Who do you want to update?\n";
                    id = DataValidInput::getIntInput("Please enter student ID: ");
                    DataValidInput::validateId(id);

                    manager.updateStudent(id);
                    break;
                }
                case 4:
                {
                    int id;
                    std::cout << "4. Delete Student" << std::endl;
                    std::cout << "Who do you want to delete?\n";
                    id = DataValidInput::getIntInput("Enter student ID: ");
                    DataValidInput::validateId(id);

                    manager.deleteStudent(id);
                    break;
                }
                case 5:
                    done = true;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
};
