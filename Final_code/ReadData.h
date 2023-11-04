/**
 * @file ReadData.h
 * @brief Header file containing class definitions for ReadData and System, as well as related data structures.
 */

#ifndef PROJETO_AED_READDATA_H
#define PROJETO_AED_READDATA_H

#include "Data.h"
#include "UtilityFunctions.h"
#include <list>
#include <sstream>
#include <unordered_map>
#include <variant>

/**
 * @struct Global
 * @brief A struct to hold global data for the application.
 */
struct Global {
    vector<Class> Classes;      ///< A vector of Class objects.
    vector<Schedule> Schedules; ///< A vector of Schedule objects.
    StudentBST Students;        ///< A binary search tree for storing Student objects.
};

/**
 * @struct ChangeLogEntry
 * @brief A struct to represent a change log entry for the application.
 */
struct ChangeLogEntry {
    string timestamp;        ///< The timestamp of the log entry.
    string requestType;      ///< The type of the request.
    int studentCode;         ///< The student code.
    string studentName;      ///< The name of the student.
    string currentUcCode;    ///< The current UC code.
    string currentClassCode; ///< The current class code.
    string newUcCode;        ///< The new UC code.
    string newClassCode;     ///< The new class code.
    string extraNotes = "-"; ///< Additional notes or reason for the request.
    bool accepted;           ///< A flag indicating whether the request was accepted.
};

/**
 * @class ReadData
 * @brief A class responsible for reading and parsing data for the application.
 */
class ReadData{
public:
    Global global; ///< An instance of the Global struct to store parsed data.

    /**
     * @brief Default constructor for the ReadData class.
     */
    ReadData();

    /**
     * @brief Trim whitespace from the beginning and end of a string.
     *
     * @param toTrim The string to trim.
     * @return The trimmed string.
     */
    string TrimString(const string& toTrim);

    /**
     * @brief Read and parse data from the classes_per_uc.csv file.
     *
     * @param classesPerUcCsv The path to the classes_per_uc.csv file.
     * @return A vector of Class objects containing parsed data.
     */
    vector<Class> ReadClasses(string classesPerUcCsv);

    /**
     * @brief Read and parse data from the classes.csv file.
     *
     * @param classesCsv The path to the classes.csv file.
     * @return A vector of Schedule objects containing parsed data.
     */
    vector<Schedule> ReadSchedules(string classesCsv);

    /**
     * @brief Read and parse data from the students_classes.csv file.
     *
     * @param studentCsv The path to the students_classes.csv file.
     * @return A StudentBST containing parsed student data.
     */
    StudentBST ReadStudents(string studentCsv);
};


/**
 * @class System
 * @brief A class representing the system and its operations.
 */
class System {
private:
    vector<Class> Classes;  ///< A vector of Class objects.
    vector<Schedule> Schedules; ///< A vector of Schedule objects.
    StudentBST Students;    ///< A binary search tree for storing Student objects.
    stack<StudentBST> undoStack; ///< A stack to store previous StudentBST states.

public:
    /**
     * @brief Default constructor for the System class.
     */
    System();

    /**
    * @brief Constructor for the System class.
    *
    * @param data A Global object containing initial data for the system.
    */
    System(Global data);

    /**
     * @brief Get the Classes vector.
     *
     * @return A vector of Class objects.
     */
    vector<Class> get_Classes();

    /**
     * @brief Get the Schedules vector.
     *
     * @return A vector of Schedule objects.
     */
    vector<Schedule> get_Schedules();

    /**
     * @brief Get the Students binary search tree.
     *
     * @return A StudentBST containing Student objects.
     */
    StudentBST get_Students();

    /**
     * @brief Deep copy a StudentBST.
     *
     * @param currentNode The current node in the source StudentBST.
     * @param copy The StudentBST to which the data should be copied.
     */
    void deepCopyStudentBST(Node* currentNode, StudentBST& copy);

    /**
     * @brief Save the current state of the StudentBST to the undo stack.
     */
    void saveCurrentState();

    /**
     * @brief Undo the last action by restoring the previous state from the undo stack.
     */
    void undoAction();

    /**
     * @brief Update the system data with new Global data.
     *
     * @param global A Global object containing new data.
     */
    void updateData(Global global);
};


#endif //PROJETO_AED_READDATA_H
