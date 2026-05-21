#ifndef STUDENTMANAGEMENTSYSTEM_H
#define STUDENTMANAGEMENTSYSTEM_H

#include <vector>

#include "Student.h"

using namespace std;

class StudentManagementSystem
{
private:
    vector<Student> students;

    string adminUsername;
    string adminPassword;

    bool rollExists(int roll);

    int getValidIntegerInput();

    string getHiddenPassword();

    void loadAdminCredentials();

    void saveAdminCredentials();

public:
    StudentManagementSystem();

    bool login();

    void studentLogin();

    void addStudent();

    void displayStudents();

    void searchStudent();

    void updateStudent();

    void deleteStudent();

    void sortStudents();

    void showTopper();

    void showRankList();

    void changeAdminPassword();

    void saveToFile();

    void loadFromFile();

    void menu();
};

#endif