#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "Student.cpp"
#include "DataValidInput.cpp"
#include "StudentRepository.cpp"

class StudentManager : public StudentRepository
{
private:
    std::vector<Student *> students;

    Student *findStudentById(int id)
    {
        auto it = std::find_if(students.begin(), students.end(), [id](Student *student)
                               { return student->id == id; });
        return (it != students.end()) ? *it : nullptr;
    }

    // add test
    //  Function to print header
    void printHeader() const
    {
        const int width = 20; // Adjust this value as needed for proper spacing
        std::cout << std::left << std::setw(width) << "Name"
                  << std::left << std::setw(width) << "ID"
                  << std::left << std::setw(width) << "Type"
                  << std::endl;
    }

public:
    ~StudentManager()
    {
        for (auto student : students)
        {
            delete student;
        }
    }

    void addStudent(int id, std::string name, int type)
    {

        if (type == 1)
        {
            students.push_back(new PartTimeStudent(name, id));
        }
        else if (type == 2)
        {
            students.push_back(new FullTimeStudent(name, id));
        }
        else
        {
            throw std::invalid_argument("Invalid student type.");
        }

        std::cout << "Student added successfully__\n";
        std::cout << std::endl;
    }

    void updateStudent(int id)
    {
        Student *student = findStudentById(id);
        if (student == nullptr)
        {
            throw std::invalid_argument("Student not found");
            return;
        }

        printHeader();
        student->display();
        std::cout << std::endl;
        std::cout << "Which type do you want to update?\n";
        std::cout << "1. Update ID\n";
        std::cout << "2. Update name\n";
        std::cout << "3. Update Time\n";
        std::cout << "Please choose option you want to update 1-3: ";
        std::cout << std::endl;
        int choice = DataValidInput::getIntInput("");

        switch (choice)
        {
        case 1:
        {
            int newId;
            std::cout << "1. Update ID\n";
            std::cout << "Enter new ID: ";
            newId = DataValidInput::getIntInput("");
            DataValidInput::validateId(newId);
            student->id = newId;
            break;
        }
        case 2:
        {
            std::string newName;
            std::cout << "2. UPDATE NAME\n";
            std::cout << "Enter new name: ";
            newName = DataValidInput::getStringInput("");
            student->name = newName;
            break;
        }
        case 3:
        {
            int newType;
            std::cout << "3. UPDATE Time\n";
            std::cout << "Enter 1 for Part-Time, 2 for Full-Time: ";
            newType = DataValidInput::getIntInput("");

            if (newType == 1)
            {
                student = new PartTimeStudent(student->name, student->id);
            }
            else if (newType == 2)
            {
                student = new FullTimeStudent(student->name, student->id);
            }
            else
            {
                throw std::invalid_argument("Invalid student time.");
            }
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        std::cout << "Student updated successfully___\n";
    }

    void deleteStudent(int id)
    {
        Student *student = findStudentById(id);
        if (student == nullptr)
        {
            throw std::invalid_argument("Student not found");
        }

        printHeader();
        student->display(); // Display student details before confirming deletion
        std::cout << std::endl;
        char confirm = DataValidInput::getCharInput("Are you sure you want to delete this student? (Y/N): ");

        if (confirm == 'Y' || confirm == 'y')
        {
            auto it = std::remove_if(students.begin(), students.end(), [id](Student *student)
                                     {
            if (student->id == id) {
                delete student;
                return true;
            }
            return false; });

            if (it != students.end())
            {
                students.erase(it, students.end());
                std::cout << "Student has been successfully deleted.\n";
            }
            else
            {
                throw std::invalid_argument("Student not found");
            }
        }
        else
        {
            std::cout << "Delete student has been canceled.\n";
        }
    }

    void viewStudents()
    {
        if (students.empty())
        {
            throw std::invalid_argument("No student available");
            return;
        }

        printHeader(); // Print the header once
        for (const auto &student : students)
        {
            student->display();
        }
    }
};