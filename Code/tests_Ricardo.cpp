#include "Functions_Ricardo.h"

int main() {
    ReadData readData;
    Functions_Ricardo functions(readData);
    //functions.consultTheScheduleOfClass("3LEIC03");

    functions.consultTheScheduleOfStudent(202021152);

    return 0;
}
