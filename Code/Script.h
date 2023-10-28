#include "Consult.h"
#include <vector>
#include <limits>

#ifndef SCRIPT_H
#define SCRIPT_H


class Script {
    struct MenuItem {
        string label;
        void (Script::*action)();
    };

public:
    Script();
    void run();

private:
    System system;
    Global global;
    Consult consult;

    void clearScreen();
    void actionGoBack();
    void backToMenu();

    void searchSchedule();
    void consultTheScheduleOfStudent();
    void consultTheScheduleOfClass();

    void searchStudent();
    void ListStudentsByName();
    void FindStudentByCode();

    void consultListOfStudentsInAtLeastNucs();

    void consultStudentsInClass();
    void consultStudentsInUc();
    void consultOccupationInYear();
};

#endif // SCRIPT_H
