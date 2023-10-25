#include "Data.h"

Class::Class(string ucCode, string classCode)
    : UcCode(ucCode), ClassCode(classCode) {}

Class::Class() {}

bool Class::operator==(const Class& other) const{
    return (UcCode==other.UcCode && ClassCode==other.ClassCode);
}

bool Class::operator<(const Class& other) const{
    if (UcCode != other.UcCode){
        return ClassCode < other.ClassCode;
    }
    return UcCode < other.UcCode;
}


Schedule::Schedule(Class ucToClass, string weekday, float startHour, float duration, string type)
        : UcToClasses(ucToClass), WeekDay(weekday), StartHour(startHour), Duration(duration), Type(type){}

Schedule::Schedule(){}

bool Schedule::operator<(const Schedule& other) const {
    // Compare first by weekDay, with Monday coming before Friday.
    if (WeekDay != other.WeekDay) {
        static const string weekdays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        auto it1 = find(weekdays, weekdays + 5, WeekDay);
        auto it2 = find(weekdays, weekdays + 5, other.WeekDay);
        if (it1 != weekdays + 5 && it2 != weekdays + 5) {
            return it1 - weekdays < it2 - weekdays;
        }
    }

    // If the weekDay is the same, compare by startHour.
    return StartHour < other.StartHour;
}


Student::Student(int studentCode, string studentName, vector<Class> ucToClass) :
    StudentCode(studentCode), StudentName(studentName), UcToClasses(ucToClass){}

Student::Student() {}

bool Student::operator<(const Student &other) const {
    return StudentName < other.StudentName;
}

Global::Global(vector<Class> classes, vector<Schedule> schedules, vector<Student> students)
    : Classes(classes), Schedules(schedules), Students(students) {}

Global::Global(vector<Class> classes) : Classes(classes) {}

Global::Global(vector<Schedule> schedules) : Schedules(schedules) {}

Global::Global(vector<Student> students) : Students(students) {}

Global::Global() {}
