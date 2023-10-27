//
// Created by chill on 10-10-2023.
//

#ifndef PROJETO_AED_DATA_H
#define PROJETO_AED_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Class {
public:
    string UcCode;
    string ClassCode;

    Class(string ucCode, string classCode);
    Class();
    bool operator==(const Class& other) const;
    bool operator<(const Class& other) const;
};

class Schedule {
public:
    Class UcToClasses;
    string WeekDay;
    float StartHour;
    float Duration;
    string Type;

    Schedule(Class ucToClass, string weekday, float startHour, float duration, string type);
    Schedule();
    bool operator<(const Schedule& other) const;
};

class Student {
public:
    int StudentCode;
    string StudentName;
    vector<Class> UcToClasses;

    Student(int studentCode, string studentName);
    Student();
    bool operator<(const Student& other) const;
    void addUcClass(string ucCode, string classCode);
};

// Structure used in the construction of StudentBST
struct Node {
    Student data;
    Node* left;
    Node* right;

    Node(const Student& student) : data(student), left(nullptr), right(nullptr) {}
};

// Binary search tree to store 'Student' objects
class StudentBST {
private:
    Node* root; // Pointer to the root of the BST
    Node* insert(Node* root, const Student& student); // Recursive method to insert a student into the BST
    Node* searchByCode(Node* root, int studentCode); // Recursive method to search for a student with its StudentCode
    Node* searchByName(Node* root, const string& studentName); // Recursive method to search for a student with its StudentName

public:
    StudentBST();
    void insert(int studentCode, const string& studentName, vector<Class> ucToClasses); // Insert a new student into the BST
    Student* searchByCode(int studentCode); // Search for a student with its StudentCode
    Student* searchByName(const string& studentName); // Search for a student with its StudentName
    Node* getRoot();
};

class Global {
public:
    vector<Class> Classes;
    vector<Schedule> Schedules;
    StudentBST Students;

    Global(vector<Class> classes, vector<Schedule> schedules, StudentBST students);
    Global(vector<Class> classes);
    Global(vector<Schedule> schedules);
    Global(StudentBST students);
    Global();
};

#endif //PROJETO_AED_DATA_H
