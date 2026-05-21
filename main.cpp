#include "StudentManagementSystem.h"

#include <iostream>
#include <limits>

using namespace std;

int main()
{
    StudentManagementSystem sms;

    sms.loadFromFile();

    int choice;

    do
    {
        cout << "\n========== STUDENT MANAGEMENT PORTAL ==========\n";

        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice : ";

        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            if (sms.login())
            {
                sms.menu();
            }
            else
            {
                cout << "\nToo many failed attempts!\n";
            }

            break;
        }

        case 2:
        {
            sms.studentLogin();
            break;
        }

        case 3:
        {
            cout << "Exiting program...\n";
            break;
        }

        default:
        {
            cout << "Invalid choice!\n";
        }
        }

    } while (choice != 3);

    return 0;
}