#ifndef PROJETO_AED_UTILITYFUNCTIONS_H
#define PROJETO_AED_UTILITYFUNCTIONS_H

#include <cctype>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

char removeAccents(char c);
string ToLower(const string& input);
string floatToHours(float hours);
void sortByCode(vector<pair<string, int>>& result, bool ascending);
void sortClassByYear(vector<pair<string, int>>& result, bool ascending);
void sortByOccupation(vector<pair<string, int>>& result, bool ascending);
string getCurrentTimestamp();




#endif //PROJETO_AED_UTILITYFUNCTIONS_H
