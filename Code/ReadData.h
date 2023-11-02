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

struct ChangeClassRequest {
    int studentCode;
    string currentUcCode;
    string currentClassCode;
    string newClassCode;
};

struct ChangeUcRequest {
    int studentCode;
    string currentUcCode;
    string currentClassCode;
    string newUcCode;
};

struct LeaveUcClassRequest {
    int studentCode;
    string currentUcCode;
    string currentClassCode;
};

struct JoinUcClassRequest {
    int studentCode;
    string newUcCode;
};

struct ChangeRequest {
    string requestType;
    variant<ChangeClassRequest, ChangeUcRequest, LeaveUcClassRequest, JoinUcClassRequest> requestData;
};

struct ChangeLogEntry {
    std::string timestamp;
    std::string requestType;
    int studentCode;
    std::string currentUcCode;
    std::string currentClassCode;
    std::string newUcCode;
    std::string newClassCode;
    std::string extraNotes = "-"; //reason of why the request was denied
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
    stack<Global> undoStack;

public:
    System();
    System(Global data);

    vector<Class> get_Classes();
    vector<Schedule> get_Schedules();
    StudentBST get_Students();

    void saveCurrentState();
    void undoAction();
    void updateData(Global global);
};


#endif //PROJETO_AED_READDATA_H
