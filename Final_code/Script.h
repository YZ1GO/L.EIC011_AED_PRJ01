/**
 * @file Script.h
 * @brief Defines the Script class for interacting with the "LEIC Schedules" system.
 */

#ifndef SCRIPT_H
#define SCRIPT_H

#include "Consult.h"
#include "Change.h"
#include <vector>
#include <limits>
#include <queue>

/**
 * @struct ChangeClassRequest
 * @brief Represents a request to change a student's class.
 */
struct ChangeClassRequest {
    Student* student;        ///< A pointer to the student for whom the change is requested.
    string currentUcCode;    ///< The current UC (University Course) code of the student.
    string currentClassCode; ///< The current class code of the student.
    string newClassCode;     ///< The desired new class code for the student.
};

/**
 * @struct ChangeUcRequest
 * @brief Represents a request to change a student's UC (University Course).
 */
struct ChangeUcRequest {
    Student* student;        ///< A pointer to the student for whom the change is requested.
    string currentUcCode;    ///< The current UC code of the student.
    string currentClassCode; ///< The current class code of the student.
    string newUcCode;        ///< The desired new UC code for the student.
};

/**
 * @struct LeaveUcClassRequest
 * @brief Represents a request for a student to leave a specific UC and class.
 */
struct LeaveUcClassRequest {
    Student* student;        ///< A pointer to the student who wishes to leave.
    string currentUcCode;    ///< The UC code of the UC the student wants to leave.
    string currentClassCode; ///< The class code of the class the student wants to leave.
};

/**
 * @struct JoinUcClassRequest
 * @brief Represents a request for a student to join a specific UC and class.
 */
struct JoinUcClassRequest {
    Student* student; ///< A pointer to the student who wishes to join.
    string newUcCode; ///< The UC code of the UC the student wants to join.
};

/**
 * @struct SwapClassesRequest
 * @brief Represents a request for two students to swap classes within the same UC.
 */
struct SwapClassesRequest {
    Student* student1; ///< A pointer to the first student involved in the class swap.
    string ucCode;     ///< The UC code to which the swap pertains.
    string classCode1; ///< The class code of the first student.
    Student* student2; ///< A pointer to the second student involved in the class swap.
    string classCode2; ///< The class code of the second student.
};

/**
 * @struct ChangeRequest
 * @brief Represents a generic change request, which can be of various types (changing class, changing UC, leaving UC and class, joining UC and class, or swapping classes).
 */
struct ChangeRequest {
    string requestType; ///< A string indicating the type of change request (e.g., "ChangeClassRequest").
    variant<ChangeClassRequest, ChangeUcRequest, LeaveUcClassRequest, JoinUcClassRequest, SwapClassesRequest> requestData; ///< A variant that can hold any of the specific request types, allowing for flexibility in managing different types of requests.
};

/**
 * @class Script
 * @brief Main script for interacting with the "LEIC Schedules" system.
 *
 * The `Script` class provides a menu-driven interface for users and administrators
 * to manage academic data, process change requests, and access consultation features.
 */
class Script {
public:
    /**
     * Constructor for the Script class.
     */
    Script();

    /**
     * Run the main script and interact with the user.
     */
    void run();

    /**
     * Queue of change requests waiting to be processed.
     */
    queue<ChangeRequest> changeRequestQueue;

    /**
     * List of All change request log
     */
    vector<ChangeLogEntry> changeLogs;

private:
    /**
     * @struct MenuItem
     * Structure for defining menu items.
     */
    struct MenuItem {
        string label;
        void (Script::*action)(); ///< Function pointer to the action associated with the menu item.
    };

    System system; ///< The academic system used for data management.
    Global global; ///< The global data used by the script.
    Consult consult; ///< The consultation component for accessing academic data.
    const string adminPassword = "12345"; ///< The administrator's password.

    /**
     * A map to keep track of students with pending change requests.
     * The key is the student code, and the value is a boolean indicating if a request is pending.
     */
    map<int, bool> studentHasPendingRequest;

    /**
     * Draw a text box with the specified text.
     * @param text The text to display in the box.
     */
    void drawBox(const string& text);

    /**
     * Display a menu with a list of menu items and return the user's choice.
     * @param menuName The name of the menu.
     * @param menuItems A vector of menu items.
     * @return The user's choice as an integer.
     */
    int showMenu(const string& menuName, const vector<MenuItem>& menuItems);

    /**
     * Clear the screen of the terminal
     */
    void clearScreen();

    /**
     * Action to go back to the previous menu.
     */
    void actionGoBack();

    /**
     * Delay before to go back to the previous menu, forcing user to press any key
     */
    void backToMenu();

    /**
     * Update the global data with the provided data.
     * @param global The global data to update with.
     */
    void updateData(Global global);

    /**
     * Undo the last succeed change.
     */
    void undoAction();

    /**
     * @brief Displays a submenu for searching and consulting schedules.
     *
     * This function presents a submenu for searching and consulting academic schedules,
     * allowing the user to choose between viewing a student's schedule, a class's schedule,
     * or returning to the main menu.
     *
     * The submenu options are displayed until the user selects to go back to the main menu.
     */
    void searchSchedule();

    /**
     * @brief Displays a submenu for searching and consulting student information.
     *
     * This function presents a submenu for searching and consulting student information.
     * Users can choose to search for a student by their code or name, or return to the main menu.
     *
     * The submenu options are displayed until the user selects to go back to the main menu.
     */
    void searchStudent();

    /**
     * @brief Displays a submenu for searching class and UC occupation information.
     *
     * This function presents a submenu for searching the occupation information of classes, UCs, and years.
     * Users can choose to view the occupation of classes, UCs, or years, or return to the main menu.
     *
     * The submenu options are displayed until the user selects to go back to the main menu.
     */
    void searchAllOccupations();

    /**
     * @brief Displays a submenu for searching specific class and UC occupation information.
     *
     * This function presents a submenu for searching the occupation information of classes of a specific UC or UCs of a specific year.
     * Users can choose to view the occupation of classes of a UC, UCs of a year, or return to the main menu.
     *
     * The submenu options are displayed until the user selects to go back to the main menu.
     */
    void searchSpecificOccupation();

    /**
     * @brief Displays a submenu for listing students in different contexts.
     *
     * This function presents a submenu that allows users to list students in various contexts, including classes, UCs, or years. Users can choose to view a list of students in a specific class, UC, or year, or return to the main menu.
     *
     * The submenu options are displayed until the user selects to go back to the main menu.
     */
    void searchListOfStudents();

    /**
     * @brief Displays the student schedule.
     *
     * This function allows users to consult a student's schedule.
     */
    void consultTheScheduleOfStudent();

    /**
     * @brief Displays the class schedule.
     *
     * This function allows users to consult a class's schedule.
     */
    void consultTheScheduleOfClass();

    /**
     * @brief Searches for a student information by student code.
     *
     * Users can search for a student by entering a student code.
     */
    void findStudentByCode();

    /**
     * @brief Searches for a student information by student name.
     *
     * Users can search for a student by entering a student name.
     */
    void listStudentsByName();

    /**
     * @brief Displays the occupation of all Classes.
     */
    void occupationOfClasses();

    /**
     * @brief Displays the occupation of all UCs.
     */
    void occupationOfUcs();

    /**
     * @brief Displays the occupation of all Years (1-3).
     */
    void occupationOfYears();

    /**
     * @brief Displays the occupation of Classes of a UC.
     */
    void occupationOfClassesOfUc();

    /**
     * @brief Displays the occupation of UCs of a Year.
     */
    void occupationOfUcsOfYear();

    /**
     * @brief Displays the list of students enrolled in a Class.
     */
    void listOfStudentsInClass();

    /**
     * @brief Displays the list of students enrolled in a UC.
     */
    void listOfStudentsInUc();

    /**
     * @brief Displays the list of students enrolled in a Year.
     */
    void listOfStudentsInYear();

    /**
     * @brief Displays the list of students registered in at least 'N' UCs.
     */
    void listOfStudentsInAtLeastNUCs();

    /**
     * @brief Displays pending change requests for a specific student and handles cancellation.
     *
     * This function shows the pending change request for a specific student identified by their student code.
     * It allows the user to cancel a pending request.
     *
     * @param studentCode The student code for which pending requests should be displayed and managed.
     */
    void pendingRequest(const int& studentCode);

    /**
     * @brief Initiates the process for changing a student's class.
     *
     * This function initiates the process for changing a student's class within a specific UC. It collects the necessary data
     * and adds a change request to the queue for further processing.
     */
    void changeClass();

    /**
     * @brief Initiates the process for changing a student's UC.
     *
     * This function initiates the process for changing a student's UC, including selecting a new UC.
     * It collects the necessary data and adds a change request to the queue for further processing.
     */
    void changeUC();

    /**
     * @brief Initiates the process for a student to leave a UC and class.
     *
     * This function initiates the process for a student to leave their current UC and class.
     * It collects the necessary data and adds a change request to the queue for further processing.
     */
    void leaveUCAndClass();

    /**
     * @brief Initiates the process for a student to join a UC and class.
     *
     * This function initiates the process for a student to join a specific UC.
     * It collects the necessary data and adds a change request to the queue for further processing.
     */
    void joinUCAndClass();

    /**
     * @brief Initiates the process for swapping classes between two students.
     *
     * This function initiates the process for swapping classes between two students within the same UC.
     * It collects the necessary data and adds a change request to the queue for further processing.
     */
    void swapClassesBetweenStudents();

    /**
     * @brief Processes a change request from the queue.
     *
     * This function processes the next change request from the queue, applying the requested change to the student's data.
     * After processing, the request is removed from the queue, and relevant data and change logs are updated.
     */
    void processRequest();

    /**
     * @brief Allows the Administrator to process all change requests in the queue.
     *
     * This function allows the administrator to process all the change requests from the queue, applying the requested change to the student's data.
     * After processing, the request is removed from the queue, and relevant data and change logs are updated. If there are no pending
     * change requests, it informs the admin.
     */
    void processNextChangeRequest();

    /**
     * @brief Allows the Administrator to process the next change request in the queue.
     *
     * This function allows the administrator to process the next change request from the queue, applying the requested change to the student's data.
     * After processing, the request is removed from the queue, and relevant data and change logs are updated. If there are no pending
     * change requests, it informs the admin.
     */
    void processAllChangeRequests();

    /**
     * @brief Displays the change logs menu, allowing administrators to view different types of change logs.
     *
     * This function presents a menu to the admin, where they can choose to view different types of change logs, such as all change logs,
     * successful change logs, and unsuccessful (failed) change logs. The admin can navigate through these logs and perform actions
     * such as undoing the last change if allowed.
     */
    void changeLogsMenu();

    /**
     * @brief Displays all change logs, including both successful and unsuccessful changes.
     *
     * This function displays a list of all change logs, which include information about the requested changes, timestamps, student details,
     * state (accepted or denied), and any additional notes. If there are no logs, it informs the admin accordingly.
     */
    void allChangeLogs();

    /**
     * @brief Displays successful change logs and provides options for undoing the last change.
     *
     * This function presents successful change logs, which include accepted changes, to the user. It allows the admin to undo the last change if they choose to.
     * The function also provides an option to go back to the previous menu.
     */
    void successfulChangeLogs();

    /**
     * @brief Displays unsuccessful (failed) change logs.
     *
     * This function displays a list of change logs that represent changes that were denied or unsuccessful. It includes information about the
     * requested changes, timestamps, student details, and the reason of why they were denied. If there are no failed change logs, it informs the user accordingly.
     */
    void failedChangeLogs();

    /**
     * @brief Saves the updated student data to a CSV file.
     *
     * This function saves the updated student data to a CSV (Comma-Separated Values) file named "students_updated.csv".
     * It provides feedback to the user, indicating whether the file output was successful.
     */
    void printToFile();
};

#endif // SCRIPT_H