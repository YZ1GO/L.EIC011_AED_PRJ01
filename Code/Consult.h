/**
 * @file Consult.h
 * @brief Header file containing class definitions for Consult.
 */

#ifndef PROJETO_AED_CONSULT_H
#define PROJETO_AED_CONSULT_H

#include "ReadData.h"

/**
 * @class Consult
 * @brief Class for consulting student and class data.
 */
class Consult {
private:
    /**
     * @brief Retrieves a set of UCs for a given year.
     *
     * @param year The year for which to retrieve UCs.
     * @return A set of UC codes for the specified year.
     */
    set<string> ucsOfTheYear(int year);

public:
    Global globalData;

    /**
     * @brief Default constructor for the Consult class.
     *
     * This constructor initializes the Consult object.
     */
    Consult();

    /**
     * @brief Parameterized constructor for the Consult class.
     *
     * This constructor initializes the Consult object with the provided Global data.
     *
     * @param global The Global data to initialize the Consult.
     */
    Consult(Global global);

    /**
     * @brief Updates the Consult's data with new Global data.
     *
     * This function updates the Consult's data with the provided Global data.
     *
     * @param data A Global object containing new data.
     */
    void updateData(Global data);

    /**
     * @brief Lists students by name.
     */
    void listStudentsByName();

    /**
     * @brief Finds a student by code.
     */
    void findStudentByCode();

    /**
     * @brief Prints the schedule for a given set of schedules.
     *
     * @param schedules A vector of Schedule objects to print.
     */
    void printSchedule(vector<Schedule> schedules);

    /**
     * @brief Retrieves the schedule of a given student.
     *
     * @param student The Student for which to retrieve the schedule.
     * @return A vector of Schedule objects representing the student's schedule.
     */
    vector<Schedule> getStudentSchedule(const Student& student);

    /**
     * @brief Consults the schedule of a specific student.
     */
    void consultTheScheduleOfStudent();

    /**
     * @brief Consults the schedule of a specific class.
     */
    void consultTheScheduleOfClass();

    /**
     * @brief Lists students registered in at least N UCs.
     */
    void listOfStudentsInAtLeastNUCs();

    /**
     * @brief Lists students in a specific class, UC, or year, and returns the list of students.
     *
     * @param identifier The identifier (class, UC, year) for which to list students.
     * @param searchCriteria A function to filter students based on the identifier.
     */
    void listOfStudentsInXBySortOrder(const string& identifier, const function<bool(const Class&)> searchCriteria);

    /**
     * @brief Lists students in a specific class.
     */
    void listOfStudentsInClass();

    /**
     * @brief Lists students in a specific UC.
     */
    void listOfStudentsInUc();

    /**
     * @brief Lists students in a specific year.
     */
    void listOfStudentsInYear();

    /**
     * @brief Shows the sorting menu based on the provided students count and identifier.
     *
     * @param studentsCount A map of identifier (class, UC, year) to the number of students.
     * @param identifier The identifier for which to show the sorting menu.
     */
    void showSortingMenu(const map<string, int>& studentsCount, const string& identifier);

    /**
     * @brief Consults the occupation in all classes.
     */
    void occupationInClasses();

    /**
     * @brief Consults the occupation in all UCs.
     */
    void occupationInUcs();

    /**
     * @brief Consults the occupation in all years.
     */
    void occupationInYears();

    /**
     * @brief Consults the occupation by sorting order based on the provided identifier type and identifier.
     *
     * @param identifierType The type of identifier (UC, year) for sorting.
     * @param identifier The specific identifier to sort by.
     * @param studentsCount A map of identifier (UC, year) to the number of students.
     */
    void consultOccupationBySortOrder(const string& identifierType, const string& identifier, const map<string, int>& studentsCount);

    /**
     * @brief Consults all classes occupation for a specific UC.
     */
    void consultUcOccupation();

    /**
     * @brief Consults all UCs occupation for a specific year.
     */
    void consultYearOccupation();

};


#endif //PROJETO_AED_CONSULT_H
