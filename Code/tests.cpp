#include "Functions.h"

int main() {
    Functions functions;

    Student student1 = functions.ProcurarAlunoPorNumeroEstudante(202071557);

    functions.ConsultarHorarioAluno(student1);

    return 0;
}