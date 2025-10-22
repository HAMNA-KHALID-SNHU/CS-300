//============================================================================
// Name        : CS-300-PROJECT-TWO-BY-2902671.cpp
// Author      : HAMNA KHALID
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
/*
 * CS-300 DSA: Analysis and Design
 * Project Two – Advising Assistance Program
 *
 * Author: HAMNA KHALID
 * SNHU ID: 2902671
 * Professor: SATHISH GOPALAKRISHNAN
 * Date: October 19, 2025
 *
 * Description:
 * This program reads a list of Computer Science courses and their prerequisites,
 * stores them in a hash-based table, and allows users to view the full course list
 * or search for individual courses. The data is loaded from a CSV file and displayed
 * in alphanumeric order. Menu options allow loading, listing, searching, and exiting.
 */

//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// ===================== STRUCT FOR COURSE =====================
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// ===================== HASH TABLE USING MAP =====================
typedef map<string, Course> CourseTable;

// ===================== FUNCTION DECLARATIONS =====================
void loadCourses(CourseTable& courses, const string& fileName);
void printCourseList(const CourseTable& courses);
void printCourse(const CourseTable& courses, const string& courseNumber);
void displayMenu();

// ===================== LOAD COURSES FROM FILE =====================
void loadCourses(CourseTable& courses, const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Unable to open file '" << fileName << "'." << endl;
        return;
    }

    courses.clear();
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string courseNumber, title, prereq;
        vector<string> prereqs;

        getline(ss, courseNumber, ',');
        getline(ss, title, ',');

        // collect remaining prerequisites
        while (getline(ss, prereq, ',')) {
            prereqs.push_back(prereq);
        }

        Course c;
        c.courseNumber = courseNumber;
        c.title = title;
        c.prerequisites = prereqs;

        courses[courseNumber] = c;
    }

    file.close();
    cout << "Courses loaded successfully from '" << fileName << "'!" << endl;
}

// ===================== PRINT ALL COURSES =====================
void printCourseList(const CourseTable& courses) {
    if (courses.empty()) {
        cout << "Error: No courses loaded yet. Please load data first." << endl;
        return;
    }

    vector<string> keys;
    for (const auto& pair : courses) {
        keys.push_back(pair.first);
    }

    sort(keys.begin(), keys.end()); // ensure alphanumeric order

    cout << "\nHere is a sample schedule:\n" << endl;
    for (const auto& key : keys) {
        cout << key << ", " << courses.at(key).title << endl;
    }
    cout << endl;
}

// ===================== PRINT A SPECIFIC COURSE =====================
void printCourse(const CourseTable& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);

    if (it == courses.end()) {
        cout << "Error: Course not found." << endl;
        return;
    }

    const Course& c = it->second;
    cout << c.courseNumber << ", " << c.title << endl;

    if (!c.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < c.prerequisites.size(); ++i) {
            cout << c.prerequisites[i];
            if (i < c.prerequisites.size() - 1)
                cout << ", ";
        }
        cout << endl;
    } else {
        cout << "Prerequisites: None" << endl;
    }
}

// ===================== DISPLAY MENU =====================
void displayMenu() {
    cout << "\n1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "4. Exit" << endl;
}

// ===================== MAIN FUNCTION =====================
int main() {
    CourseTable courses;
    string fileName;
    int choice = 0;
    bool dataLoaded = false;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter the filename of the course data (or press Enter for default ABCU_Advising_Program_Input.csv): ";
            getline(cin, fileName);

            if (fileName.empty()) {
                fileName = "ABCU_Advising_Program_Input.csv";
                cout << "Using default file: " << fileName << endl;
            }

            loadCourses(courses, fileName);
            if (!courses.empty()) dataLoaded = true;

        } else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Error: No courses loaded yet. Please load the file first (Option 1)." << endl;
            } else {
                printCourseList(courses);
            }

        } else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Error: No courses loaded yet. Please load the file first (Option 1)." << endl;
            } else {
                cout << "What course do you want to know about? ";
                string courseNum;
                getline(cin, courseNum);
                printCourse(courses, courseNum);
            }

        } else if (choice == 4) {
            cout << "\nThank you for using the course planner. Goodbye!" << endl;
            // close any open resources and safely exit to avoid exe lock
            cin.clear();
            cout.flush();
            return 0;

        } else {
            cout << "Invalid selection. Please try again." << endl;
        }
    }
}
