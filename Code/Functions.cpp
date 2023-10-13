#include "Functions.h"

Functions::Functions() {
    ReadData dataReader("students_classes.csv", "classes.csv", "classes_per_uc.csv");
    students = dataReader.students;
    schedules = dataReader.schedules;
    classes = dataReader.classes;
}

void Functions::ConsultarHorarioAluno(int studentCode) {
    for (Student& student : students) {
        if (studentCode == student.StudentCode) {
            student.printStundetInformation();
        }
    }
    cout << "Student with code " << studentCode << " not found." << endl;
}
