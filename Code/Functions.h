#ifndef PROJETO_AED_FUNCTIONS_H
#define PROJETO_AED_FUNCTIONS_H

#include "ReadData.h"
#include <iostream>
using namespace std;

class Functions {
private:
    vector<Class> classes;
    vector<Schedule> schedules;
    vector<Student> students;

public:
    Functions();

    Student ProcurarAlunoPorNumeroEstudante(int studentCode);
    Student ProcurarAlunoPorNomeEstudante(const string& studentName);
    Schedule ProcurarHorarioPorUcToClass(Class ucToClass);
    void ConsultarHorarioAluno(Student student);
};

#endif //PROJETO_AED_FUNCTIONS_H
