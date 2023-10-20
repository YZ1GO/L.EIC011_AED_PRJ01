#include "Functions.h"

Functions::Functions() {
    ReadData dataReader;
}

Student Functions::ProcurarAlunoPorNumeroEstudante(int studentCode) {
    for (Student& student : dataReader.students){
        if (studentCode == student.StudentCode){
            return student;
        }
    }
    return {};
}

Student Functions::ProcurarAlunoPorNomeEstudante(const string& studentName) {
    for (Student& student : dataReader.students) {
        if (studentName == student.StudentName) {
            return student;
        }
    }
    return {};
}

Schedule Functions::ProcurarHorarioPorUcToClass(Class ucToClass){
    for (const Schedule& schedule : dataReader.schedules) {
        cout << "Comparing ucToClass: " << ucToClass.UcCode << " , " << ucToClass.ClassCode << " with schedule: " << schedule.UcToClasses.UcCode << " , " << schedule.UcToClasses.ClassCode << endl;
        if (ucToClass == schedule.UcToClasses){
            cout << "Match found!" << endl;
            return schedule;
        }
    }
    return {};
}

void Functions::Functions::ConsultarHorarioAluno(int studentCode) {
    printf("\033[2J");
    Student student = ProcurarAlunoPorNumeroEstudante(studentCode);
    student.printStudentInformation();
    for (const Class& studentClass : student.UcToClasses){
        Schedule schedule1 = ProcurarHorarioPorUcToClass(studentClass);
        schedule1.printSchedule();
    }
}


// Função para imprimir os dados de uma classe em um arquivo
void Functions::printClassToFile(const Class& classObj, ofstream& outputFile) {
    outputFile << "Class Code: " << classObj.ClassCode << endl;
    outputFile << "UC Code: " << classObj.UcCode << endl;
    outputFile << "---------------------------" << endl;
}

// Função para imprimir os dados de um cronograma em um arquivo
void Functions::printScheduleToFile(const Schedule& schedule, ofstream& outputFile) {
    outputFile << "UC Code: " << schedule.UcToClasses.UcCode << endl;
    outputFile << "Class Code: " << schedule.UcToClasses.ClassCode << endl;
    outputFile << "Weekday: " << schedule.WeekDay << endl;
    outputFile << "Start Hour: " << schedule.StartHour << endl;
    outputFile << "Duration: " << schedule.Duration << endl;
    outputFile << "Type: " << schedule.Type << endl;
    outputFile << "---------------------------" << endl;
}

// Função para imprimir os dados de um estudante em um arquivo
void Functions::printStudentToFile(const Student& student, ofstream& outputFile) {
    outputFile << "Student Code: " << student.StudentCode << endl;
    outputFile << "Student Name: " << student.StudentName << endl;
    outputFile << "UCs and Classes:" << endl;
    for (const Class& ucToClass : student.UcToClasses) {
        outputFile << "  UC Code: " << ucToClass.UcCode << ", Class Code: " << ucToClass.ClassCode << endl;
    }
    outputFile << "---------------------------" << endl;
}

void Functions::output_three_vectors_content() {

    ofstream classOutputFile("classes.txt");  // Arquivo para as informações das classes
    ofstream scheduleOutputFile("schedules.txt");  // Arquivo para as informações dos cronogramas
    ofstream studentOutputFile("students.txt");  // Arquivo para as informações dos estudantes

    // Classes
    classOutputFile << "Classes:" << endl;
    for (const Class& classObj : dataReader.classes) {
        printClassToFile(classObj, classOutputFile);
    }

    // Schedules
    scheduleOutputFile << "Schedules:" << endl;
    for (const Schedule& schedule : dataReader.schedules) {
        printScheduleToFile(schedule, scheduleOutputFile);
    }

    // Students
    studentOutputFile << "Students:" << endl;
    for (const Student& student : dataReader.students) {
        printStudentToFile(student, studentOutputFile);
    }

    // Fecha os arquivos de saída
    classOutputFile.close();
    scheduleOutputFile.close();
    studentOutputFile.close();

}
