#ifndef PROJETO_AED_READDATA_H
#define PROJETO_AED_READDATA_H

#include "Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief A class for reading data and populating UC and Class objects.
 */
class ReadData {

public:
    vector<UC> UCs; /**< A vector of UC objects. */
    vector<Class> Classes; /**< A vector of Class objects. */

    /**
     * @brief Construct a new ReadData object.
     * 
     * @param classesPerUcCsv Path to the classes_per_uc.csv file.
     * @param classesCsv Path to the classes.csv file.
     * @param studentCsv Path to the students_classes.csv file.
     */
    ReadData(const string classesPerUcCsv, const string classesCsv, const string studentCsv);

    /**
     * @brief Add a UC to the UCs vector.
     * 
     * @param ucCode The code of the UC.
     * @param classCode The code of the associated class.
     */
    void add_uc(const string ucCode, const string classCode);

    /**
    * @brief Add a Class to the vector of Classes associated with a specific UC.
    *
    * @param ucCode The code of the UC (Academic Course) to which the Class belongs.
    * @param newClass The Class to be added to the vector of Classes.
    *
    * This function adds a new Class to the vector of Classes associated with a specific UC identified by its code (ucCode).
    */
    void add_class_to_uc(const string ucCode, const Class newClass);

    /**
     * @brief Add a class to the Classes vector.
     * 
     * @param classCode The code of the class.
     * @param ucCode The code of the associated UC.
     * @param weekday The day of the week for the class schedule.
     * @param startHour The start hour of the class schedule.
     * @param duration The duration of the class schedule.
     * @param type The type of the class (e.g., TP or T).
     */
    void add_class(const string classCode, const string ucCode, const string weekday, const float startHour, const float duration, const string type);

    /**
     * @brief Add a student to the corresponding class.
     * 
     * @param studentCode The code of the student.
     * @param studentName The name of the student.
     * @param ucCode The code of the associated UC.
     * @param classCode The code of the associated class.
     */
    void add_student(const int studentCode, const string studentName, const string ucCode, const string classCode);
    
    /**
     * @brief Read data from the classes_per_uc.csv file and populate the UCs and Classes vectors.
     * 
     * @param classesPerUcCsv Path to the classes_per_uc.csv file.
     */
    void ReadUCs(const string classesPerUcCsv);
    
    /**
     * @brief Read data from the classes.csv file and populate the Classes vector.
     * 
     * @param classesCsv Path to the classes.csv file.
     */
    void ReadClasses(const string classesCsv);

    /**
     * @brief Read data from the students_classes.csv file and add students to the corresponding classes.
     * 
     * @param studentCsv Path to the students_classes.csv file.
     */
    void ReadStudents(const string studentCsv);

};

#endif // PROJETO_AED_READDATA_H
