//
// Created by chill on 10-10-2023.
//

#ifndef PROJETO_AED_DATA_H
#define PROJETO_AED_DATA_H

#include "UtilityFunctions.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <set>

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
    Student* searchByCode(Node* root, int studentCode); // Recursive method to search for a student with its StudentCode
    // Recursive method to search for all student with StudentName or partial StudentName (case insensitive)
    void searchAllByName(Node* root, const string& searchName, vector<Student>& matchingStudents);
    void searchStudentsInAtLeastNucs(Node* root, const int n, set<Student>& matchingStudents);
    void findStudentsInClass(Node* root, const string& classCode, set<Student>& studentsOfTheClass);

public:
    StudentBST();
    Node* getRoot();
    void insert(int studentCode, const string& studentName, vector<Class> ucToClasses); // Insert a new student into the BST
    Student* searchByCode(int studentCode); // Search for a student with its StudentCode
    // Search for all students with StudentName or partial StudentName (case insensitive)
    void searchAllByName(const string& searchName, vector<Student>& matchingStudents);
    void searchStudentsInAtLeastNucs(const int n, set<Student>& matchingStudents);
    void findStudentsInClass(const string& classCode, set<Student>& studentsOfTheClass);
};

#endif //PROJETO_AED_DATA_H
