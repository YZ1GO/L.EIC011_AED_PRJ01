#include "ReadData.h"

ReadData::ReadData(string classesPerUcCsv, string classesCsv, string studentCsv){
    ReadClasses(classesPerUcCsv);
    ReadSchedules(classesCsv);
    ReadStudents(studentCsv);
}

void ReadData::ReadClasses(const string classesPerUcCsv){
    ifstream file(classesPerUcCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << classesPerUcCsv << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        Class class1;

        getline(ss, class1.UcCode, ',');
        getline(ss, class1.ClassCode, ',');

        classes.push_back(class1);
    }
    file.close();
}

void ReadData::ReadSchedules(const string classesCsv){
    ifstream file(classesCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << classesCsv << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        Schedule schedule1;
        string startHour, duration;

        string ucCode, classCode;
        getline(ss, classCode, ',');
        getline(ss, ucCode, ',');
        schedule1.UcToClasses = Class(ucCode, classCode);

        getline(ss, schedule1.WeekDay, ',');
        getline(ss, startHour, ',');
        getline(ss, duration, ',');
        getline(ss, schedule1.Type, ',');

        try {
            schedule1.StartHour = stof(startHour);
            schedule1.Duration = stof(duration);
        } catch (const invalid_argument& arg) {
            cerr << "Error: Invalid float conversion - " << arg.what() << endl;
            schedule1.StartHour = 0.0; //
            schedule1.Duration = 0.0;
        }

        schedules.push_back(schedule1);
    }
    file.close();
}

void ReadData::ReadStudents(const string studentCsv){
    ifstream file(studentCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << studentCsv << endl;
        return;
    }

    string line;
    getline(file, line);

    unordered_map<int, Student> studentMap;

    while(getline(file, line)){
        stringstream ss(line);
        string studentCodeStr, studentName, ucCode, classCode;

        getline(ss, studentCodeStr, ',');

        int studentCode;
        try {
            studentCode = stoi(studentCodeStr);
        } catch (const invalid_argument& arg) {
            cerr << "Error: Invalid integer conversion - " << arg.what() << endl;
            continue;
        }

        getline(ss, studentName, ',');

        // Check if this student already exists in the map
        if (studentMap.find(studentCode) == studentMap.end()) {
            // If not found, create a new entry
            Student student1;
            student1.StudentCode = studentCode;
            student1.StudentName = studentName;
            getline(ss, ucCode, ',');
            getline(ss, classCode, ',');
            student1.UcToClasses.emplace_back(ucCode, classCode);
            studentMap[studentCode] = student1;
        } else {
            // If found, update the existing entry
            getline(ss, ucCode, ',');
            getline(ss, classCode, ',');
            studentMap[studentCode].UcToClasses.emplace_back(ucCode, classCode);
        }
    }
    for (const auto& student : studentMap) {
        students.push_back(student.second);
    }
    file.close();
}
