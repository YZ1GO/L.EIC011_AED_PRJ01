#include "Functions.h"

Functions::Functions() {
    ReadData dataReader("classes_per_uc.csv", "classes.csv", "students_classes.csv");
    classes = dataReader.classes;
    schedules = dataReader.schedules;
    students = dataReader.students;
}

Student Functions::ProcurarAlunoPorNumeroEstudante(int studentCode) {
    for (Student& student : students){
        if (studentCode == student.StudentCode){
            return student;
        }
    }
    return {};
}

Student Functions::ProcurarAlunoPorNomeEstudante(const string& studentName) {
    for (Student& student : students) {
        if (studentName == student.StudentName) {
            return student;
        }
    }
    return {};
}

Schedule Functions::ProcurarHorarioPorUcToClass(Class ucToClass){
    for (Schedule schedule : schedules) {
        if (ucToClass == schedule.UcToClasses){
            return schedule;
        }
    }
    return {};
}

void Functions::ConsultarHorarioAluno(Student student) {
    printf("\033[2J");
    student.printStudentInformation();
    for (const Class& studentClass : student.UcToClasses){
        Schedule schedule1 = ProcurarHorarioPorUcToClass(studentClass);
        schedule1.printSchedule();
    }
}
