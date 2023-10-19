#include "ReadData.h"
#include <iostream>
#include <vector>

void printUCs(const vector<UC>& UCs) {
    for (const UC& uc : UCs) {
        cout << "UC Code: " << uc.UcCode_ << endl;
        cout << "Classes: " << endl;
        for (const Class& classObj : uc.Classes_) {
            cout << "  Class Code: " << classObj.ClassCode_ << endl;
        }
        cout << "-----------------------------" << endl;
    }
}

int main() {
    
    ReadData dataReader("classes_per_uc.csv", "classes.csv", "students_classes.csv");

    vector<UC> UCs = dataReader.UCs;

    printUCs(UCs);

    return 0;
}
