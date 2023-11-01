#include "Consult.h"
#include "Change.h"
#include <vector>
#include <limits>
#include <variant>
#include <queue>

#ifndef SCRIPT_H
#define SCRIPT_H

struct ChangeClassRequest {
    int studentCode;
    string currentUcCode;
    string currentClassCode;
    string newClassCode;
};

struct ChangeUcRequest {
    int studentCode;
    string currentUcCode;
    string currentClassCode;
    string newUcCode;
};

struct LeaveUcClassRequest {
    int studentCode;
    string currentUcCode;
    string currentClassCode;
};

struct JoinUcClassRequest {
    int studentCode;
    string newUcCode;
};

struct ChangeRequest {
    string requestType;
    variant<ChangeClassRequest, ChangeUcRequest, LeaveUcClassRequest, JoinUcClassRequest> requestData;
};

class Script {
    struct MenuItem {
        string label;
        void (Script::*action)();
    };

public:
    Script();
    void run();
    queue<ChangeRequest> changeRequestQueue;


private:
    System system;
    Global global;
    Consult consult;

    const string adminPassword = "12345";

    void drawBox(const string& text);
    int showMenu(const string& menuName, const vector<MenuItem>& menuItems);
    void clearScreen();
    void actionGoBack();
    void backToMenu();
    void updateData(Global data);
    void undoAction();
    void searchSchedule();
    void searchStudent();
    void searchAllOccupations();
    void searchSpecificOccupation();
    void searchListOfStudents();
    void consultTheScheduleOfStudent();
    void consultTheScheduleOfClass();
    void findStudentByCode();
    void listStudentsByName();
    void occupationOfClasses();
    void occupationOfUcs();
    void occupationOfYears();
    void occupationOfClassesOfUc();
    void occupationOfUcsOfYear();
    void listOfStudentsInClass();
    void listOfStudentsInUc();
    void listOfStudentsInYear();
    void listOfStudentsInAtLeastNUCs();
    void changeClass();
    void changeUC();
    void joinUCAndClass();
    void leaveUCAndClass();
    void processChangeRequests();

};

#endif // SCRIPT_H