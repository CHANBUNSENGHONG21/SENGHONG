
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "StudentApplication.cpp"
#include "CourseApplication.cpp"
#include "DataValidInput.cpp"


using namespace std;

void displayMenu()
{
  std::cout << "\nMAIN MENU: (Version 1.0.0)\n";
  std::cout << "1. Student Management\n";
  std::cout << "2. Course Management\n";
  std::cout << "0. Exit\n";
}

int main()
{
  int choice;
  cout.setf(ios::fixed | ios::showpoint);
  cout << setprecision(2);

  do
  {
    displayMenu();
    choice = DataValidInput::getIntInput("Enter your choice: ");
    switch (choice)
    {
    case 1:
      StudentApplication studentApp;
      studentApp.run();
      break;
    case 2:
      CourseApplication courseApp;
      courseApp.run();
      break;
    case 0:

      break;
    default:

      cout << "\a";
    }
  } while (choice != 0);

  return 0;
}