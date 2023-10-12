#include "Functions.h"

Functions::Functions() {
    ReadData dataReader("students_classes.csv", "classes.csv", "classes_per_uc.csv");
    students = dataReader.student;
    classes = dataReader.classes;
    classes_per_uc = dataReader.classes_per_uc;
}

void Functions::ConsultarHorarioAluno(int studentCode) {
    for (Student student : students) {
        if (student.StudentCode == studentCode) {
            cout << "Número do Aluno(a): " << studentCode << endl;
            cout << "Nome do Aluno(a): " << student.StudentName << endl;
            cout << "Código da UC: " << student.UcCode << endl;
            cout << "Código da turma: " << student.ClassCode << endl;
        }
    }
}
