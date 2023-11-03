/**
 * @file Data.cpp
 *
 * Implementation of the classes and functions defined in Data.h.
 */

#include "Data.h"

/**
 * @brief Default constructor for the Class class.
 */
Class::Class() {}

/**
 * @brief Constructor for the Class class.
 *
 * @param ucCode The UC code associated with the class.
 * @param classCode The class code.
 */
Class::Class(string ucCode, string classCode)
    : UcCode(ucCode), ClassCode(classCode) {}

/**
 * @brief Equality operator for comparing two Class objects.
 *
 * @param other The Class object to compare with.
 * @return True if the objects are equal, false otherwise.
 */
bool Class::operator==(const Class& other) const{
    return (UcCode==other.UcCode) && (ClassCode==other.ClassCode);
}

/**
 * @brief Less than operator for comparing two Class objects.
 *
 * @param other The Class object to compare with.
 * @return True if this object is less than the other object, false otherwise.
 */
bool Class::operator<(const Class& other) const{
    if (UcCode != other.UcCode){
        return ClassCode < other.ClassCode;
    }
    return UcCode < other.UcCode;
}

/**
 * @brief Default constructor for the Schedule class.
 */
Schedule::Schedule(){}

/**
 * @brief Constructor for the Schedule class.
 *
 * @param ucToClass The associated Class object.
 * @param weekday The weekday of the schedule.
 * @param startHour The start hour of the schedule.
 * @param duration The duration of the schedule.
 * @param type The type of the schedule.
 */
Schedule::Schedule(Class ucToClass, string weekday, float startHour, float duration, string type)
        : UcToClasses(ucToClass), WeekDay(weekday), StartHour(startHour), Duration(duration), Type(type){}

/**
 * @brief Less than operator for comparing Schedule objects.
 *
 * This operator compares Schedule objects first by weekday (Monday to Friday order) and then by start hour.
 *
 * @param other The Schedule object to compare with.
 * @return True if this object is less than the other object, false otherwise.
 */
bool Schedule::operator<(const Schedule& other) const {
    // Compare first by weekDay, with Monday coming before Friday.
    if (WeekDay != other.WeekDay) {
        static const string weekdays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        auto it1 = find(weekdays, weekdays + 5, WeekDay);
        auto it2 = find(weekdays, weekdays + 5, other.WeekDay);

        // Check if both weekdays are found in the weekdays array.
        if (it1 != weekdays + 5 && it2 != weekdays + 5) {
            // Compare the positions of the weekdays in the array.
            return it1 - weekdays < it2 - weekdays;
        }
    }

    // If the weekDay is the same, compare by startHour.
    return StartHour < other.StartHour;
}

/**
 * @brief Default constructor for the Student class.
 */
Student::Student() {}

/**
 * @brief Constructor for the Student class.
 *
 * @param studentCode The student code.
 * @param studentName The name of the student.
 */
Student::Student(const int studentCode, const string studentName) :
    StudentCode(studentCode), StudentName(studentName){}

/**
 * @brief Less than operator for comparing Student objects.
 *
 * @param other The Student object to compare with.
 * @return True if this object is less than the other object, false otherwise.
 */
bool Student::operator<(const Student &other) const {
    return StudentName < other.StudentName;
}

/**
 * @brief Helper function to insert a student into the Binary Search Tree (BST).
 *
 * This recursive function inserts a new student into the BST by comparing the student's data with the
 * data in the current node. If the current node is null (the subtree is empty), it creates a new node
 * with the given student and returns it. If the student data is less than the data in the current node,
 * it recursively inserts the student into the left subtree. If the student data is greater, it recursively
 * inserts the student into the right subtree.
 *
 * @param root The root node of the current subtree.
 * @param student The Student object to insert into the BST.
 * @return The root of the updated subtree after insertion.
 */
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

/**
 * @brief Perform an in-order traversal of the Binary Search Tree (BST) starting from the given node
 * and execute a specified action for each node.
 *
 * This function performs an in-order traversal of the BST, visiting nodes in ascending order. For each
 * node, it executes the specified action.
 *
 * @param node The current node in the traversal.
 * @param action The action to be executed for each node.
 */
void StudentBST::inOrderTraversal(Node* node, function<void(const Student&)> action) {
    if (node == nullptr) {
        return;
    }

    inOrderTraversal(node->left, action);  // Traverse left subtree
    action(node->data);                             // Perform action on the current node
    inOrderTraversal(node->right, action); // Traverse right subtree
}

/**
 * @brief Search for a student with a specific student code in the BST.
 *
 * This function recursively searches the BST to find a student with the given student code.
 *
 * @param root The root of the current subtree.
 * @param studentCode The student code to search for.
 * @return A pointer to the Student object if found, or nullptr if not found.
 */
Student* StudentBST::searchByCode(Node* root, const int& studentCode) {
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

/**
 * @brief Construct an empty StudentBST.
 *
 * This constructor initializes an empty StudentBST by setting the root pointer to nullptr.
 */
StudentBST::StudentBST() : root(nullptr) {}

/**
 * @brief Get the root node of the BST.
 *
 * @return A pointer to the root node of the BST.
 */
Node* StudentBST::getRoot() {
    return root;
}

/**
 * @brief Set the root node of the BST.
 *
 * @param newRoot A pointer to the new root node of the BST.
 */
void StudentBST::setRoot(Node* newRoot) {
    root = newRoot;
}

/**
 * @brief Insert a student into the BST.
 *
 * This function inserts a student into the BST using the Binary Search Tree property.
 * If the student's data is less than the current node's data, it's inserted into the left subtree;
 * if greater, it's inserted into the right subtree.
 *
 * @param studentCode The student's unique code.
 * @param studentName The student's name.
 * @param ucToClasses A vector of Class objects representing the student's classes.
 */
void StudentBST::insertStudent(const int& studentCode, const string& studentName, vector<Class> ucToClasses) {
    Student student(studentCode, studentName);
    student.UcToClasses = ucToClasses;
    root = insertStudent(root, student);
}

/**
 * @brief Search for a student with a specific student code in the BST.
 *
 * This function initiates the search for a student with the given student code by calling the
 * recursive search function and providing the root of the BST.
 *
 * @param studentCode The student code to search for.
 * @return A pointer to the Student object if found, or nullptr if not found.
 */
Student* StudentBST::searchByCode(const int& studentCode) {
    return searchByCode(root, studentCode);
}

/**
 * @brief Search for students by name and store matching students in a vector.
 *
 * This function searches for students whose names contain the specified search string and adds
 * matching students to the provided vector.
 *
 * @param searchName The name or part of the name to search for.
 * @param matchingStudents A vector to store the matching Student objects.
 */
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

/**
 * @brief Search for students registered in at least 'n' UCs and store matching students in a set.
 *
 * This function searches for students who are registered in at least 'n' UCs and adds matching
 * students to the provided set.
 *
 * @param n The minimum number of UCs a student must be registered in to be considered a match.
 * @param matchingStudents A set to store the matching Student objects.
 */
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

/**
 * @brief Search for students based on a custom search criteria and store matching students in a set.
 *
 * This function searches for students based on a custom search criteria provided as a function.
 * It adds matching students to the provided set.
 *
 * @param searchCriteria A function that defines the custom search criteria for Class objects.
 * @param matchingStudents A set to store the matching Student objects.
 */
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

/**
 * @brief Count the number of students in all classes for a specific course unit.
 *
 * This function counts the number of students who are registered in all class
 * for a specific course unit and stores the counts in a map.
 *
 * @param ucCode The unique code of the UC.
 * @param classStudentsCount A map to store the counts of students in each class.
 */
void StudentBST::getStudentsCountInClass(const string& ucCode, map<string, int>& classStudentsCount) {
    // Define a lambda function to perform the counting
    auto countAction = [&classStudentsCount, &ucCode](const Student& student) {
        // Action to perform on each node (in this case, searching by uc code)
        for (const Class& studentClass : student.UcToClasses) {
            if (studentClass.UcCode == ucCode) {
                classStudentsCount[studentClass.ClassCode]++;
                break;
            }
        }
    };

    // Perform the counting using an in-order traversal
    inOrderTraversal(root, countAction);
}

/**
 * @brief Count the number of students in a all UCs for a specified academic year.
 *
 * This function counts the number of students who are registered in all UCs
 * for a specified academic year and stores the counts in a map.
 *
 * @param ucCode The unique code of the UC.
 * @param ucStudentsCount A map to store the counts of students in each UC.
 */
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

/**
 * @brief Count the number of students in a specific class.
 *
 * This function counts the number of students who are registered in the specified class and returns the count.
 *
 * @param classCode The class code to count students in.
 * @return The number of students in the specified class.
 */
int StudentBST::countStudentsInClass(const string& classCode) {
    int count = 0;

    // Define a lambda function to perform the counting
    auto countAction = [&count, &classCode](const Student& student) {
        bool found = false; // Flag to avoid counting the same student multiple times for the same class
        for (const Class& studentClass : student.UcToClasses) {
            if (studentClass.ClassCode == classCode) {
                count++;
                break; // No need to continue checking this student for this class
            }
        }
    };

    // Traverse the BST and count students in the specific class
    inOrderTraversal(root, countAction);

    return count;
}

/**
 * @brief Count the number of students in a specific UC (course).
 *
 * This function counts the number of students who are registered in the specified UC (course) and returns the count.
 *
 * @param ucCode The UC code to count students in.
 * @return The number of students in the specified UC (course).
 */
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

/**
 * @brief Count the number of students based on the first character of their class code.
 *
 * This function counts the number of students whose class code starts with a specified character
 * and returns the count.
 *
 * @param year The character representing the class code's year (e.g., 'A', 'B').
 * @return The number of students with class codes starting with the specified character.
 */
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

/**
 * @brief Save students data to a CSV file.
 *
 * This function saves all students data to a CSV file.
 *
 * @param filename The name of the CSV file to save the data to.
 */
void StudentBST::saveToCSV(const string& filename) {
    ofstream csvFile(filename);

    if (!csvFile.is_open()) {
        cerr << "Failed to open CSV file." << endl;
        return;
    }

    csvFile << "StudentCode,StudentName,UcCode,ClassCode" << endl;

    auto writeStudentToCSV = [&csvFile](const Student& student) {
        for (const Class& ucClass : student.UcToClasses) {
            csvFile << student.StudentCode << "," << student.StudentName << ","
                    << ucClass.UcCode << "," << ucClass.ClassCode << endl;
        }
    };

    inOrderTraversal(root, writeStudentToCSV);
    csvFile.close();
}
