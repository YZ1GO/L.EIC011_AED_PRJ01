#ifndef PROJETO_AED_UTILITYFUNCTIONS_H
#define PROJETO_AED_UTILITYFUNCTIONS_H

#include <cctype>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

/**
 * @file
 * @brief This file contains utility functions for string and data manipulation.
 */

/**
 * @brief Remove accents from a character.
 * @param c The character from which to remove accents.
 * @return The character without accents.
 */
char removeAccents(char c);

/**
 * @brief Convert a string to lowercase.
 * @param input The input string.
 * @return The input string in lowercase.
 */
string ToLower(const string& input);

/**
 * @brief Convert a floating-point value in hours to a string with hours and minutes.
 * @param hours The floating-point value representing hours.
 * @return The formatted string in "hh:mm" format.
 */
string floatToHours(float hours);

/**
 * @brief Sort classes by class code or UCs by UC code in ascending or descending order.
 * @param result The vector to be sorted.
 * @param ascending Set to true to sort in ascending order, false for descending.
 */
void sortByCode(vector<pair<string, int>>& result, bool ascending);

/**
 * @brief Sort classes by year and by class codes, in ascending or descending order.
 * @param result The vector to be sorted.
 * @param ascending Set to true to sort in ascending order, false for descending.
 */
void sortClassByYear(vector<pair<string, int>>& result, bool ascending);

/**
 * @brief Sort classes or ucs by occupation, in ascending or descending order.
 * @param result The vector to be sorted.
 * @param ascending Set to true to sort in ascending order, false for descending.
 */
void sortByOccupation(vector<pair<string, int>>& result, bool ascending);

/**
 * @brief Get the current timestamp as a string.
 * @return The current timestamp as a string in "YYYY-MM-DD hh:mm:ss" format.
 */
string getCurrentTimestamp();

#endif //PROJETO_AED_UTILITYFUNCTIONS_H
