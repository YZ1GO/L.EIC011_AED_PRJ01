#ifndef PROJETO_AED_UTILITYFUNCTIONS_H
#define PROJETO_AED_UTILITYFUNCTIONS_H

#include <cctype>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

std::string ToLower(const std::string& input);
std::string floatToHours(float hours);
bool checkIfUCCodeEqual(std::string a, std::string b);
bool checkIfClassCodeEqual(std::string a, std::string b);



#endif //PROJETO_AED_UTILITYFUNCTIONS_H
