//
// Created by chill on 27-10-2023.
//

#include "Script.h"

Script::Script() {
    System system_;
    this->system = system_;
    global = {system.get_Classes(), system.get_Schedules(), system.get_Students()};
}

void Script::run(string command) {

}

void Script::consultTheScheduleOfStudent() {
    int studentCode;
    cin >> studentCode;

    Consult consult(global);
    consult.consultTheScheduleOfStudent(studentCode);

}