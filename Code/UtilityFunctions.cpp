#include "UtilityFunctions.h"

using namespace std;

// Helper function to convert a string to lowercase
string ToLower(const string& input) {
    string lowered;
    for (char c : input) {
        lowered += tolower(c);
    }
    return lowered;
}

// Helper function to convert a float to hours
string floatToHours(float hours) {
    int wholeHours = static_cast<int>(hours);
    int minutes = static_cast<int>((hours - wholeHours) * 60);

    stringstream ss;
    ss << setw(2) << setfill('0') << wholeHours << ":" << setw(2) << setfill('0') << minutes;

    return ss.str();
}

// Helper function to check if 2 uc codes are equal
bool checkIfUCCodeEqual(string a, string b) {
    return a[5]==b[5] && a[6]==b[6] && a[7]==b[7];
}

// Helper function to check if 2 class codes are equal
bool checkIfClassCodeEqual(string a, string b) {
    return a[0]==b[0] && a[5]==b[5] && a[6]==b[6];
}


