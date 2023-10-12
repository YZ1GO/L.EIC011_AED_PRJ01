#ifndef PROJETO_AED_FUNCTIONS_H
#define PROJETO_AED_FUNCTIONS_H

#include "ReadData.h"
#include <iostream>
using namespace std;

class Functions {
private:
    vector<Student> students;
    vector<Classes> classes;
    vector<Classe_per_Uc> classes_per_uc;

public:
    Functions();

    void ConsultarHorarioAluno(int studentCode);
};

#endif //PROJETO_AED_FUNCTIONS_H
