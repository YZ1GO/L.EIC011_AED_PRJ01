#include "ReadData.h"

ReadData::ReadData(const string classesPerUcCsv, const string classesCsv, const string studentCsv){
    ReadUCs(classesPerUcCsv);
    ReadClasses(classesCsv);
    ReadStudents(studentCsv);
}

void ReadData::add_uc(const string ucCode, const string classCode){
    for (auto& uc : UCs){
        if (uc.UcCode_ == ucCode){
            uc.Classes_.push_back(Class(ucCode, classCode));
            return;
        }
    }
    UCs.push_back(UC(ucCode, classCode));
}

void ReadData::add_class_to_uc(const string ucCode, const Class newClass){
    for (auto& uc : UCs) {
        if (uc.UcCode_ == ucCode) {
            uc.Classes_.push_back(newClass);
        return;
        }
    }
}

void ReadData::add_class(const string classCode, const string ucCode, const string weekday, const float startHour, const float duration, const string type) {
    Schedule schedule(weekday, startHour, duration, type);
    Class newClass(ucCode, classCode, schedule);
    for (auto& class_ : Classes) {
        if (class_.ClassCode_ == classCode && class_.UcCode_ == ucCode) {
            class_.Schedule_.push_back(schedule);
            return;
        }
    }
    Classes.push_back(newClass);
    add_class_to_uc(ucCode, newClass);

}

void ReadData::add_student(const int studentCode, const string studentName, const string ucCode, const string classCode){
    Class class_student(ucCode, classCode);
    for (auto& classObj : Classes){
        if (classObj == class_student){
            classObj.Students_.push_back(Student(studentCode, studentName));
            return;
        }
    }
}

void ReadData::ReadUCs(const string classesPerUcCsv){
    ifstream file(classesPerUcCsv);
    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);

        string ucCode, classCode;
        getline(ss, ucCode, ',');
        getline(ss, classCode,',');

        add_uc(ucCode, classCode);
    }
    file.close();
}

void ReadData::ReadClasses(const string classesCsv){
    ifstream file(classesCsv);
    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);

        Schedule schedule1;
        string classCode, ucCode, weekday, startHour_str, duration_str, type;

        getline(ss, classCode, ',');
        getline(ss, ucCode, ',');
        getline(ss, weekday, ',');
        getline(ss, startHour_str, ',');
        getline(ss, duration_str, ',');
        getline(ss, type, ',');

        float startHour, duration;
        startHour = stof(startHour_str);
        duration = stof(duration_str);

        add_class(classCode, ucCode, weekday, startHour, duration, type);
    }
    file.close();
}

void ReadData::ReadStudents(const string studentCsv){
    ifstream file(studentCsv);
    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        string studentCode_str, studentName, ucCode, classCode;

        getline(ss, studentCode_str, ',');
        getline(ss, studentName, ',');
        getline(ss, ucCode, ',');
        getline(ss, classCode, ',');

        int studentCode = stoi(studentCode_str); // Convert to integer

        add_student(studentCode, studentName, ucCode, classCode);
    }
    file.close();
}



