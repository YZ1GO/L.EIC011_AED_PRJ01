/**
 * @file Change.h
 * @brief Header file for the Change class.
 */

#ifndef PROJETO_AED_CHANGE_H
#define PROJETO_AED_CHANGE_H

#include "ReadData.h"
#include "Consult.h"

/**
 * @class Change
 * @brief A class manage Student Class changes and Schedule updates.
 *
 * The Change class is responsible for handling student class changes, checking class capacities,
 * and ensuring a balance between classes. It also manages student schedule updates and supports
 * changing UCs and classes for students, as well as swapping classes between students.
 *
 * This class facilitates necessary changes to student enrollments and schedules.
 */
class Change {
public:
    Global global;
    ChangeLogEntry logEntry;

    /**
     * @brief Constructor for the Change class.
     * @param globalCopy The Global object to initialize with.
     */
    Change(Global& globalCopy);

    /**
     * @brief Check if adding a student to a new class will exceed its capacity.
     * @param classStudentsCount A map of class codes and their student counts.
     * @param newClassCode The class code to check.
     * @return True if adding the student will exceed the capacity, otherwise false.
     */
    bool checkIfClassCapacityExceeds(map<string, int> classStudentsCount, const string& newClassCode);

    /**
     * @brief Check if changing a student's class would disturb the balance between classes.
     * @param classStudentsCount A map of class codes and their student counts.
     * @param currentUcCode The current UC code.
     * @param oldClassCode The old class code.
     * @param newClassCode The new class code.
     * @return True if the balance is disturbed, otherwise false.
     */
    bool checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& currentUcCode, const string& oldClassCode, const string& newClassCode);

    /**
     * @brief Try to build a new schedule for a student.
     * @param student The Student object for which to build a schedule.
     * @return True if the schedule is successfully built, otherwise false.
     */
    bool tryBuildNewSchedule(const Student& student);

    /**
     * @brief Get the schedule of a student.
     * @param student The Student object.
     * @param studentSchedule The vector to store the student's schedule.
     */
    void getStudentSchedule(const Student& student, vector<Schedule>& studentSchedule);

    /**
     * @brief Change the class of a student.
     * @param student The Student object to change the class for.
     * @param currentUcCode The current UC code.
     * @param currentClassCode The current class code.
     * @param newClassCode The new class code.
     */
    void changeClass(Student& student, const string& currentUcCode, const string& currentClassCode, const string& newClassCode);

    /**
     * @brief Check if a student can join a new UC.
     * @param student The Student object.
     * @return True if the student can join the new UC, otherwise false.
     */
    bool checkIfCanJoinNewUC(const Student& student);

    /**
     * @brief Find all classes with vacancy in a new UC for a student.
     * @param student The Student object.
     * @param newUcCode The new UC code.
     * @return A map of class codes and their vacancy counts.
     */
    map<string, int> classesWithVacancyInNewUC(const Student& student, const string& newUcCode);

    /**
     * @brief Change the UC and respective class of a student，student can choose the UC to go but class can't be chosen.
     * @param student The Student object to change the UC for.
     * @param currentUcCode The current UC code.
     * @param currentClassCode The current class code.
     * @param newUcCode The new UC code.
     */
    void changeUC(Student& student, const string& currentUcCode, const string& currentClassCode, const string& newUcCode);

    /**
     * @brief Leave a UC and respective class for a student.
     * @param student The Student object.
     * @param ucCode The UC code to leave.
     * @param classCode The class code to leave.
     */
    void leaveUCAndClass(Student& student, const string& ucCode, const string& classCode);

    /**
     * @brief Join a UC and class for a student.
     * @param student The Student object.
     * @param newUcCode The new UC code to join.
     */
    void joinUCAndClass(Student& student, const string& newUcCode);

    /**
     * @brief Swap classes between two students.
     * @param student1 The first Student object.
     * @param ucCode The UC code of the classes to be swapped.
     * @param classCode1 The class code of the first student.
     * @param student2 The second Student object.
     * @param classCode2 The class code of the second student.
     */
    void swapClassesBetweenStudents(Student& student1, const string& ucCode, const string& classCode1, Student& student2, const string& classCode2);

    vector<string> successfulRequests;
    vector<string> failedRequests;
    string successMessage;
    string failureMessage;
};

#endif //PROJETO_AED_CHANGE_H
