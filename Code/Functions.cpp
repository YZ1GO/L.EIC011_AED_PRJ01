#include "Functions.h"

Functions::Functions() {
    ReadData dataReader;
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

void Functions::printStudentsInOrder(const Node* root, ofstream& outputFile) {
    if (root == nullptr) {
        return;
    }

    printStudentsInOrder(root->left, outputFile);
    printStudentToFile(root->data, outputFile);
    printStudentsInOrder(root->right, outputFile);
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
    printStudentsInOrder(dataReader.students.getRoot(), studentOutputFile);

    // Fecha os arquivos de saída
    classOutputFile.close();
    scheduleOutputFile.close();
    studentOutputFile.close();

}
