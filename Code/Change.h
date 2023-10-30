#ifndef PROJETO_AED_CHANGE_H
#define PROJETO_AED_CHANGE_H

#include "ReadData.h"

class Change {
public:
    Global global;
    Change();
    void removeStudent(Global& globalCopy);
    bool tryBuildNewSchedule(const Global& globalCopy, const Student& student);
    void getStudentSchedule(const Global& globalCopy, const Student& student, vector<Schedule>& studentSchedule);
    void changeClass(Global& globalCopy, int studentCode, const string& ucCode, const string& classCode);
};

#endif //PROJETO_AED_CHANGE_H
