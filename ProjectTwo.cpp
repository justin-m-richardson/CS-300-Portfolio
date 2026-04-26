#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// This struct stores the main information for each course from the file.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Each node holds one course and points to the left and right side of the tree.
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    // Places a new course in the tree based on its course number.
    Node* addNode(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }

        if (course.courseNumber < node->course.courseNumber) {
            node->left = addNode(node->left, course);
        }
        else if (course.courseNumber > node->course.courseNumber) {
            node->right = addNode(node->right, course);
        }
        else {
            // If the course already exists, replace the old information with the new information.
            node->course = course;
        }

        return node;
    }

    // Goes through the tree in order so the course list prints from lowest to highest.
    void printInOrder(Node* node) const {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
            printInOrder(node->right);
        }
    }

    // Looks through the tree for the course number entered by the user.
    Course* searchNode(Node* node, string courseNumber) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->course.courseNumber == courseNumber) {
            return &(node->course);
        }
        else if (courseNumber < node->course.courseNumber) {
            return searchNode(node->left, courseNumber);
        }
        else {
            return searchNode(node->right, courseNumber);
        }
    }

    // Frees the memory used by the tree when it is cleared or the program ends.
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        destroyTree(root);
    }

    void clear() {
        destroyTree(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void insert(Course course) {
        root = addNode(root, course);
    }

    void printCourseList() const {
        printInOrder(root);
    }

    Course* search(string courseNumber) const {
        return searchNode(root, courseNumber);
    }
};

// Trims spaces or hidden line characters from the beginning and end of a string.
string trim(string text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    size_t end = text.find_last_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }

    return text.substr(start, end - start + 1);
}

// Makes the course number uppercase so the user can type it either way.
string toUpperCase(string text) {
    for (char& letter : text) {
        letter = toupper(static_cast<unsigned char>(letter));
    }

    return text;
}

// Breaks one line from the CSV file into separate fields.
vector<string> splitLine(string line) {
    vector<string> fields;
    string field;
    stringstream lineStream(line);

    while (getline(lineStream, field, ',')) {
        fields.push_back(trim(field));
    }

    return fields;
}

// Opens the course file and loads each valid course into the binary search tree.
bool loadCourses(string fileName, BinarySearchTree& courseTree) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Could not open file: " << fileName << endl;
        return false;
    }

    courseTree.clear();

    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        lineNumber++;

        if (trim(line).empty()) {
            continue;
        }

        vector<string> fields = splitLine(line);

        if (fields.size() < 2) {
            cout << "Error on line " << lineNumber << ": course number and title are required." << endl;
            continue;
        }

        Course course;
        course.courseNumber = toUpperCase(fields.at(0));
        course.courseTitle = fields.at(1);

        for (size_t i = 2; i < fields.size(); ++i) {
            if (!fields.at(i).empty()) {
                course.prerequisites.push_back(toUpperCase(fields.at(i)));
            }
        }

        courseTree.insert(course);
    }

    inputFile.close();
    return true;
}

// Prints the selected course and shows any prerequisites connected to it.
void printCourseInformation(BinarySearchTree& courseTree) {
    string courseNumber;

    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    courseNumber = toUpperCase(trim(courseNumber));

    Course* course = courseTree.search(courseNumber);

    if (course == nullptr) {
        cout << courseNumber << " was not found." << endl;
        return;
    }

    cout << course->courseNumber << ", " << course->courseTitle << endl;

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";

        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            cout << course->prerequisites.at(i);

            if (i < course->prerequisites.size() - 1) {
                cout << ", ";
            }
        }

        cout << endl;
    }
}

// Keeps the menu separate so it is easier to read and reuse.
void printMenu() {
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << endl;
}

int main() {
    BinarySearchTree courseTree;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        printMenu();
        cout << "What would you like to do? ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "That is not a valid option." << endl;
            continue;
        }

        if (choice == 1) {
            string fileName;

            cout << "Enter the file name: ";
            cin.ignore();
            getline(cin, fileName);
            fileName = trim(fileName);

            if (loadCourses(fileName, courseTree)) {
                cout << "Course data loaded successfully." << endl;
            }
        }
        else if (choice == 2) {
            if (courseTree.isEmpty()) {
                cout << "Please load the course data first." << endl;
            }
            else {
                cout << "Here is a sample schedule:" << endl << endl;
                courseTree.printCourseList();
            }
        }
        else if (choice == 3) {
            if (courseTree.isEmpty()) {
                cout << "Please load the course data first." << endl;
            }
            else {
                printCourseInformation(courseTree);
            }
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}