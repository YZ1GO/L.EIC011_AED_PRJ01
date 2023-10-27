#include "ReadData.h"

ReadData::ReadData(){
    ReadClasses("classes_per_uc.csv");
    ReadSchedules("classes.csv");
    ReadStudents("students_classes.csv");
    global = Global(classes, schedules, students);
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

    int studentCode = 0;
    string studentName;
    vector<Class> ucToClasses;

    while(getline(file, line)){
        stringstream ss(line);
        string studentCodeStr, currentStudentName, ucCode, classCode;

        getline(ss, studentCodeStr, ',');

        int currentStudentCode;
        try {
            currentStudentCode = stoi(studentCodeStr);
        } catch (const invalid_argument& arg) {
            cerr << "Error: Invalid integer conversion - " << arg.what() << endl;
            continue;
        }

        getline(ss, currentStudentName, ',');
        getline(ss, ucCode, ',');
        getline(ss, classCode, ',');

        if (currentStudentCode == studentCode && currentStudentName == studentName) {
            ucToClasses.emplace_back(ucCode, classCode);
        } else {
            if (studentCode != 0) {
                students.insert(studentCode, studentName, ucToClasses);
            }
            studentCode = currentStudentCode;
            studentName = currentStudentName;
            ucToClasses = {Class(ucCode, classCode)};
        }
    }

    if (studentCode != 0) {
        students.insert(studentCode, studentName, ucToClasses);
    }

    file.close();
}
