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
    void listStudentsByName();
    void findStudentByCode();

    void searchOccupation();
    void listOfStudentsInClass();
    void listOfStudentsInUc();
    void listOfStudentsInYear();

    void listOfStudentsInAtLeastNUCs();


    void removeStudent();
    void changeClass();
    void changeUC();
    void leaveUCAndClass();
};

#endif // SCRIPT_H
