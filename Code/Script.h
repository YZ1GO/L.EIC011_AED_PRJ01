#include "ReadData.h"
#include "Consult.h"

#ifndef PROJETO_AED_SCRIPT_H
#define PROJETO_AED_SCRIPT_H


class Script {

public:
    System system;
    Global global;

    Script();
    void run(string command);

private:

    void consultTheScheduleOfStudent();
    void consultTheScheduleOfClass();

    void ListStudentsWithSameName();
    void consultListOfStudentsInAtLeastNucs();
    void consultStudentsInClass_ascendingOrder();
    void consultStudentsInClass_descendingOrder();
    void consultOccupationOfUc_ascendingOrder();
    void consultOccupationOfUc_descendingOrder();
    void consultOccupationOfYear_ascendingOrder();
    void consultOccupationOfYear_descendingOrder();

};


#endif //PROJETO_AED_SCRIPT_H
