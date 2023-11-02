#ifndef PROJETO_AED_CHANGE_H
#define PROJETO_AED_CHANGE_H

#include "ReadData.h"
#include "Consult.h"

class Change {
public:
    Global global;
    ChangeLogEntry logEntry;
    Change(Global& globalCopy);
    bool checkIfClassCapacityExceeds(map<string, int> classStudentsCount, const string& newClassCode);
    bool checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& currentUcCode, const string& oldClassCode, const string& newClassCode);
    bool tryBuildNewSchedule(const Student& student);
    void getStudentSchedule(const Student& student, vector<Schedule>& studentSchedule);
    void changeClass(Student& student, const string& currentUcCode, const string& currentClassCode, const string& newClassCode);
    bool checkIfCanJoinNewUC(const Student& student);
    map<string, int> classesWithVacancyInNewUC(const Student& student, const string& newUcCode);
    void changeUC(Student& student, const string& currentUcCode, const string& currentClassCode, const string& newUcCode);

    void leaveUCAndClass(Student& student, const string& ucCode, const string& classCode);
    void joinUCAndClass(Student& student, const string& newUcCode);

    vector<string> successfulRequests;
    vector<string> failedRequests;
    string successMessage;
    string failureMessage;
};

#endif //PROJETO_AED_CHANGE_H
