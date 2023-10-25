#include "Functions_Ricardo.h"

int main() {
    ReadData readData;
    Functions_Ricardo functions(readData);

    //done
    //functions.consultTheScheduleOfClass("3LEIC03");

    //biggest issue with comparision, open code for details
    functions.consultTheScheduleOfStudent(202021152);

    //done
    functions.consultNumberOfStudentsInAtLeastNucs(7);

    //problem with comparison
    functions.consultStudentsInClass_ascendingOrder("3LEIC06");
    functions.consultStudentsInClass_descendingOrder("3LEIC06");


    //semi-DONE : problem doesnt print the classCode
    //functions.consultOccupationOfUc_ascendingOrder("L.EIC001");
    //functions.consultOccupationOfUc_descendingOrder("L.EIC001");

    return 0;
}
