//
// Created by Gabriel on 24/10/2023.
//

#include "Functions_Gabriel.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

Functions_Gabriel::Functions_Gabriel(){
    ReadData dataReader;
}

Functions_Gabriel::Functions_Gabriel(ReadData datareader) {
    dataReader = datareader;
}

void Functions_Gabriel::printUCwithGreatestNumbers() {
    vector<Class> classes;

    ifstream inputFile("students_classes.csv");
    string line;
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

    Class mostFrequentClass = classes[0];
    int maxCount = 1;

    for (size_t i = 0; i < classes.size(); ++i) {
        int count = 1;

        for (size_t j = i + 1; j < classes.size(); ++j) {
            if (classes[i] == classes[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mostFrequentClass = classes[i];
        }
    }

    vector<Class> mostFrequentClasses;
    for (size_t i = 0; i < classes.size(); ++i) {
        int count = 1;

        for (size_t j = i + 1; j < classes.size(); ++j) {
            if (classes[i] == classes[j]) {
                count++;
            }
        }
        if (count == maxCount) {
            mostFrequentClasses.push_back(classes[i]);
        }
    }
    cout << "Most frequent classes with frequency of: " << maxCount << endl;
    for (Class i : mostFrequentClasses){
        cout  << "UcCode: " << i.UcCode
              << ", ClassCode: " << i.ClassCode << endl;
    }

}

int main(){
    ReadData datareader;
    Functions_Gabriel funcao;
    Functions_Gabriel functions(datareader);
    //parametro
    funcao.printUCwithGreatestNumbers();
}
