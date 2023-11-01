#include "UtilityFunctions.h"

// Helper function to convert a string to lowercase
string ToLower(const string& input) {
    string lowercase;
    for (char c : input) {
        // doesnt work if (c == 'ó') { c = 'o'; } //Ambrósio, Verónica
        lowercase += tolower(c);
    }
    return lowercase;
}

// Helper function to convert a float to hours
string floatToHours(float hours) {
    int wholeHours = static_cast<int>(hours);
    int minutes = static_cast<int>((hours - wholeHours) * 60);

    stringstream ss;
    ss << setw(2) << setfill('0') << wholeHours << ":" << setw(2) << setfill('0') << minutes;

    return ss.str();
}

// Helper function to sort classes by classCode or ucs by ucCode
void sortByCode(vector<pair<string, int>>& result, bool ascending) {
    sort(result.begin(), result.end(), [ascending](const pair<string, int>& a, const pair<string, int>& b) {
        int codeA = stoi(a.first.substr(5));  // Extract the numeric part and convert to an integer
        int codeB = stoi(b.first.substr(5));  // Extract the numeric part and convert to an integer
        return ascending ? (codeA < codeB) : (codeA > codeB);
    });
}

// Helper function to sort classes by year
void sortByYear(vector<pair<string, int>>& result, bool ascending) {
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

// Helper function to sort classes by class occupation or ucs by uc occupation
void sortByOccupation(vector<pair<string, int>>& result, bool ascending) {
    sort(result.begin(), result.end(), [ascending](const pair<string, int>& a, const pair<string, int>& b) {
        return ascending ? (a.second < b.second) : (a.second > b.second);
    });
}
