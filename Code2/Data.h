#ifndef PROJETO_AED_DATA_H
#define PROJETO_AED_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

/**
 * @brief A class representing a schedule.
 */
class Schedule {
public:
    string WeekDay_; /**< The day of the week for the schedule. */
    float StartHour_; /**< The start hour of the schedule. */
    float Duration_; /**< The duration of the schedule. */
    string Type_; /**< The type of the schedule (e.g., TP, T or PL). */

    Schedule(string weekday, float startHour, float duration, string type);
    Schedule();
};

/**
 * @brief A class representing a student.
 */
class Student {
public:
    int StudentCode_; /**< The code of the student. */
    string StudentName_; /**< The name of the student. */

    Student(int studentCode, string studentName);
    Student();
};

/**
 * @brief A class representing a class.
 */
class Class {
public:
    string UcCode_; /**< The code of the associated UC. */
    string ClassCode_; /**< The code of the class. */
    vector<Student> Students_; /**< A vector of students in the class. */
    vector<Schedule> Schedule_; /**< The class schedule. */

    Class(string ucCode, string classCode, vector<Student> students, vector<Schedule> schedule);
    Class(string ucCode, string classCode);
    Class(string ucCode, string classCode, Schedule schedule);
    Class();
    bool operator==(const Class& other) const;
};

/**
 * @brief A class representing a UC (University Course).
 */
class UC {
public:
    string UcCode_; /**< The code of the UC. */
    vector<Class> Classes_; /**< A vector of classes associated with the UC. */

    UC(string ucCode, const vector<Class>& classes);
    UC(string ucCode, string classCode);
    UC();
};

#endif // PROJETO_AED_DATA_H
