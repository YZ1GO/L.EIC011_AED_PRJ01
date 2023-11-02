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
    bool checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& oldClassCode, const string& newClassCode);
    bool tryBuildNewSchedule(const Student& student);
    void getStudentSchedule(const Student& student, vector<Schedule>& studentSchedule);
    void changeClass(int studentCode, const string& ucCode, const string& currentClassCode, const string& newClassCode);
    bool checkIfCanJoinNewUC(const Student& student);
    map<string, int> classesWithVacancyInNewUC(const Student& student, const string& newUcCode);
    void changeUC(int studentCode, const string& currentUcCode, const string& currentClassCode, const string& newUcCode);

    void leaveUCAndClass(int studentCode, const string& ucCode, const string& classCode);
    void joinUCAndClass(int studentCode, const string& newUcCode);
};

#endif //PROJETO_AED_CHANGE_H
