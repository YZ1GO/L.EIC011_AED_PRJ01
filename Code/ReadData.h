#ifndef PROJETO_AED_READDATA_H
#define PROJETO_AED_READDATA_H

#include "Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include "UtilityFunctions.h"
#include <variant>

struct Global {
    vector<Class> Classes;
    vector<Schedule> Schedules;
    StudentBST Students;
};

struct ChangeLogEntry {
    string timestamp;
    string requestType;
    int studentCode;
    string studentName;
    string currentUcCode;
    string currentClassCode;
    string newUcCode;
    string newClassCode;
    string extraNotes = "-"; // Reason of why the request was denied
    bool accepted;
};

class ReadData{

public:
    Global global;
    ReadData();

    string TrimString(const string& toTrim);
    vector<Class> ReadClasses(string classesPerUcCsv); // function to parse data from classes_per_uc.csv
    vector<Schedule> ReadSchedules(string classesCsv); // function to parse data from classes.csv
    StudentBST ReadStudents(string studentCsv); // function to parse data from students_classes.csv
};

class System {
private:
    vector<Class> Classes;
    vector<Schedule> Schedules;
    StudentBST Students;
    stack<StudentBST> undoStack;

public:
    System();
    System(Global data);

    vector<Class> get_Classes();
    vector<Schedule> get_Schedules();
    StudentBST get_Students();

    void deepCopyStudentBST(Node* currentNode, StudentBST& copy);
    void saveCurrentState();
    void undoAction();
    void updateData(Global global);
};


#endif //PROJETO_AED_READDATA_H
