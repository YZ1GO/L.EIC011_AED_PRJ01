#include "Data.h"

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

Node* StudentBST::searchByCode(Node* root, int studentCode) {
    if (root == nullptr || root->data.StudentCode == studentCode) {
        return root;
    }

    if (studentCode < root->data.StudentCode) {
        return searchByCode(root->left, studentCode);
    } else {
        return searchByCode(root->right, studentCode);
    }
}

Node* StudentBST::searchByName(Node* root, const string& studentName) {
    if (root == nullptr || root->data.StudentName == studentName) {
        return root;
    }

    if (studentName < root->data.StudentName) {
        return searchByName(root->left, studentName);
    } else {
        return searchByName(root->right, studentName);
    }
}

StudentBST::StudentBST() : root(nullptr) {}

void StudentBST::insert(int studentCode, const string& studentName, vector<Class> ucToClasses) {
    Student student(studentCode, studentName);
    student.UcToClasses = ucToClasses;
    root = insert(root, student);
}

Student* StudentBST::searchByCode(int studentCode) {
    Node* result = searchByCode(root, studentCode);
    if (result) {
        return &result->data;
    }
    return nullptr;
}

Student* StudentBST::searchByName(const string& studentName) {
    Node* result = searchByName(root, studentName);
    if (result) {
        return &result->data;
    }
    return nullptr;
}

Node* StudentBST::getRoot() {
    return root;
}


Global::Global(vector<Class> classes, vector<Schedule> schedules, StudentBST students)
    : Classes(classes), Schedules(schedules), Students(students) {}

Global::Global(vector<Class> classes) : Classes(classes) {}

Global::Global(vector<Schedule> schedules) : Schedules(schedules) {}

Global::Global(StudentBST students) : Students(students) {}

Global::Global() {}
