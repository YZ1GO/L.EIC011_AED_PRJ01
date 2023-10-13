#ifndef PROJETO_AED_FUNCTIONS_H
#define PROJETO_AED_FUNCTIONS_H

#include "ReadData.h"
#include <iostream>
using namespace std;

class Functions {
private:
    vector<Student> students;
    vector<Schedule> schedules;
    vector<Class> classes;

public:
    Functions();

    Student ProcurarAlunoPorNumeroEstudante(int studentCode);
    Student ProcurarAlunoPorNomeEstudante(const string& studentName);
    static void ConsultarHorarioAluno(Student student);
};

#endif //PROJETO_AED_FUNCTIONS_H
