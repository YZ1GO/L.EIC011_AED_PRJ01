#ifndef PROJETO_AED_CHANGE_H
#define PROJETO_AED_CHANGE_H

#include "ReadData.h"

class Change {
public:
    Global global;
    Change();
    void removeStudent(Global& globalCopy);
    bool checkIfClassCapacityExceeds(const Global& globalCopy, map<string, int> classStudentsCount, const string& newClassCode);
    bool checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& oldClassCode, const string& newClassCode);
    bool tryBuildNewSchedule(const Global& globalCopy, const Student& student);
    void getStudentSchedule(const Global& globalCopy, const Student& student, vector<Schedule>& studentSchedule);
    void changeClass(Global& globalCopy, int studentCode, const string& ucCode, const string& currentClassCode, const string& newClassCode);
    bool checkIfMaxUCsExceeded(const Student& student);
    map<string, int> classesWithVacancyInNewUC(Global& globalCopy, const Student& student, const string& newUcCode);
    void changeUC(Global& globalCopy, int studentCode, const string& currentUcCode, const string& currentClassCode, const string& newUcCode);

    void leaveUCAndClass(Global& globalCopy, int studentCode, const string& ucCode, const string& classCode);
    void joinUCAndClass(Global& globalCopy, int studentCode, const string& ucCode);
};

#endif //PROJETO_AED_CHANGE_H
