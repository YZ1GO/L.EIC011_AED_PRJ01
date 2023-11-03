/**
 * @file Data.cpp
 *
 * Implementation of the classes and functions defined in Data.h.
 */

#include "ReadData.h"

/**
 * @brief Initializes the ReadData class by reading data from CSV files.
 */
ReadData::ReadData(){
    global = {ReadClasses("classes_per_uc.csv"),
              ReadSchedules("classes.csv"),
              ReadStudents("students_classes.csv")};
}

/**
 * @brief Trims leading and trailing white spaces from a string.
 *
 * @param toTrim The input string to trim.
 * @return The trimmed string.
 */
string ReadData::TrimString(const string& toTrim) {
    string trimmed = toTrim;
    trimmed.erase(trimmed.begin(), find_if(trimmed.begin(), trimmed.end(),
                                                     [](char c) { return !isspace(c); }));
    trimmed.erase(find_if(trimmed.rbegin(), trimmed.rend(),
                               [](char c) { return !isspace(c); }).base(), trimmed.end());
    return trimmed;
}

/**
 * @brief Reads and parses class data from a CSV file.
 *
 * @param classesPerUcCsv The path to the CSV file containing class data.
 * @return A vector of Class objects.
 */
vector<Class> ReadData::ReadClasses(const string classesPerUcCsv){
    vector<Class> classes;
    ifstream file(classesPerUcCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << classesPerUcCsv << endl;
        return classes;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        Class class1;

        getline(ss, class1.UcCode, ',');
        class1.UcCode = TrimString(class1.UcCode);
        getline(ss, class1.ClassCode);
        class1.ClassCode = TrimString(class1.ClassCode);

        classes.push_back(class1);
    }
    file.close();
    return classes;
}

/**
 * @brief Reads and parses schedule data from a CSV file.
 *
 * @param classesCsv The path to the CSV file containing schedule data.
 * @return A vector of Schedule objects.
 */
vector<Schedule> ReadData::ReadSchedules(const string classesCsv){
    vector<Schedule> schedules;
    ifstream file(classesCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << classesCsv << endl;
        return schedules;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        Schedule schedule1;
        string startHour, duration;

        string ucCode, classCode;
        getline(ss, classCode, ',');
        classCode = TrimString(classCode);
        getline(ss, ucCode, ',');
        ucCode = TrimString(ucCode);
        schedule1.UcToClasses = Class(ucCode, classCode);

        getline(ss, schedule1.WeekDay, ',');
        schedule1.WeekDay = TrimString(schedule1.WeekDay);
        getline(ss, startHour, ',');
        getline(ss, duration, ',');
        getline(ss, schedule1.Type);
        schedule1.Type = TrimString(schedule1.Type);

        try {
            schedule1.StartHour = stof(startHour);
            schedule1.Duration = stof(duration);
        } catch (const invalid_argument& arg) {
            cerr << "Error: Invalid float conversion - " << arg.what() << endl;
            schedule1.StartHour = 0.0;
            schedule1.Duration = 0.0;
        }

        schedules.push_back(schedule1);
    }
    file.close();
    return schedules;
}

/**
 * @brief Reads and parses student data from a CSV file.
 *
 * @param studentCsv The path to the CSV file containing student data.
 * @return A StudentBST object containing the parsed student data.
 */
StudentBST ReadData::ReadStudents(const string studentCsv){
    StudentBST students;
    ifstream file(studentCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << studentCsv << endl;
        return students;
    }

    string line;
    getline(file, line);

    int studentCode = 0;
    string studentName;
    vector<Class> ucToClasses;

    while(getline(file, line)){
        stringstream ss(line);
        string studentCodeStr, currentStudentName, ucCode, classCode;

        getline(ss, studentCodeStr, ',');
        studentCodeStr = TrimString(studentCodeStr);

        int currentStudentCode;
        try {
            currentStudentCode = stoi(studentCodeStr);
        } catch (const invalid_argument& arg) {
            cerr << "Error: Invalid integer conversion - " << arg.what() << endl;
            continue;
        }

        getline(ss, currentStudentName, ',');
        currentStudentName = TrimString(currentStudentName);
        getline(ss, ucCode, ',');
        ucCode = TrimString(ucCode);
        getline(ss, classCode);
        classCode = TrimString(classCode);

        // If student is the same as the previous line
        if (currentStudentCode == studentCode && currentStudentName == studentName) {
            // Add ucCode and classCode to the student
            ucToClasses.emplace_back(ucCode, classCode);
        } else { // If student isn't the same as the previous line
            if (studentCode != 0) {
                // Create a new node for the new student
                students.insertStudent(studentCode, studentName, ucToClasses);
            }
            // Update the parameters to the current (new) student
            studentCode = currentStudentCode;
            studentName = currentStudentName;
            ucToClasses = {Class(ucCode, classCode)};
        }
    }

    if (studentCode != 0) {
        students.insertStudent(studentCode, studentName, ucToClasses);
    }
    file.close();

    return students;
}

/**
 * @brief Default constructor for the System class.
 *
 * This constructor initializes the System object by reading data from external sources and saving the current state.
 */
System::System() {
    ReadData dataReader;
    Classes = dataReader.global.Classes;
    Schedules = dataReader.global.Schedules;
    Students = dataReader.global.Students;
    saveCurrentState();
}

/**
 * @brief Parameterized constructor for the System class.
 *
 * This constructor initializes the System object with the provided data and saves the current state.
 *
 * @param data A Global object containing data to initialize the System.
 */
System::System(Global data) {
    Classes = data.Classes;
    Schedules = data.Schedules;
    Students = data.Students;
    saveCurrentState();
}

/**
 * @brief Recursively deep copies a StudentBST.
 *
 * This function recursively creates a deep copy of the given StudentBST and stores it in the provided 'copy' StudentBST object.
 *
 * @param currentNode The current node to copy.
 * @param copy The StudentBST object to copy into.
 */
void System::deepCopyStudentBST(Node* currentNode, StudentBST& copy) {
    if (currentNode == nullptr) {
        return;
    }

    // Insert the student into the copy
    copy.insertStudent(currentNode->data.StudentCode, currentNode->data.StudentName, currentNode->data.UcToClasses);

    // Recursively copy the left and right subtrees
    deepCopyStudentBST(currentNode->left, copy);
    deepCopyStudentBST(currentNode->right, copy);
}

/**
 * @brief Saves the current state by creating deep copies of the data.
 */
void System::saveCurrentState() {
    // Create a deep copy of the StudentBST
    StudentBST copiedStudents;
    deepCopyStudentBST(Students.getRoot(), copiedStudents);

    // Push the deep copies onto the undoStack
    undoStack.push(copiedStudents);
}

/**
 * @brief Updates the System's data with new Global data.
 *
 * This function updates the System's data with the provided Global data.
 *
 * @param global A Global object containing new data.
 */
void System::updateData(Global global){
    Classes = global.Classes;
    Schedules = global.Schedules;
    Students = global.Students;
}

/**
 * @brief Undoes the last action by restoring the previous state.
 *
 * This function removes the previous state from the undoStack and restores the System's data to that previous state.
 */
void System::undoAction() {
    if (!undoStack.empty()) {
        undoStack.pop();  // Remove the previous state from the stack

        // Get the root of the StudentBST from the previous state
        Node* previousRoot = undoStack.top().getRoot();

        // Update the current Students object's root to the previous root
        Students.setRoot(previousRoot);
    }
}

/**
 * @brief Retrieves the classes data.
 *
 * This function returns the vector of Class objects representing class data.
 *
 * @return A vector of Class objects.
 */
vector<Class> System::get_Classes() {
    return Classes;
}

/**
 * @brief Retrieves the schedules data.
 *
 * This function returns the vector of Schedule objects representing schedule data.
 *
 * @return A vector of Schedule objects.
 */
vector<Schedule> System::get_Schedules() {
    return Schedules;
}

/**
 * @brief Retrieves the students data.
 *
 * This function returns the StudentBST object representing student data.
 *
 * @return A StudentBST object.
 */
StudentBST System::get_Students() {
    return Students;
}