//
// Created by Bruno Huang on 2023/10/27.
//

#ifndef PROJETO_AED_UTILITYFUNCTIONS_H
#define PROJETO_AED_UTILITYFUNCTIONS_H

#include <cctype>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

string ToLower(const string& input);
string floatToHours(float hours);
bool checkIfUCCodeEqual(string a, string b);
bool checkIfClassCodeEqual(string a, string b);



#endif //PROJETO_AED_UTILITYFUNCTIONS_H
