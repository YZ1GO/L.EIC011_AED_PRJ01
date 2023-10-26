#include "Functions_Ricardo.h"

int main() {
    ReadData readData;
    Functions_Ricardo functions(readData);

    //done
    //functions.consultTheScheduleOfClass("3LEIC03");
    functions.consultTheScheduleOfStudent(202043337);

    //done
    //functions.consultListOfStudentsInAtLeastNucs(6);

    //done
    //functions.consultStudentsInClass_ascendingOrder("1LEIC02");
    //functions.consultStudentsInClass_descendingOrder("1LEIC02");

    //done
    //functions.consultOccupationOfUc_ascendingOrder("L.EIC001");
    //functions.consultOccupationOfUc_descendingOrder("L.EIC025");

    //done
    //functions.consultOccupationOfYear_ascendingOrder(1);
    //functions.consultOccupationOfYear_descendingOrder(1);


    return 0;
}
