#include "Functions.h"

Functions::Functions() {
    ReadData dataReader("students_classes.csv", "classes.csv", "classes_per_uc.csv");
    students = dataReader.students;
    schedules = dataReader.schedules;
    classes = dataReader.classes;
}

void Functions::ConsultarHorarioAluno(int studentCode) {
    for (const Student& student : students) {
        if (studentCode == student.StudentCode) {
            cout << "Número do Aluno(a): " << studentCode << endl;
            cout << "Nome do Aluno(a): " << student.StudentName << endl;
            cout << "Códigos da UC e códigos da respetiva Turma: ";
            for (const auto& pair : student.UcToClasses) {
                cout << pair.first << ", " << pair.second << endl;
            }
            return;
        }
    }
    cout << "Student with code " << studentCode << " not found." << endl;
}
