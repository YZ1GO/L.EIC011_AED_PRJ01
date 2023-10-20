#include "Data.h"

Class::Class(string ucCode, string classCode)
    : UcCode(ucCode), ClassCode(classCode) {}

Class::Class() {}

bool Class::operator==(const Class& other) const{
    return (UcCode==other.UcCode && ClassCode==other.ClassCode);
}

Schedule::Schedule(Class ucToClass, string weekday, float startHour, float duration, string type)
        : UcToClasses(ucToClass), WeekDay(weekday), StartHour(startHour), Duration(duration), Type(type){}

Schedule::Schedule(){}


Student::Student(int studentCode, string studentName, vector<Class> ucToClass) :
    StudentCode(studentCode), StudentName(studentName), UcToClasses(ucToClass){}

Student::Student() {}

Global::Global(vector<Class> classes, vector<Schedule> schedules, vector<Student> students)
    : Classes(classes), Schedules(schedules), Students(students) {}

Global::Global(vector<Class> classes) : Classes(classes) {}

Global::Global(vector<Schedule> schedules) : Schedules(schedules) {}

Global::Global(vector<Student> students) : Students(students) {}

Global::Global() {}
