#include "Consult.h"
#include "Change.h"
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
    Global getData();

private:
    System system;
    Global global;
    Consult consult;

    int showMenu(const string& menuName, const vector<MenuItem>& menuItems);
    void clearScreen();
    void actionGoBack();
    void backToMenu();

    void updateData(Global data);
    void undoAction();

    void searchSchedule();
    void consultTheScheduleOfStudent();
    void consultTheScheduleOfClass();

    void searchStudent();
    void ListStudentsByName();
    void FindStudentByCode();

    void searchOccupation();
    void consultStudentsInClass();
    void consultStudentsInUc();
    void consultStudentsInYear();

    void consultListOfStudentsInAtLeastNucs();


    void removeStudent();
    void changeClass();
};

#endif // SCRIPT_H
