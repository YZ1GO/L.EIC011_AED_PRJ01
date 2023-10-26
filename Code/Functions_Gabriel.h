//
// Created by Gabriel on 24/10/2023.
//

#ifndef PROJETO_AED_FUNCTIONS_GABRIEL_H
#define PROJETO_AED_FUNCTIONS_GABRIEL_H

#include "ReadData.h"


class Functions_Gabriel {
private:
    ReadData dataReader;
public:

    Functions_Gabriel();
    Functions_Gabriel(ReadData datareader);

    void printUCwithGreatestNumbers();
};


#endif //PROJETO_AED_FUNCTIONS_GABRIEL_H
