#include "Data.h"

Class::Class(string ucCode, string classCode)
    : UcCode(ucCode), ClassCode(classCode) {}

Class::Class() {}

void Class::printClass() {
    cout << UcCode << " , " << ClassCode << endl;
}

Student::Student(int studentCode, string studentName, vector<Class> ucToClass) :
    StudentCode(studentCode), StudentName(studentName), UcToClasses(ucToClass){}

Student::Student() {}

void Student::printStudentInformation() {
    cout << "  INFORMAÇÕES RELATIVAS AO ESTUDANTE  " << endl;
    cout << "Número mecanografico: " << StudentCode << endl;
    cout << "Nome do Estudante: " << StudentName << endl;
    cout << "Código da UC e código da respetiva turma: " << endl;
    for (Class ucToClass : UcToClasses){
        ucToClass.printClass();
    }
}

Schedule::Schedule(Class ucToClass, string weekday, float startHour, float duration, string type)
: UcToClasses(ucToClass), WeekDay(weekday), StartHour(startHour), Duration(duration), Type(type){}

Schedule::Schedule() {}
