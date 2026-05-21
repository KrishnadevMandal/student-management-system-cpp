#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>

using namespace std;

class Student
{
public:
    string name;
    int rollNo;
    string password;
    map<string, int> marks;
    float percentage;
    char grade;
    Student();
    void calculateGrade();
};

#endif