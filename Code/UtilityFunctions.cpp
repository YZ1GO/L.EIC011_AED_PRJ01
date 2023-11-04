#include "UtilityFunctions.h"

/**
 * @file
 * @brief Implementation of the functions in UtilityFunctions.h.
 */

/**
 * @brief Remove accents from a character.
 * @param c The character from which to remove accents.
 * @return The character without accents.
 */
string ToLower(const string& input) {
    string lowercase;
    for (char c : input) {
        // doesnt work if (c == 'ó') { c = 'o'; } //Ambrósio, Verónica
        lowercase += tolower(c);
    }
    return lowercase;
}

/**
 * @param hours The floating-point number representing hours.
 * @return A string in "hh:mm" format corresponding to the given hours.
 */
string floatToHours(float hours) {
    int wholeHours = static_cast<int>(hours);
    int minutes = static_cast<int>((hours - wholeHours) * 60);

    stringstream ss;
    ss << setw(2) << setfill('0') << wholeHours << ":" << setw(2) << setfill('0') << minutes;

    return ss.str();
}

/**
 * Sorts a vector of pairs containing classes or UCs and an associated occupation of, based on class codes or UC codes.
 *
 * @param result The vector of pairs to be sorted.
 * @param ascending If true, the sorting order is ascending; otherwise, it's descending.
 */
void sortByCode(vector<pair<string, int>>& result, bool ascending) {
    sort(result.begin(), result.end(), [ascending](const pair<string, int>& a, const pair<string, int>& b) {
        string codeA = a.first;
        string codeB = b.first;

        if (codeA == "UP001" && codeB.substr(0, 5) == "L.EIC") {
            return !ascending; // "UP001" comes after "L.EIC" codes in ascending order
        } else if (codeA.substr(0, 5) == "L.EIC" && codeB == "UP001") {
            return ascending; // "UP001" comes before "L.EIC" codes in descending order
        }

        // Extract the last two digits of the classCode or ucCode and convert to an integer
        int numA = stoi(codeA.substr(codeA.length() - 2));
        int numB = stoi(codeB.substr(codeB.length() - 2));

        return ascending ? (numA < numB) : (numA > numB);
    });
}

/**
 * Sorts a vector of pairs containing class codes and an associated occupation of, based on the class year.
 *
 * @param result The vector of pairs to be sorted.
 * @param ascending If true, the sorting order is ascending; otherwise, it's descending.
 */
void sortClassByYear(vector<pair<string, int>>& result, bool ascending) {
    sort(result.begin(), result.end(), [ascending](const pair<string, int>& a, const pair<string, int>& b) {
        // Extract the first digit of classCode
        char classDigitA = a.first[0];
        char classDigitB = b.first[0];

        // Compare based on the first digit of classCode
        if (classDigitA == classDigitB) {
            // Extract the numeric part and convert to an integer
            int codeA = stoi(a.first.substr(5));  // Skip the first character and "LEIC"
            int codeB = stoi(b.first.substr(5));  // Skip the first character and "LEIC"

            return ascending ? (codeA < codeB) : (codeA > codeB);
        }

        return ascending ? (classDigitA < classDigitB) : (classDigitA > classDigitB);
    });
}

/**
 * Sorts a vector of pairs containing class codes or UC codes and an associated occupation of, based on occupation.
 *
 * @param result The vector of pairs to be sorted.
 * @param ascending If true, the sorting order is ascending; otherwise, it's descending.
 */
void sortByOccupation(vector<pair<string, int>>& result, bool ascending) {
    sort(result.begin(), result.end(), [ascending](const pair<string, int>& a, const pair<string, int>& b) {
        return ascending ? (a.second < b.second) : (a.second > b.second);
    });
}

/**
 * @return A string representing the current timestamp in "YYYY-MM-DD hh:mm:ss" format.
 */
string getCurrentTimestamp() {
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return buffer;
}
