#include "Functions_Ricardo.h"

int main() {
    ReadData readData;
    Functions_Ricardo functions(readData);

    //done
    //functions.consultTheScheduleOfClass("3LEIC03");
    //functions.consultTheScheduleOfStudent(202043337);

    //done
    //functions.consultNumberOfStudentsInAtLeastNucs(6);


    //done
    //functions.consultStudentsInClass_ascendingOrder("1LEIC02");
    //functions.consultStudentsInClass_descendingOrder("1LEIC02");

    //semi-DONE : problem doesnt print the classCode
    functions.consultOccupationOfUc_ascendingOrder("L.EIC001");
    //functions.consultOccupationOfUc_descendingOrder("L.EIC001");

    /*Class a = readData.classes[3];
    cout << a.UcCode << ", " << a.ClassCode << endl;
    cout << functions.AUX_numberOfStudentsInClass(a) << endl;
    set<Student> b = functions.AUX_listOfStudentsInClass(a.ClassCode);
    for (auto c : b){
        cout << c.StudentCode << " " << c.StudentName << endl;
    }*/

    return 0;
}
