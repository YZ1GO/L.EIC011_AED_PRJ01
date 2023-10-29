//
// Created by Gabriel on 24/10/2023.
//

#include "Functions_Gabriel.h"
#include "ReadData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

Functions_Gabriel::Functions_Gabriel(){
    ReadData dataReader;
}

Functions_Gabriel::Functions_Gabriel(ReadData datareader) {
    dataReader = datareader;
}

vector<pair<Class, int>> countClassFrequencies(const vector<Class>& classes) {
    vector<pair<Class, int>> frequencyPairs;

    for (const Class& cls : classes) {
        bool found = false;
        for (auto& pair : frequencyPairs) {
            if (pair.first == cls) {
                pair.second++;
                found = true;
                break;
            }
        }

        if (!found) {
            frequencyPairs.emplace_back(cls, 1);
        }
    }

    sort(frequencyPairs.begin(), frequencyPairs.end(),
         [](const pair<Class, int>& a, const pair<Class, int>& b) {
             return a.second > b.second;
         });

    return frequencyPairs;
}

void Functions_Gabriel::printUCwithGreatestNumbers() {
    vector<Class> classes;
    std::ifstream inputFile("students_classes.csv");
    std::string line;
    while (getline(inputFile, line)) {

        Class classInstance;
        string ucCode;
        string classCode;
        string StudentCode;
        string StudentName;
        stringstream ss(line);
        getline(ss, StudentCode, ',');
        getline(ss, StudentName, ',');
        getline(ss, classInstance.UcCode, ',');
        getline(ss, classInstance.ClassCode);

        classes.push_back(classInstance);
    }
    inputFile.close();

    if (!classes.empty()) {
        vector<pair<Class, int>> frequencyPairs = countClassFrequencies(classes);

        cout << "Class Frequencies in Decreasing Order:\n";
        for (const auto& pair : frequencyPairs) {
            const Class& cls = pair.first;
            int count = pair.second;
            cout << "UcCode: " << cls.UcCode << ", ClassCode: " << cls.ClassCode << ", Frequency: " << count << endl;
        }
    } else {
        cout << "No valid data found in the file." << endl;
    }
}



int main(){
    ReadData datareader;
    Functions_Gabriel funcao;
    Functions_Gabriel functions(datareader);
    //parametro
    funcao.printUCwithGreatestNumbers();
}
