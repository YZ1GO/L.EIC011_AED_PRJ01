#include "Functions_Ricardo.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

Functions_Ricardo::Functions_Ricardo(ReadData readData) {
    data = readData;
}

//auxiliary function converts float to hours
string Functions_Ricardo::floatToHours(float hours) {
    int wholeHours = static_cast<int>(hours);
    int minutes = static_cast<int>((hours - wholeHours) * 60);

    stringstream ss;
    ss << setw(2) << setfill('0') << wholeHours << ":" << setw(2) << setfill('0') << minutes;

    return ss.str();
}

//auxiliary function that prints the information a schedule
void Functions_Ricardo::printSchedule(Schedule schedule) {
    cout << schedule.UcToClasses.UcCode << ", " << schedule.UcToClasses.ClassCode << "" << endl;
    cout << "      WeekDay: " << schedule.WeekDay << endl;
    cout << "   Start Hour: " << floatToHours(schedule.StartHour) << endl;
    cout << "     End Hour: " << floatToHours(schedule.StartHour + schedule.Duration) << endl;
    cout << "     Duration: " << schedule.Duration << " hours" << endl;
    cout << "         Type: " << schedule.Type << endl;
    cout << "-------------------------------------------------" << endl;
}

void Functions_Ricardo::consultTheScheduleOfClass(string classCode) {
    vector<Schedule> schedules;
    for (const Schedule& schedule : data.schedules){
        if (classCode == schedule.UcToClasses.ClassCode){
            schedules.push_back(schedule);
        }
    }
    sort(schedules.begin(), schedules.end());

    for (const Schedule& schedule : schedules){
        printSchedule(schedule);
    }
}

//PROBLEM CODE
void Functions_Ricardo::consultTheScheduleOfClass(Class StudentClass) {
    vector<Schedule> schedules;
    for (const Schedule& schedule : data.schedules){

        //THAT COMPARISON HAS PROBLEM
        if (StudentClass == schedule.UcToClasses){
            cout << "this code works" << endl;
            schedules.push_back(schedule);
        }
    }
    sort(schedules.begin(), schedules.end());

    for (const Schedule& schedule : schedules){
        printSchedule(schedule);
    }
}

/*
void Functions_Ricardo::printDayBlock(const string& dayOfWeek, const vector<Schedule>& daySchedules) {
    cout << "-----------------------" << endl;
    cout << "     " << dayOfWeek << endl;
    cout << "-----------------------" << endl;

    for (const Schedule& schedule : daySchedules) {
        cout << schedule.UcToClasses.UcCode << ", " << schedule.UcToClasses.ClassCode << endl;
        cout << "Start Hour: " << floatToHours(schedule.StartHour) << endl;
        cout << "End Hour: " << floatToHours(schedule.StartHour + schedule.Duration) << endl;
        cout << "Duration: " << schedule.Duration << " hours" << endl;
        cout << "Type: " << schedule.Type << endl << endl;
    }
}
void Functions_Ricardo::consultTheScheduleOfClass(const string& classCode) {
    // Create a map to group schedules by day of the week
    unordered_map<string, vector<Schedule>> schedulesByDay;

    for (const Schedule& schedule : data.schedules) {
        if (classCode == schedule.UcToClasses.ClassCode) {
            schedulesByDay[schedule.WeekDay].push_back(schedule);
        }
    }

    // Sort schedules within each day
    for (auto& entry : schedulesByDay) {
        sort(entry.second.begin(), entry.second.end());
    }

    // Print schedules in day blocks
    for (const auto& entry : schedulesByDay) {
        const string& dayOfWeek = entry.first;
        const vector<Schedule>& daySchedules = entry.second;
        printDayBlock(dayOfWeek, daySchedules);
    }
}*/

/*
//NOT WORKING
void Functions_Ricardo::consultTheScheduleOfStudent(int studentCode) {
    Student studentToConsult;
    for (const Student& student : data.students){
        if (student.StudentCode == studentCode){
            studentToConsult = student;
            break;
        }
    }
    cout << studentToConsult.StudentName;
    for (const Class& studentUcClass : studentToConsult.UcToClasses){
        cout << studentUcClass.ClassCode;
        consultTheScheduleOfClass(studentUcClass.ClassCode);
    }
}*/

void Functions_Ricardo::consultTheScheduleOfStudent(int studentCode) {
    // Find the student with the given student code
    for (const Student& student : data.students) {
        if (student.StudentCode == studentCode) {
            cout << "Student Code: " << student.StudentCode << endl;
            cout << "Student Name: " << student.StudentName << endl;

            // Iterate through the classes for this student
            for (const Class& studentClass : student.UcToClasses) {
                consultTheScheduleOfClass(studentClass);
            }
            return;  // Stop searching after finding the student
        }
    }
    cout << "Student with code " << studentCode << " not found." << endl;
}



