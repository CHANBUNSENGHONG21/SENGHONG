#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "ShortCourse.cpp"
#include "FullCourse.cpp"
#include "Course.cpp"
#include "DataValidInput.cpp"
#include "CourseRepository.cpp"

class CourseManager : public CourseRepository
{
private:
    std::vector<Course *> courses;

    Course *findCourseById(int id)
    {
        auto it = std::find_if(courses.begin(), courses.end(), [id](Course *course)
                               { return course->id == id; });
        return (it != courses.end()) ? *it : nullptr;
    }

    //  Function to print header
    void printHeader() const
    {
        const int width = 20; // Adjust this value as needed for proper spacing
        std::cout << std::left << std::setw(width) << "Course Name"
                  << std::left << std::setw(width) << "ID"
                  << std::left << std::setw(width) << "Type"
                  << std::endl;
    }

public:
    ~CourseManager()
    {
        for (auto course : courses)
        {
            delete course;
        }
    }

    void addCourse(int id, std::string courseName, int type)
    {

        if (type == 1)
        {
            courses.push_back(new ShortCourse(courseName, id));
        }
        else if (type == 2)
        {
            courses.push_back(new FullCourse(courseName, id));
        }
        else
        {
            throw std::invalid_argument("Invalid course type.");
        }

        std::cout << "Course added successfully.\n";
        std::cout << std::endl;
    }

    void updateCourse(int id)
    {
        Course *course = findCourseById(id);
        if (course == nullptr)
        {
            throw std::invalid_argument("Course not found");
            return;
        }

        printHeader();
        course->display();
        std::cout << std::endl;
        std::cout << "Which type do you want to update in course?\n";
        std::cout << "1. Update ID\n";
        std::cout << "2. Update course Name\n";
        std::cout << "3. Update type\n";
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
            course->id = newId;
            break;
        }
        case 2:
        {
            std::string newCourse;
            std::cout << "2. UPDATE COURSE NAME\n";
            std::cout << "Enter new course name: ";
            newCourse = DataValidInput::getStringInput("");
            course->courseName = newCourse;
            break;
        }
        case 3:
        {
            int newType;
            std::cout << "3. UPDATE TYPE\n";
            std::cout << "Enter 1 for Short-Course, 2 for Full-Course: ";
            newType = DataValidInput::getIntInput("");

            if (newType == 1)
            {
                course = new ShortCourse(course->courseName, course->id);
            }
            else if (newType == 2)
            {
                course = new FullCourse(course->courseName, course->id);
            }
            else
            {
                throw std::invalid_argument("Invalid course type.");
            }
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        std::cout << "Course updated successfully.\n";
    }

    void deleteCourse(int id)
    {

        Course *course = findCourseById(id);
        if (course == nullptr)
        {
            throw std::invalid_argument("Course not found");
        }

        printHeader();
        course->display(); // Display student details before confirming deletion
        std::cout << std::endl;
        char confirm = DataValidInput::getCharInput("Are you sure you want to delete this course? (Y/N): ");

        if (confirm == 'Y' || confirm == 'y')
        {
            auto it = std::remove_if(courses.begin(), courses.end(), [id](Course *course)
                                     {
            if (course->id == id) {
                delete course;
                return true;
            }
            return false; });

            if (it != courses.end())
            {
                courses.erase(it, courses.end());
                std::cout << "Course has been successfully deleted.\n";
            }
            else
            {
                throw std::invalid_argument("Course not found");
            }
        }
        else
        {
            std::cout << "Delete courset has been canceled.\n";
        }
    }

    void viewCourses()
    {
        if (courses.empty())
        {
            throw std::invalid_argument("No course available");
            return;
        }

        printHeader(); // Print the header once
        for (const auto &course : courses)
        {
            course->display();
        }
    }
};