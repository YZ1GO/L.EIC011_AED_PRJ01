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

Node* StudentBST::insertStudent(Node* root, const Student& student) {
    if (root == nullptr) {
        return new Node(student);
    }

    if (student < root->data) {
        root->left = insertStudent(root->left, student);
    } else if (root->data < student) {
        root->right = insertStudent(root->right, student);
    }

    return root;
}

Node* StudentBST::removeStudent(Node *root, int studentCode) {
    if (root == nullptr) {
        return root; // Student not found;
    }

    // If the student to be removed is in the left subtree
    if (studentCode < root->data.StudentCode) {
        root->left = removeStudent(root->left, studentCode);
    }
    // If the student to be removed is in the right subtree
    else if (root->data.StudentCode < studentCode) {
        root->right = removeStudent(root->right, studentCode);
    }
    // If the current node contains the student to be removed
    else {
        // Node with only one child or no child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the in-order successor (smallest in the right subtree)
        Node* temp = getSmallestNode(root->right);

        // Copy the in-order successor's data to this node
        root->data = temp->data;

        // Delete the in-order successor
        root->right = removeStudent(root->right, temp->data.StudentCode);
    }

    return root;
}

Node* StudentBST::getSmallestNode(Node* node) {
    // Find the leftmost node in the BST
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
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

void StudentBST::insertStudent(int studentCode, const string& studentName, vector<Class> ucToClasses) {
    Student student(studentCode, studentName);
    student.UcToClasses = ucToClasses;
    root = insertStudent(root, student);
}

void StudentBST::removeStudent(int studentCode) {
    root = removeStudent(root, studentCode);
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
    // Perform the counting using an in-order traversal
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


int StudentBST::countStudentsInClass(const string& classCode) {
    int count = 0;

    // Define a lambda function to perform the counting
    auto countAction = [&count, &classCode](const Student& student) {
        bool found = false; // Flag to avoid counting the same student multiple times for the same class
        for (const Class& studentClass : student.UcToClasses) {
            string trimmedClassCode = studentClass.ClassCode;
            // Trim leading and trailing white spaces
            trimmedClassCode.erase(trimmedClassCode.begin(), find_if(trimmedClassCode.begin(), trimmedClassCode.end(),
                                                                     [](char c) { return !isspace(c); }));
            trimmedClassCode.erase(find_if(trimmedClassCode.rbegin(), trimmedClassCode.rend(),
                                           [](char c) { return !isspace(c); }).base(), trimmedClassCode.end());

            if (!trimmedClassCode.empty() && trimmedClassCode == classCode && !found) {
                count++;
                found = true; // Mark the student as counted for this class
            }
        }
    };

    // Traverse the BST and count students in the specific class
    inOrderTraversal(root, countAction);

    return count;
}

int StudentBST::countStudentsInUC(const string& ucCode) {
    int count = 0;

    // Define a lambda function to perform the counting
    auto countAction = [&count, &ucCode](const Student& student) {
        for (const Class& studentClass : student.UcToClasses) {
            if (studentClass.UcCode == ucCode) {
                count++;
                break;  // No need to continue checking this student for this UC
            }
        }
    };

    // Traverse the BST and count students in the specific UC
    inOrderTraversal(root, countAction);

    return count;
}

int StudentBST::countStudentsInYear(const string& year) {
    int count = 0;

    // Define a lambda function to perform the counting
    auto countAction = [&count, &year](const Student& student) {
        for (const Class& studentClass : student.UcToClasses) {
            if (!studentClass.ClassCode.empty() && studentClass.ClassCode[0] == year[0]) {
                count++;
                break;  // No need to continue checking this student for this year
            }
        }
    };

    // Traverse the BST and count students in the specific year
    inOrderTraversal(root, countAction);

    return count;
}