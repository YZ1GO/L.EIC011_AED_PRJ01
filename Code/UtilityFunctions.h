#ifndef PROJETO_AED_UTILITYFUNCTIONS_H
#define PROJETO_AED_UTILITYFUNCTIONS_H

#include <cctype>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

string ToLower(const string& input);
string floatToHours(float hours);
bool checkIfUCCodeEqual(string a, string b);
bool checkIfClassCodeEqual(string a, string b);
void sortByClassCode(vector<pair<string, int>>& result, bool ascending);
void sortByClassOccupation(vector<pair<string, int>>& result, bool ascending);




#endif //PROJETO_AED_UTILITYFUNCTIONS_H
