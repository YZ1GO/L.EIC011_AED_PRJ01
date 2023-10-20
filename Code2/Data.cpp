#include "Data.h"


Schedule::Schedule(string weekday, float startHour, float duration, string type)
    : WeekDay_(weekday), StartHour_(startHour), Duration_(duration), Type_(type) {}

Schedule::Schedule() {}



Student::Student(int studentCode, string studentName)
    : StudentCode_(studentCode), StudentName_(studentName) {}

Student::Student() {}



Class::Class(string ucCode, string classCode, vector<Student> students, vector<Schedule> schedule)
    : UcCode_(ucCode), ClassCode_(classCode), Students_(students), Schedule_(schedule) {}

Class::Class(string ucCode, string classCode) : UcCode_(ucCode), ClassCode_(classCode) {}

Class::Class(string ucCode, string classCode, Schedule schedule) : UcCode_(ucCode), ClassCode_(classCode) {
    Schedule_.push_back(schedule);
}

Class::Class() {}

bool Class::operator==(const Class& other) const {
    return UcCode_ == other.UcCode_ && ClassCode_ == other.ClassCode_;
}



UC::UC(string ucCode, const vector<Class>& classes)
    : UcCode_(ucCode), Classes_(classes) {}

UC::UC(string ucCode, string classCode) : UcCode_(ucCode){
    Classes_.push_back(Class(ucCode, classCode));
}

UC::UC() {}
