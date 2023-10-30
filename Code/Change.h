#ifndef PROJETO_AED_CHANGE_H
#define PROJETO_AED_CHANGE_H

#include "ReadData.h"

class Change {
public:
    Global global;
    Change();
    void removeStudent(Global& global1);
    void changeClass(Global& global1, int studentCode, const string& ucCode, const string& classCode);
};

#endif //PROJETO_AED_CHANGE_H
