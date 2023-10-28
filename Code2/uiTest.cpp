#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Define a structure to represent a menu item
struct MenuItem {
    string label;
    void (*action)();
};

// Function to clear the terminal screen
void clearScreen() {
    system("clear"); // For Unix/Linux
    // system("cls"); // For Windows
}

void actionOption1() {
    clearScreen();
    cout << "Option 1 selected." << endl;
}

void actionOption2() {
    clearScreen();
    cout << "Option 2 selected." << endl;
}

void actionOption3() {
    clearScreen();
    cout << "Option 3 selected." << endl;
}

void actionGoBack() {
    clearScreen();
    cout << "Going back to the previous menu." << endl;
}

// Implement the actions for your specific menu items
void searchSchedule() {
    clearScreen();
    cout << "Search Schedule selected." << endl;
    // Implement your code for searching the schedule here
}

void searchStudent() {
    clearScreen();
    cout << "Search Student selected." << endl;
    // Implement your code for searching students here
}

void searchUCOccupations() {
    clearScreen();
    cout << "Search UC Occupations selected." << endl;

    vector<MenuItem> ucOccupationsMenu = {
            {"Option 1", actionOption1},
            {"Option 2", actionOption2},
            {"Option 3", actionOption3},
            {"Go Back", actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        cout << "UC Occupations Menu:" << endl;
        for (int i = 0; i < ucOccupationsMenu.size(); i++) {
            cout << i + 1 << ". " << ucOccupationsMenu[i].label << endl;
        }
        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 4) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= ucOccupationsMenu.size()) {
            ucOccupationsMenu[choice - 1].action();
        }
    }
    // Implement your code for searching UC occupations here
}

void searchYearOccupations() {
    clearScreen();
    cout << "Search Year Occupations selected." << endl;
    // Implement your code for searching year occupations here
}

int main() {
    vector<MenuItem> mainMenu = {
            {"Search", nullptr},
            {"Changes", nullptr},
            {"Exit", nullptr}
    };

    vector<MenuItem> searchMenu = {
            {"Schedule", searchSchedule},
            {"Student", searchStudent},
            {"UC Occupations", searchUCOccupations},
            {"Year Occupations", searchYearOccupations},
            {"Go Back", nullptr}
    };

    bool exitMenu = false;

    while (!exitMenu) {
        clearScreen();
        cout << "Main Menu:" << endl;
        for (int i = 0; i < mainMenu.size(); i++) {
            cout << i + 1 << ". " << mainMenu[i].label << endl;
        }

        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice >= 1 && choice <= mainMenu.size()) {
            if (mainMenu[choice - 1].action != nullptr) {
                mainMenu[choice - 1].action();
            } else if (choice == 1) {
                bool exitSubMenu = false;
                while (!exitSubMenu) {
                    clearScreen();
                    cout << "Search Menu:" << endl;
                    for (int i = 0; i < searchMenu.size(); i++) {
                        cout << i + 1 << ". " << searchMenu[i].label << endl;
                    }
                    int subChoice;
                    cout << "Enter your choice: ";
                    if (!(cin >> subChoice)) {
                        // Invalid input (not an integer)
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (subChoice == 5) {
                        exitSubMenu = true;
                    } else if (subChoice >= 1 && subChoice <= searchMenu.size()) {
                        if (searchMenu[subChoice - 1].action != nullptr) {
                            searchMenu[subChoice - 1].action();
                        }
                    }
                }
            } else {
                exitMenu = true;
            }
        }
    }

    cout << "Goodbye!" << endl;

    return 0;
}
