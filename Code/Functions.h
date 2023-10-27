#ifndef PROJETO_AED_FUNCTIONS_H
#define PROJETO_AED_FUNCTIONS_H

#include "ReadData.h"
#include <iostream>
using namespace std;

class Functions {
private:
    ReadData dataReader;

public:
    Functions();



    void printClassToFile(const Class& classObj, ofstream& outputFile);
    void printScheduleToFile(const Schedule& schedule, ofstream& outputFile);
    void printStudentToFile(const Student& student, ofstream& outputFile);
    void printStudentsInOrder(const Node* root, ofstream& outputFile);
    void output_three_vectors_content();
};

#endif //PROJETO_AED_FUNCTIONS_H
