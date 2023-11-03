/**
 * @file Data.h
 * @brief Header file containing class definitions for Class, Schedule, Student, and StudentBST.
 */

#ifndef PROJETO_AED_DATA_H
#define PROJETO_AED_DATA_H

#include "UtilityFunctions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @class Class
 * @brief Represents a course class.
 */
class Class {
public:
    string UcCode; /**< The code of the course unit (UC). */
    string ClassCode; /**< The code of the class within the course unit. */

    /**
     * @brief Default constructor for the Class.
     */
    Class();

    /**
     * @brief Constructor for the Class.
     * @param ucCode The course unit code.
     * @param classCode The class code.
     */
    Class(string ucCode, string classCode);

    /**
     * @brief Equality operator for comparing two Class objects.
     * @param other The Class object to compare with.
     * @return True if the two objects are equal, otherwise false.
     */
    bool operator==(const Class& other) const;

    /**
     * @brief Less than operator for comparing two Class objects.
     * @param other The Class object to compare with.
     * @return True if this Class object is less than the other, otherwise false.
     */
    bool operator<(const Class& other) const;
};

/**
 * @class Schedule
 * @brief Represents the schedule of a class for a course unit.
 */
class Schedule {
public:
    Class UcToClasses; /**< The Class object associated with the schedule. */
    string WeekDay; /**< The day of the week for the class. */
    float StartHour; /**< The starting hour of the class. */
    float Duration; /**< The duration of the class in hours. */
    string Type; /**< The type of the class (T, TP, PL). */

    /**
     * @brief Default constructor for the Schedule.
     */
    Schedule();

    /**
     * @brief Constructor for the Schedule.
     * @param ucToClass The associated Class object.
     * @param weekday The day of the week.
     * @param startHour The starting hour of the class.
     * @param duration The duration of the class.
     * @param type The type of the class.
     */
    Schedule(Class ucToClass, string weekday, float startHour, float duration, string type);

    /**
    * @brief Less than operator for comparing two Schedule objects.
    * @param other The Schedule object to compare with.
    * @return True if this Schedule object is less than the other, otherwise false.
    */
    bool operator<(const Schedule& other) const;
};

/**
 * @class Student
 * @brief Represents a student.
 */
class Student {
public:
    int StudentCode; /**< The unique code of the student. */
    string StudentName; /**< The name of the student. */
    vector<Class> UcToClasses; /**< The list of classes the student is enrolled in. */

    /**
     * @brief Default constructor for the Student.
     */
    Student();

    /**
    * @brief Constructor for the Student.
    * @param studentCode The unique code of the student.
    * @param studentName The name of the student.
    */
    Student(const int studentCode, const string studentName);

    /**
    * @brief Less than operator for comparing two Student objects.
    * @param other The Student object to compare with.
    * @return True if this Student object is less than the other, otherwise false.
    */
    bool operator<(const Student& other) const;
};

/**
 * @struct Node
 * @brief A structure representing a binary tree node containing Student data.
 *
 * This structure defines a node for a binary tree, with each node holding
 * a Student object and pointers to its left and right children.
 */
struct Node {
    Student data; /**< The Student data associated with the node. */
    Node* left;   /**< Pointer to the left child node. */
    Node* right;  /**< Pointer to the right child node. */

    /**
     * @brief Constructor for Node.
     * @param student The Student object to be associated with this node.
     *
     * This constructor initializes a Node with the given Student data and
     * sets the left and right child pointers to nullptr.
     */
    Node(const Student& student) : data(student), left(nullptr), right(nullptr) {}
};

/**
 * @class StudentBST
 * @brief Binary search tree to store 'Student' objects.
 *
 * This class represents a binary search tree for storing and managing student records.
 * Each node in the tree holds a 'Student' object.
 */
class StudentBST {
private:
    Node* root; /**< Pointer to the root of the BST. */

    /**
     * @brief Recursive method to insert a student into the BST.
     * @param root The root of the subtree to insert the student into.
     * @param student The Student object to insert.
     * @return The root of the updated subtree.
     */
    Node* insertStudent(Node* root, const Student& student);

    /**
     * @brief Recursively searches for a student with the specified Student Code in an in-order traversal of the binary search tree.
     *
     * This method performs an in-order traversal of the binary search tree (BST) and recursively searches for a student
     * whose Student Code matches the given code.
     *
     * @param root Pointer to the root node of the BST to traverse.
     * @param studentCode The Student Code to search for.
     * @return A pointer to the Student object if found; otherwise, returns nullptr.
     */
    Student* searchByCode(Node* root, const int& studentCode);

    /**
     * @brief In-order traversal of the BST with a custom action.
     * @param node The current node being processed.
     * @param action The action to perform on each Student object.
     */
    void inOrderTraversal(Node* node, function<void(const Student&)> action);

public:
    /**
     * @brief Default constructor for StudentBST.
     */
    StudentBST();

    /**
     * @brief Get the root of the BST.
     * @return Pointer to the root node.
     */
    Node* getRoot();

    /**
     * @brief Set the root of the BST.
     * @param newRoot Pointer to the new root node.
     */
    void setRoot(Node* newRoot);

    /**
     * @brief Insert a new student into the BST.
     * @param studentCode The unique code of the student.
     * @param studentName The name of the student.
     * @param ucToClasses The list of classes the student is enrolled in.
     */
    void insertStudent(const int& studentCode, const string& studentName, vector<Class> ucToClasses);

    /**
     * @brief Search for a student with a specific StudentCode.
     * @param studentCode The unique code of the student to search for.
     * @return Pointer to the found Student object, or nullptr if not found.
     */
    Student* searchByCode(const int& studentCode);

    /**
     * @brief Search for all students with a specific name or partial name (case insensitive).
     * @param searchName The name to search for.
     * @param matchingStudents The list of matching Student objects.
     */
    void searchAllByName(const string& searchName, vector<Student>& matchingStudents);

    /**
     * @brief Search for students who are enrolled in at least 'n' course units.
     * @param n The minimum number of course units a student is enrolled.
     * @param matchingStudents The list of matching Student objects.
     */
    void searchStudentsInAtLeastNUCs(const int n, set<Student>& matchingStudents);

    /**
     * @brief Search for students who meet a custom search criteria.
     * @param searchCriteria The custom search criteria function.
     * @param matchingStudents The list of matching Student objects.
     */
    void searchStudentsWithin(const function<bool(const Class&)> searchCriteria, set<Student>& matchingStudents);

    /**
     * @brief Get the count of students in each class for a specific course unit.
     * @param ucCode The code of the course unit to count students in.
     * @param classStudentsCount A map containing class codes as keys and the number of students in each class.
     */
    void getStudentsCountInClass(const string& ucCode, map<string, int>& classStudentsCount);

    /**
     * @brief Get the count of students in a specific course unit.
     * @param ucCode The code of the course unit to count students in.
     * @param ucStudentsCount A map containing the course unit codes as keys and the number of students in each course unit.
     */
    void getStudentsCountInUc(const string& ucCode, map<string, int>& ucStudentsCount);

    /**
     * @brief Count the number of students in a specific class.
     * @param classCode The code of the class to count students in.
     * @return The number of students in the class.
     */
    int countStudentsInClass(const string& classCode);

    /**
     * @brief Count the number of students in a specific course unit.
     * @param ucCode The code of the course unit to count students in.
     * @return The number of students in the course unit.
     */
    int countStudentsInUC(const string& ucCode);

    /**
     * @brief Count the number of students in a specific academic year.
     * @param year The academic year to count students in.
     * @return The number of students in the academic year.
     */
    int countStudentsInYear(const string& year);

    /**
     * @brief Save the student data to a CSV file.
     * @param filename The name of the CSV file to save the data to.
     */
    void saveToCSV(const string& filename);
};

#endif //PROJETO_AED_DATA_H