#include "Student.h"

Student::Student()
{
    percentage = 0;
    grade = 'F';
}

void Student::calculateGrade()
{
    if (marks.empty())
    {
        percentage = 0;
        grade = 'F';
        return;
    }

    int total = 0;

    for (const auto &[subject, mark] : marks)
    {
        total += mark;
    }

    percentage = total / float(marks.size());

    if (percentage >= 90)
        grade = 'A';

    else if (percentage >= 80)
        grade = 'B';

    else if (percentage >= 70)
        grade = 'C';

    else if (percentage >= 60)
        grade = 'D';

    else
        grade = 'F';
}