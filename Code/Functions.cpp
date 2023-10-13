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
        if (schedule.UcToClasses == ucToClass){
            return schedule;
        }
    }
    return Schedule();
}
void Functions::ConsultarHorarioAluno(Student student) {
    printf("\033[2J");
    student.printStudentInformation();
    for (Class classes : student.UcToClasses){
        Schedule schedule1 = ProcurarHorarioPorUcToClass(classes);
        schedule1.printSchedule();
    }



   /* for (Class studentClass : student.UcToClasses) {
        if (schedule.UcToClasses == studentClass) {
            schedule.printSchedule();
        }
    }*/


}
