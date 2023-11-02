#include "ReadData.h"

using namespace std;

ReadData::ReadData(){
    global = {ReadClasses("classes_per_uc.csv"),
              ReadSchedules("classes.csv"),
              ReadStudents("students_classes.csv")};
}

string ReadData::TrimString(const string& toTrim) {
    string trimmed = toTrim;
    trimmed.erase(trimmed.begin(), find_if(trimmed.begin(), trimmed.end(),
                                                     [](char c) { return !isspace(c); }));
    trimmed.erase(find_if(trimmed.rbegin(), trimmed.rend(),
                               [](char c) { return !isspace(c); }).base(), trimmed.end());
    return trimmed;
}

vector<Class> ReadData::ReadClasses(const string classesPerUcCsv){
    vector<Class> classes;
    ifstream file(classesPerUcCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << classesPerUcCsv << endl;
        return classes;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        Class class1;

        getline(ss, class1.UcCode, ',');
        class1.UcCode = TrimString(class1.UcCode);
        getline(ss, class1.ClassCode);
        class1.ClassCode = TrimString(class1.ClassCode);

        classes.push_back(class1);
    }
    file.close();
    return classes;
}

vector<Schedule> ReadData::ReadSchedules(const string classesCsv){
    vector<Schedule> schedules;
    ifstream file(classesCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << classesCsv << endl;
        return schedules;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        Schedule schedule1;
        string startHour, duration;

        string ucCode, classCode;
        getline(ss, classCode, ',');
        classCode = TrimString(classCode);
        getline(ss, ucCode, ',');
        ucCode = TrimString(ucCode);
        schedule1.UcToClasses = Class(ucCode, classCode);

        getline(ss, schedule1.WeekDay, ',');
        schedule1.WeekDay = TrimString(schedule1.WeekDay);
        getline(ss, startHour, ',');
        getline(ss, duration, ',');
        getline(ss, schedule1.Type);
        schedule1.Type = TrimString(schedule1.Type);

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
    return schedules;
}

StudentBST ReadData::ReadStudents(const string studentCsv){
    StudentBST students;
    ifstream file(studentCsv);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << studentCsv << endl;
        return students;
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
        studentCodeStr = TrimString(studentCodeStr);

        int currentStudentCode;
        try {
            currentStudentCode = stoi(studentCodeStr);
        } catch (const invalid_argument& arg) {
            cerr << "Error: Invalid integer conversion - " << arg.what() << endl;
            continue;
        }

        getline(ss, currentStudentName, ',');
        currentStudentName = TrimString(currentStudentName);
        getline(ss, ucCode, ',');
        ucCode = TrimString(ucCode);
        getline(ss, classCode);
        classCode = TrimString(classCode);

        if (currentStudentCode == studentCode && currentStudentName == studentName) {
            ucToClasses.emplace_back(ucCode, classCode);
        } else {
            if (studentCode != 0) {
                students.insertStudent(studentCode, studentName, ucToClasses);
            }
            studentCode = currentStudentCode;
            studentName = currentStudentName;
            ucToClasses = {Class(ucCode, classCode)};
        }
    }

    if (studentCode != 0) {
        students.insertStudent(studentCode, studentName, ucToClasses);
    }
    file.close();

    return students;
}

System::System() {
    ReadData dataReader;
    Classes = dataReader.global.Classes;
    Schedules = dataReader.global.Schedules;
    Students = dataReader.global.Students;
    saveCurrentState();
}

System::System(Global data) {
    Classes = data.Classes;
    Schedules = data.Schedules;
    Students = data.Students;
    saveCurrentState();
}

void System::saveCurrentState() {
    Global currentState = {Classes, Schedules, Students};
    undoStack.push(currentState);
}

void System::updateData(Global global){
    Classes = global.Classes;
    Schedules = global.Schedules;
    Students = global.Students;
}

void System::undoAction() {
    if (!undoStack.empty()) {
        Global previousState = undoStack.top();  // Get the previous state
        undoStack.pop();  // Remove the previous state from the stack
        Classes = previousState.Classes;  // Restore the previous data
        Schedules = previousState.Schedules;
        Students = previousState.Students;
    }
}

vector<Class> System::get_Classes() {
    return Classes;
}

vector<Schedule> System::get_Schedules() {
    return Schedules;
}

StudentBST System::get_Students() {
    return Students;
}