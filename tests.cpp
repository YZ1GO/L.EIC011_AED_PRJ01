//
// Created by chill on 10-10-2023.
//
#include "ReadData.h"
void ConsultarHorarioAluno(const vector<Student>& students, const vector<Classes>& classes, int studentCode) {
    cout << "Horário do Aluno (Código " << studentCode << "):" << endl;

    for (const Student& student : students) {
        if (student.StudentCode == studentCode) {
            cout << "Nome do Aluno: " << student.StudentName << endl;
            cout << "Código da UC: " << student.UcCode << endl;
            cout << "Código da Turma: " << student.ClassCode << endl;
            cout << "Horários das Aulas:" << endl;

            for (const Classes& classe : classes) {
                if (classe.ClassCode == student.ClassCode) {
                    cout << "Dia da Semana: " << classe.WeekDay << endl;
                    cout << "Hora de Início: " << classe.StartHour << endl;
                    cout << "Duração: " << classe.Duration << " horas" << endl;
                    cout << "Tipo de Aula: " << classe.Type << endl;
                }
            }
            return; // Aluno encontrado, termina a função
        }
    }

    cout << "Aluno não encontrado." << endl;
}


int main() {
    ReadData dataReader("students_classes.csv", "classes.csv", "classes_per_uc.csv"); // Substitua pelos nomes dos seus arquivos CSV

    vector<Student> students = dataReader.student;
    vector<Classes> classes = dataReader.classes;

    int codigoAlunoParaConsultar = 202031607; // Substitua pelo código do aluno que deseja consultar
    ConsultarHorarioAluno(students, classes, codigoAlunoParaConsultar);

    return 0;
}
