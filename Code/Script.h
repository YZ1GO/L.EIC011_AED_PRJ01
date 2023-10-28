#include "Consult.h"
#include <limits>
#include <vector>

#ifndef PROJETO_AED_SCRIPT_H
#define PROJETO_AED_SCRIPT_H

struct MenuItem {
    string label;
    void (*action)();
};

class Script {

public:
    Script();
    void run();

private:
    System system;
    Global global;
    Consult consult;

    //UI FUNCTIONS

    static void clearScreen();
    static void actionGoBack();
    static void actionOption1();
    static void actionOption2();
    static void actionOption3();

    static void searchSchedule();
    static void searchStudent();
    static void searchUCOccupations();
    static void searchYearOccupations();

    //Functions of the program
    void consultTheScheduleOfStudent();
    void consultTheScheduleOfClass();

    void consultListOfStudentsInAtLeastNucs();

    void consultStudentsInClass();
    void consultStudentsInClass_ascendingOrder();
    void consultStudentsInClass_descendingOrder();

    void consultOccupation();

    void consultOccupationOfUc();
    void consultOccupationOfUc_ascendingOrder();
    void consultOccupationOfUc_descendingOrder();

    void consultOccupationOfYear();
    void consultOccupationOfYear_ascendingOrder();
    void consultOccupationOfYear_descendingOrder();

};


#endif //PROJETO_AED_SCRIPT_H
