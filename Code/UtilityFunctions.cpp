//
// Created by Bruno Huang on 2023/10/27.
//

#include "UtilityFunctions.h"

// Helper function to convert a string to lowercase
string ToLower(const string& input) {
    string lowered;
    for (char c : input) {
        lowered += tolower(c);
    }
    return lowered;
}