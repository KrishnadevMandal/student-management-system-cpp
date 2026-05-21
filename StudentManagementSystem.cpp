#include "StudentManagementSystem.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <limits>
#include <conio.h>

using namespace std;

const string FILE_NAME = "students.txt";

StudentManagementSystem::StudentManagementSystem()
{
    loadAdminCredentials();
}

bool StudentManagementSystem::rollExists(int roll)
{
    for (const auto &s : students)
    {
        if (s.rollNo == roll)
            return true;
    }

    return false;
}

int StudentManagementSystem::getValidIntegerInput()
{
    int value;

    while (!(cin >> value))
    {
        cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input! Enter a number : ";
    }

    return value;
}

string StudentManagementSystem::getHiddenPassword()
{
    string password;

    char ch;

    while (true)
    {
        ch = _getch();

        // ENTER key
        if (ch == 13)
        {
            cout << endl;
            break;
        }

        // BACKSPACE key
        else if (ch == 8)
        {
            if (!password.empty())
            {
                password.pop_back();

                cout << "\b \b";
            }
        }

        else
        {
            password += ch;

            cout << '*';
        }
    }

    return password;
}

void StudentManagementSystem::loadAdminCredentials()
{
    ifstream fin("admin.txt");

    if (!fin)
    {
        ofstream fout("admin.txt");

        fout << "admin\n1234";

        fout.close();

        adminUsername = "admin";
        adminPassword = "1234";

        return;
    }

    getline(fin, adminUsername);
    getline(fin, adminPassword);

    fin.close();
}

void StudentManagementSystem::saveAdminCredentials()
{
    ofstream fout("admin.txt");

    fout << adminUsername << endl;
    fout << adminPassword;

    fout.close();
}

bool StudentManagementSystem::login()
{
    string username;
    string password;

    int attempts = 3;

    while (attempts--)
    {
        cout << "\n========== ADMIN LOGIN ==========\n";

        cout << "Username : ";
        getline(cin, username);

        cout << "Password : ";
        password = getHiddenPassword();

        if (username == adminUsername && password == adminPassword)
        {
            cout << "\nLogin successful!\n";

            return true;
        }

        cout << "\nInvalid username or password!\n";
        cout << "Attempts left : " << attempts << endl;
    }

    return false;
}

void StudentManagementSystem::studentLogin()
{
    int roll;

    string password;

    cout << "\n========== STUDENT LOGIN ==========\n";

    cout << "Enter roll number : ";

    roll = getValidIntegerInput();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter password : ";

    password = getHiddenPassword();

    for (const auto &s : students)
    {
        if (s.rollNo == roll &&
            s.password == password)
        {
            cout << fixed << setprecision(2);

            cout << "\n========== STUDENT DETAILS ==========\n";
            cout << "Name         : " << s.name << endl;
            cout << "Roll No.     : " << s.rollNo << endl;
            cout << "Percentage   : " << s.percentage << "%" << endl;
            cout << "Grade        : " << s.grade << endl;
            cout << "\nSubjects:\n";

            for (const auto &[subject, mark] : s.marks)
            {
                cout << subject << " : " << mark << endl;
            }

            return;
        }
    }

    cout << "\nInvalid roll number or password!\n";
}

void StudentManagementSystem::addStudent()
{
    Student s;

    cout << "Enter name : ";
    getline(cin, s.name);

    while (s.name.empty())
    {
        cout << "Name cannot be empty! Enter again : ";
        getline(cin, s.name);
    }

    cout << "Enter roll number : ";
    s.rollNo = getValidIntegerInput();

    while (s.rollNo <= 0)
    {
        cout << "Invalid roll number! Enter positive value : ";
        s.rollNo = getValidIntegerInput();
    }

    if (rollExists(s.rollNo))
    {
        cout << "Roll number already exists!\n";
        return;
    }

    cout << "Create password : ";
    s.password = getHiddenPassword();

    while (s.password.empty())
    {
        cout << "Password cannot be empty! Enter again : ";

        s.password = getHiddenPassword();
    }

    int subjects;
    cout << "Enter number of subjects : ";
    subjects = getValidIntegerInput();

    while (subjects <= 0)
    {
        cout << "Invalid subject count! Enter positive value : ";
        subjects = getValidIntegerInput();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < subjects; i++)
    {
        string sub;
        int mark;

        cout << "\nEnter subject name : ";
        getline(cin, sub);

        while (sub.empty())
        {
            cout << "Subject name cannot be empty! Enter again : ";
            getline(cin, sub);
        }

        cout << "Enter marks : ";
        mark = getValidIntegerInput();

        while (mark < 0 || mark > 100)
        {
            cout << "Invalid marks! Enter between 0 and 100 : ";
            mark = getValidIntegerInput();
        }

        s.marks[sub] = mark;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    s.calculateGrade();

    students.push_back(s);

    cout << "\nStudent added successfully!\n";
}

void StudentManagementSystem::displayStudents()
{
    if (students.empty())
    {
        cout << "No students found!\n";
        return;
    }

    cout << fixed << setprecision(2);

    cout << "\n-------------------------------------------------------------------------------------------------\n";

    cout << left
         << setw(10) << "ROLL NO."
         << setw(25) << "NAME"
         << setw(15) << "PERCENTAGE"
         << setw(10) << "GRADE"
         << "SUBJECTS\n";

    cout << "-------------------------------------------------------------------------------------------------\n";

    for (const auto &s : students)
    {
        cout << left
             << setw(10) << s.rollNo
             << setw(25) << s.name
             << setw(15) << s.percentage
             << setw(10) << s.grade;

        for (const auto &[subject, mark] : s.marks)
        {
            cout << subject << ": " << mark << "  ";
        }

        cout << endl;
    }
}

void StudentManagementSystem::searchStudent()
{
    int roll;

    cout << "Enter roll number to search : ";

    roll = getValidIntegerInput();

    for (const auto &s : students)
    {
        if (s.rollNo == roll)
        {
            cout << fixed << setprecision(2);

            cout << "\nStudent Found!\n";

            cout << "Name         : " << s.name << endl;
            cout << "Roll No.     : " << s.rollNo << endl;
            cout << "Percentage   : " << s.percentage << fixed << setprecision(2) << "%" << endl;
            cout << "Grade        : " << s.grade << endl;

            cout << "\nSubjects:\n";

            for (const auto &[subject, mark] : s.marks)
            {
                cout << subject << " : " << mark << endl;
            }

            return;
        }
    }

    cout << "Student not found!\n";
}

void StudentManagementSystem::updateStudent()
{
    int roll;

    cout << "Enter roll number to update : ";
    roll = getValidIntegerInput();

    for (auto &s : students)
    {
        if (s.rollNo == roll)
        {
            int choice;

            do
            {
                cout << "\n========== UPDATE MENU ==========\n";

                cout << "1. Update Name\n";
                cout << "2. Update Marks\n";
                cout << "3. Add Subject\n";
                cout << "4. Delete Subject\n";
                cout << "5. Back\n";

                cout << "\nEnter your choice : ";

                choice = getValidIntegerInput();

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice)
                {
                case 1:
                {
                    cout << "Enter new name : ";

                    getline(cin, s.name);

                    while (s.name.empty())
                    {
                        cout << "Name cannot be empty! Enter again : ";

                        getline(cin, s.name);
                    }

                    cout << "Name updated successfully!\n";

                    break;
                }

                case 2:
                {
                    string subject;

                    cout << "Enter subject name : ";

                    getline(cin, subject);

                    if (s.marks.count(subject))
                    {
                        int newMarks;

                        cout << "Enter new marks : ";

                        newMarks = getValidIntegerInput();

                        while (newMarks < 0 || newMarks > 100)
                        {
                            cout << "Invalid marks! Enter between 0 and 100 : ";

                            newMarks = getValidIntegerInput();
                        }

                        s.marks[subject] = newMarks;

                        s.calculateGrade();

                        cout << "Marks updated successfully!\n";
                    }
                    else
                    {
                        cout << "Subject not found!\n";
                    }

                    break;
                }

                case 3:
                {
                    string subject;

                    cout << "Enter new subject name : ";

                    getline(cin, subject);

                    while (subject.empty())
                    {
                        cout << "Subject name cannot be empty! Enter again : ";

                        getline(cin, subject);
                    }

                    if (s.marks.count(subject))
                    {
                        cout << "Subject already exists!\n";
                    }
                    else
                    {
                        int marks;

                        cout << "Enter marks : ";

                        marks = getValidIntegerInput();

                        while (marks < 0 || marks > 100)
                        {
                            cout << "Invalid marks! Enter between 0 and 100 : ";

                            marks = getValidIntegerInput();
                        }

                        s.marks[subject] = marks;

                        s.calculateGrade();

                        cout << "Subject added successfully!\n";
                    }

                    break;
                }

                case 4:
                {
                    string subject;

                    cout << "Enter subject name to delete : ";

                    getline(cin, subject);

                    if (s.marks.count(subject))
                    {
                        s.marks.erase(subject);

                        s.calculateGrade();

                        cout << "Subject deleted successfully!\n";
                    }
                    else
                    {
                        cout << "Subject not found!\n";
                    }

                    break;
                }

                case 5:
                {
                    cout << "Returning to main menu...\n";
                    break;
                }

                default:
                {
                    cout << "Invalid choice! Try again.\n";
                }
                }

            } while (choice != 5);

            return;
        }
    }

    cout << "Student not found!\n";
}

void StudentManagementSystem::deleteStudent()
{
    int roll;

    cout << "Enter roll number to delete : ";

    roll = getValidIntegerInput();

    for (auto it = students.begin(); it != students.end(); it++)
    {
        if (it->rollNo == roll)
        {
            char confirm;

            cout << "Are you sure you want to delete "
                 << it->name
                 << "? (Y/N) : ";

            cin >> confirm;

            confirm = toupper(confirm);

            if (confirm == 'Y')
            {
                students.erase(it);

                cout << "Student deleted successfully!\n";
            }
            else
            {
                cout << "Deletion cancelled.\n";
            }

            return;
        }
    }

    cout << "Student not found!\n";
}

void StudentManagementSystem::sortStudents()
{
    int choice;

    cout << "\n========== SORT MENU ==========\n";

    cout << "1. Sort by Percentage (Descending)\n";
    cout << "2. Sort by Roll Number (Ascending)\n";
    cout << "3. Sort by Name (Alphabetical)\n";

    cout << "\nEnter your choice : ";

    choice = getValidIntegerInput();

    switch (choice)
    {
    case 1:
    {
        sort(students.begin(), students.end(),
             [](const Student &a, const Student &b)
             {
                 return a.percentage > b.percentage;
             });

        cout << "Students sorted by percentage successfully!\n";

        break;
    }

    case 2:
    {
        sort(students.begin(), students.end(),
             [](const Student &a, const Student &b)
             {
                 return a.rollNo < b.rollNo;
             });

        cout << "Students sorted by roll number successfully!\n";

        break;
    }

    case 3:
    {
        sort(students.begin(), students.end(),
             [](const Student &a, const Student &b)
             {
                 return a.name < b.name;
             });

        cout << "Students sorted by name successfully!\n";

        break;
    }

    default:
    {
        cout << "Invalid choice!\n";
    }
    }
}

void StudentManagementSystem::showTopper()
{
    if (students.empty())
    {
        cout << "No students found!\n";
        return;
    }

    Student topper = students[0];

    for (const auto &s : students)
    {
        if (s.percentage > topper.percentage)
        {
            topper = s;
        }
    }

    cout << fixed << setprecision(2);

    cout << "\n========== TOPPER ==========\n";

    cout << "Name         : " << topper.name << endl;
    cout << "Roll No.     : " << topper.rollNo << endl;
    cout << "Percentage   : " << topper.percentage << "%" << endl;
    cout << "Grade        : " << topper.grade << endl;

    cout << "\nSubjects:\n";

    for (const auto &[subject, mark] : topper.marks)
    {
        cout << subject << " : " << mark << endl;
    }
}

void StudentManagementSystem::showRankList()
{
    if (students.empty())
    {
        cout << "No students found!\n";
        return;
    }

    // Create a copy so original order is not changed
    vector<Student> rankedStudents = students;

    // Sort by percentage descending
    sort(rankedStudents.begin(), rankedStudents.end(),
         [](const Student &a, const Student &b)
         {
             return a.percentage > b.percentage;
         });

    cout << fixed << setprecision(2);

    cout << "\n================ RANK LIST ================\n";

    cout << left
         << setw(10) << "RANK"
         << setw(10) << "ROLL"
         << setw(25) << "NAME"
         << setw(15) << "PERCENTAGE"
         << "GRADE\n";

    cout << "-----------------------------------------------------------------\n";

    for (int i = 0; i < rankedStudents.size(); i++)
    {
        cout << left
             << setw(10) << i + 1
             << setw(10) << rankedStudents[i].rollNo
             << setw(25) << rankedStudents[i].name
             << setw(15) << rankedStudents[i].percentage
             << rankedStudents[i].grade
             << endl;
    }
}

void StudentManagementSystem::changeAdminPassword()
{
    string currentPassword;

    cout << "Enter current password : ";

    currentPassword = getHiddenPassword();

    if (currentPassword != adminPassword)
    {
        cout << "Incorrect current password!\n";

        return;
    }

    cout << "Enter new password : ";

    adminPassword = getHiddenPassword();

    saveAdminCredentials();

    cout << "Password changed successfully!\n";
}

void StudentManagementSystem::saveToFile()
{
    ofstream fout(FILE_NAME);

    if (!fout)
    {
        cout << "Error opening file!\n";
        return;
    }

    for (const auto &s : students)
    {
        fout << s.name << ","
             << s.rollNo << ","
             << s.password << ","
             << s.percentage << ","
             << s.grade;

        for (const auto &[subject, mark] : s.marks)
        {
            fout << "," << subject << ":" << mark;
        }

        fout << endl;
    }

    fout.close();

    cout << "Data saved successfully.\n";
}

void StudentManagementSystem::loadFromFile()
{
    ifstream fin(FILE_NAME);

    if (!fin)
    {
        cout << "No previous data file found.\n";
        return;
    }

    students.clear();

    string line;

    while (getline(fin, line))
    {
        Student s;

        stringstream ss(line);

        string part;

        getline(ss, s.name, ',');

        getline(ss, part, ',');
        s.rollNo = stoi(part);

        getline(ss, part, ',');
        s.password = part;

        getline(ss, part, ',');
        s.percentage = stof(part);

        getline(ss, part, ',');
        s.grade = part[0];

        while (getline(ss, part, ','))
        {
            size_t sep = part.find(':');

            if (sep != string::npos)
            {
                string sub = part.substr(0, sep);
                int mark = stoi(part.substr(sep + 1));
                s.marks[sub] = mark;
            }
        }

        students.push_back(s);
    }

    fin.close();

    cout << "\nData loaded successfully.\n";
}

void StudentManagementSystem::menu()
{
    int choice;

    do
    {
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";

        cout << "1.  Add Student\n";
        cout << "2.  Display All Students\n";
        cout << "3.  Search Student\n";
        cout << "4.  Update Student\n";
        cout << "5.  Delete Student\n";
        cout << "6.  Sort Students\n";
        cout << "7.  Show Topper\n";
        cout << "8.  Show Rank List\n";
        cout << "9.  Change Admin Password\n";
        cout << "10. Save Data\n";
        cout << "11. Exit\n";

        cout << "\nEnter your choice : ";

        choice = getValidIntegerInput();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << endl;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            sortStudents();
            break;

        case 7:
            showTopper();
            break;

        case 8:
            showRankList();
            break;

        case 9:
            changeAdminPassword();
            break;

        case 10:
            saveToFile();
            break;

        case 11:
            saveToFile();
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 11);
}