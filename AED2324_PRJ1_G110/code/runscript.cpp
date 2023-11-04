/**
 * @file runscript.cpp
 * @brief A simple C++ program that initializes a Script instance and runs it.
 */

#include "Script.h"

using namespace std;

/**
 * @brief The main function of the program.
 *
 * This function is the entry point of the program. It creates an instance of the `Script` class and
 * runs it by invoking the `run` method. After the `Script` instance completes its execution, the program returns 0.
 *
 * @return An integer indicating the exit status of the program (0 for success).
 */
int main() {
    Script script;

    script.run();

    return 0;
}