//
// Created by Bruno Huang on 2023/10/20.
//

#ifndef PROJETO_AED_FUNCTIONS_BRUNO_H
#define PROJETO_AED_FUNCTIONS_BRUNO_H

#include "ReadData.h"
using namespace std;

class Functions_Bruno {
public:
    ReadData dataReader;

    Functions_Bruno(ReadData datareader);

    void ListStudentsWithSameName();
    string ToLower(const string& input);
};


#endif //PROJETO_AED_FUNCTIONS_BRUNO_H
