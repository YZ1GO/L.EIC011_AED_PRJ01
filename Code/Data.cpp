#include "Data.h"

using namespace std;

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

void StudentBST::inOrderTraversal(Node* node, function<void(const Student&)> action) {
    if (node == nullptr) {
        return;
    }

    inOrderTraversal(node->left, action);  // Traverse left subtree
    action(node->data);                             // Perform action on the current node
    inOrderTraversal(node->right, action); // Traverse right subtree
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




StudentBST::StudentBST() : root(nullptr) {}

Node* StudentBST::getRoot() {
    return root;
}

void StudentBST::insert(int studentCode, const string& studentName, vector<Class> ucToClasses) {
    Student student(studentCode, studentName);
    student.UcToClasses = ucToClasses;
    root = insert(root, student);
}

Student* StudentBST::searchByCode(int studentCode) {
    return searchByCode(root, studentCode);
}

void StudentBST::searchAllByName(const string& searchName, vector<Student>& matchingStudents) {
    // Define a lambda function to perform the search by name
    auto searchByNameAction = [&matchingStudents, &searchName](const Student& student) {
        // Action to perform on each node (in this case, searching by name)
        string searchNameLowered = ToLower(searchName);
        string studentNameLowered = ToLower(student.StudentName);

        if (studentNameLowered.find(searchNameLowered) != string::npos) {
            matchingStudents.push_back(student);
        }
    };

    // Call the inOrderTraversal function to populate matchingStudents
    inOrderTraversal(root, searchByNameAction);
}

void StudentBST::searchStudentsInAtLeastNUCs(const int n, set<Student>& matchingStudents) {
    // Define a lambda function to perform the search for students registered in at least n UCs
    auto searchStudentsInAtLeastNUCsAction = [&matchingStudents, &n](const Student& student) {
        // Action to perform on each node (in this case, searching for students registered in at least n UCs)
        if (student.UcToClasses.size() >= static_cast<size_t>(n)) {
            matchingStudents.insert(student);
        }
    };

    // Call the inOrderTraversal function to populate matchingStudents
    inOrderTraversal(root, searchStudentsInAtLeastNUCsAction);
}

void StudentBST::searchStudentsWithin(const function<bool(const Class&)> searchCriteria, set<Student>& matchingStudents) {
    // Define a lambda function to perform the search by class code
    auto searchStudentsAction = [&matchingStudents, &searchCriteria](const Student& student) {
        // Action to perform on each node
        for (const Class& ucClass : student.UcToClasses) {
            if (searchCriteria(ucClass)) {
                // Found a student
                matchingStudents.insert(student);
                break;  // No need to check this student anymore
            }
        }
    };

    // Call the inOrderTraversal function to populate studentsOfTheClass
    inOrderTraversal(root, searchStudentsAction);
}


void StudentBST::getStudentsCountInClass(const string& ucCode, map<string, int>& classStudentsCount) {
    // Define a lambda function to perform the counting
    auto countAction = [&classStudentsCount, &ucCode](const Student& student) {
        // Action to perform on each node (in this case, searching by uc code)
        for (const Class& studentClass : student.UcToClasses) {
            if (studentClass.UcCode == ucCode) {
                string trimmedClassCode = studentClass.ClassCode;
                // Trim leading and trailing white spaces
                trimmedClassCode.erase(trimmedClassCode.begin(), find_if(trimmedClassCode.begin(), trimmedClassCode.end(),
                                                                         [](char c) { return !isspace(c); }));
                trimmedClassCode.erase(find_if(trimmedClassCode.rbegin(), trimmedClassCode.rend(),
                                               [](char c) { return !isspace(c); }).base(), trimmedClassCode.end());

                if (!trimmedClassCode.empty()) {
                    classStudentsCount[trimmedClassCode]++;
                }
            }
        }
    };

    // Perform the counting using an in-order traversal
    inOrderTraversal(root, countAction);
}

void StudentBST::getStudentsCountInUc(const string& ucCode, map<string, int>& ucStudentsCount) {
    auto countAction = [&ucStudentsCount, &ucCode](const Student& student) {
        for (const Class& studentClass : student.UcToClasses) {
            if (studentClass.UcCode == ucCode) {
                ucStudentsCount[ucCode]++;
                break;  // No need to continue checking this student for this UC
            }
        }
    };

    // Perform the counting using an in-order traversal
    inOrderTraversal(root, countAction);
}