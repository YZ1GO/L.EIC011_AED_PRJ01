#include "Script.h"

using namespace std;

Script::Script() {
    System system_;
    this->system = system_;
    global = {system.get_Classes(), system.get_Schedules(), system.get_Students()};
}

void Script::run() {
    consultTheScheduleOfStudent();
}

void Script::consultTheScheduleOfStudent() {
    int studentCode;
    cin >> studentCode;

    Consult consult(global);
    consult.consultTheScheduleOfStudent(studentCode);

}