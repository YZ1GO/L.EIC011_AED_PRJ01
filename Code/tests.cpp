#include "Functions.h"

int main() {
    Functions functions;

    Student student1 = functions.ProcurarAlunoPorNumeroEstudante(202071557);
    Student student2 = functions.ProcurarAlunoPorNomeEstudante("Ludovico");
    functions.ConsultarHorarioAluno(student2);

    return 0;
}