#include "Functions_Ricardo.h"

int main() {
    ReadData readData;
    Functions_Ricardo functions(readData);

    functions.consultTheScheduleOfClass("2LEIC13");

    functions.consultTheScheduleOfStudent(202043337);

    return 0;
}
