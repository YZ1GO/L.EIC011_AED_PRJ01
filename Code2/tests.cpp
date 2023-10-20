#include <iostream>
#include <fstream>
#include <vector>
#include "ReadData.h"

using namespace std;

void printClassToFile(const Class& classObj, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    outputFile << "Class Code: " << classObj.ClassCode_ << endl;
    outputFile << "   UC Code: " << classObj.UcCode_ << endl << endl;

    for (const auto schedule : classObj.Schedule_){
        outputFile << "Class Schedule:" << endl;
        outputFile << "    Weekday: " << schedule.WeekDay_ << endl;
        outputFile << "    Start Hour: " << schedule.StartHour_ << endl;
        outputFile << "    Duration: " << schedule.Duration_ << endl;
        outputFile << "    Type: " << schedule.Type_ << endl << endl;
    }
    outputFile.close();
}

void printUCAndClassCodesToFile(const UC& uc, ofstream& outputFile) {
    outputFile << "UC Code: " << uc.UcCode_ << endl;
    for (const Class& classObj : uc.Classes_) {
        outputFile << classObj.ClassCode_ << endl;
    }
    outputFile << endl;
}

int main() {
    ReadData dataReader("classes_per_uc.csv", "classes.csv", "students_classes.csv");

    string filename = "UC_class_code.txt";
    string folderpath = "output/";
    string path = folderpath + filename;
    ofstream outputFile(path);

    for (const UC& uc : dataReader.UCs) {

        for (const Class& classObj : uc.Classes_){
            string outputFileName = classObj.ClassCode_ + "_" + uc.UcCode_ + ".txt";
            string folderpath_ = "output/" + uc.UcCode_ + "/";
            string path_ = outputFileName + folderpath_;

            printClassToFile(classObj, path_);
            cout << "Class information printed to " << outputFileName << endl;
        }
            printUCAndClassCodesToFile(uc, outputFile);
    }

    outputFile.close();
    return 0;
}
