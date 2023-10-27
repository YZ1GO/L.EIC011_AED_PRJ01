#include "Data.h"
#include "UtilityFunctions.h"

Class::Class(string ucCode, string classCode)
    : UcCode(ucCode), ClassCode(classCode) {}

Class::Class() {}

bool Class::operator==(const Class& other) const{
    return (UcCode==other.UcCode) && (ClassCode==other.ClassCode);
}

bool Class::operator<(const Class& other) const{
    if (UcCode != other.UcCode){
        return ClassCode < other.ClassCode;
    }
    return UcCode < other.UcCode;
}


Schedule::Schedule(Class ucToClass, string weekday, float startHour, float duration, string type)
        : UcToClasses(ucToClass), WeekDay(weekday), StartHour(startHour), Duration(duration), Type(type){}

Schedule::Schedule(){}

bool Schedule::operator<(const Schedule& other) const {
    // Compare first by weekDay, with Monday coming before Friday.
    if (WeekDay != other.WeekDay) {
        static const string weekdays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        auto it1 = find(weekdays, weekdays + 5, WeekDay);
        auto it2 = find(weekdays, weekdays + 5, other.WeekDay);
        if (it1 != weekdays + 5 && it2 != weekdays + 5) {
            return it1 - weekdays < it2 - weekdays;
        }
    }

    // If the weekDay is the same, compare by startHour.
    return StartHour < other.StartHour;
}


Student::Student(int studentCode, string studentName) :
    StudentCode(studentCode), StudentName(studentName){}

Student::Student() {}

bool Student::operator<(const Student &other) const {
    return StudentName < other.StudentName;
}

void Student::addUcClass(string ucCode, string classCode) {
    UcToClasses.emplace_back(ucCode, classCode);
}

Node* StudentBST::insert(Node* root, const Student& student) {
    if (root == nullptr) {
        return new Node(student);
    }

    if (student < root->data) {
        root->left = insert(root->left, student);
    } else if (root->data < student) {
        root->right = insert(root->right, student);
    }

    return root;
}

Student* StudentBST::searchByCode(Node* root, int studentCode) {
    if (root == nullptr) {
        return nullptr;
    }

    // Check the current node
    if (studentCode == root->data.StudentCode) {
        return &root->data; // Student found in the current node
    }

    // Recursively search the left subtree
    Student* leftResult = searchByCode(root->left, studentCode);
    if (leftResult != nullptr) {
        return leftResult; // Student found in the left subtree
    }

    // Then, recursively search the right subtree
    return searchByCode(root->right, studentCode);
}

void StudentBST::searchAllByName(Node* root, const string& searchName, vector<Student>& matchingStudents) {
    if (root == nullptr) {
        return;
    }

    string searchNameLowered = ToLower(searchName);

    searchAllByName(root->left, searchName, matchingStudents);

    string studentNameLowered = ToLower(root->data.StudentName);

    if (studentNameLowered.find(searchNameLowered) != string::npos) {
        matchingStudents.push_back(root->data);
    }

    searchAllByName(root->right, searchName, matchingStudents);
}

StudentBST::StudentBST() : root(nullptr) {}

void StudentBST::insert(int studentCode, const string& studentName, vector<Class> ucToClasses) {
    Student student(studentCode, studentName);
    student.UcToClasses = ucToClasses;
    root = insert(root, student);
}

Student* StudentBST::searchByCode(int studentCode) {
    return searchByCode(root, studentCode);
}

void StudentBST::searchAllByName(const string& targetName, vector<Student>& matchingStudents) {
    searchAllByName(root, targetName, matchingStudents);
}

Node* StudentBST::getRoot() {
    return root;
}


