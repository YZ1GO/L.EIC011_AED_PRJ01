#include "Functions.h"

Functions::Functions() {
    ReadData dataReader("students_classes.csv", "classes.csv", "classes_per_uc.csv");
    students = dataReader.students;
    schedules = dataReader.schedules;
    classes = dataReader.classes;
}

Student Functions::ProcurarAlunoPorNumeroEstudante(int studentCode) {
    for (Student& student : students){
        if (studentCode == student.StudentCode){
            return student;
        }
    }
    return Student();
}

Student Functions::ProcurarAlunoPorNomeEstudante(string studentName) {
    for (Student& student : students) {
        if (studentName == student.StudentName) {
            return student;
        }
    }
    return Student();
}

void Functions::ConsultarHorarioAluno(Student student) {
    printf("\033[2J");
    student.printStudentInformation();
}
