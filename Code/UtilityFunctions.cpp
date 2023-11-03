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

// Helper function to sort classes by year and classCode
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

// Helper function to sort classes by class occupation or ucs by uc occupation
void sortByOccupation(vector<pair<string, int>>& result, bool ascending) {
    sort(result.begin(), result.end(), [ascending](const pair<string, int>& a, const pair<string, int>& b) {
        return ascending ? (a.second < b.second) : (a.second > b.second);
    });
}

string getCurrentTimestamp() {
    time_t currentTime = time(nullptr);
    tm* localTime = std::localtime(&currentTime);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return buffer;
}
