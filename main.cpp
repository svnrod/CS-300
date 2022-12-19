//============================================================================
// Name        : main.cpp - Project Two
// Author      : Steven Rodas
// Description : Completed code for Project Two. This program is used to give users information about Computer Science
// program courses and it's prerequisites.
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

// struct for Course
struct Course {
    string courseId;
    string courseName;
    vector<string> prerequisite;
};

// struct for Nodes
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course singleCourse) : Node() {
        this->course = singleCourse;
    }
};

// class defining the Binary search tree
class BinarySearchTree {

private:

    void Destruct(Node* node);

public:

    Node* root;
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(BinarySearchTree* tree, Node* node);
    void Search(string courseId);
    void PrintCourse(Node* node);
};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    Destruct(root);
}

// function that is used to destruct a specified node
void BinarySearchTree::Destruct(Node *node) {
    if (node != nullptr) {
        Destruct(node->left);
        node->left = nullptr;
        Destruct(node->right);
        node->right = nullptr;
        delete node;
    }
}

// function to search through binary tree given courseID
void BinarySearchTree::Search(string courseId) {
    Node* currentNode = root;

    while(currentNode != nullptr) {
        if (currentNode->course.courseId == courseId) {
            cout << currentNode->course.courseId << ", ";
            cout << currentNode->course.courseName;
            cout << endl;
            cout << "Prerequisites: ";

            for (string prerequisites : currentNode->course.prerequisite) {
                if (prerequisites == currentNode->course.prerequisite.back()) {

                    cout << prerequisites << endl;

                } else {

                    cout << prerequisites << ", ";
                }
            }

            return;
        }

        else if (courseId < currentNode->course.courseId) {

            if (currentNode->left != nullptr) {
                currentNode = currentNode->left;
            }
        } else {

            currentNode = currentNode->right;
        }
    }

    cout << "Course " << courseId << "not found. " << endl;
    return;
}

// function to insert new data to the binary tree
void BinarySearchTree::Insert(BinarySearchTree *tree, Node *node) {

    if (tree->root == nullptr) {
        tree->root = node;

    } else {

        Node* current = tree->root;

        while(current != nullptr) {

            if (node->course.courseId < current->course.courseId) {
                if (current->left == nullptr) {
                    current->left = node;
                    current = nullptr;
                } else {
                    current = current->left;
                }
            } else {

                if (current->right == nullptr) {
                    current->right = node;
                    current = nullptr;
                } else {
                    current = current->right;
                }
            }
        }
    }
}

// function to print a given course
void BinarySearchTree::PrintCourse(Node *node) {

    if (node == nullptr) {
        return;
    }

    PrintCourse(node->left);
    cout << node->course.courseId << ", ";
    cout << node->course.courseName << endl;
    PrintCourse(node->right);
}


// function to load course data using course_data.txt file
void loadCourse(string txt_file, BinarySearchTree *searchTree) {

    ifstream input_file(txt_file);

    if (input_file.is_open()) {
        cout << "The file has loaded successfully." << endl;

        int num;
        string lines;
        string full;

        while (getline(input_file, lines)) {

            num = 0;
            Node* node = new Node();
            stringstream str(lines);

            while(num < 2) {
                getline(str, full, ',');

                if (num == 0) {

                    node->course.courseId = full;

                } else {
                    node->course.courseName = full;
                }
                num++;
            }

            while (getline(str, full, ',')) {
                node->course.prerequisite.push_back(full);
            }

            searchTree->Insert(searchTree, node);
        }
    }

    else {
        cout << "There is an error. File is not found. Please try again." << endl;
        return;
    }


}

// menu that displays to console for user to read and interact with
void menu() {

    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "4. Exit Program" << endl << endl;
    cout << "What is your selection?: ";
}


// main function
int main() {

    BinarySearchTree* searchTree = new BinarySearchTree();

    string loadedFile;
    string courseSelection;

    int userSelection = 0;

    cout << "Welcome to the course planner." << endl;

    // while loop to get user's selection until user inputs '4' which exits the program.
    while (userSelection != 4) {
        menu();
        cin >> userSelection;

        // switch and case statements to determine what to be done based on user's input selection
        switch (userSelection) {

            case 1:
                cout << endl;
                loadedFile = "course_data.txt";
                loadCourse(loadedFile, searchTree);
                cout << endl;
                break;

            case 2:
                cout << endl;
                cout << "Here is a sample schedule: " << endl << endl;
                searchTree->PrintCourse(searchTree->root);
                cout << endl;
                break;

            case 3:
                cout << endl;
                cout << "What course do you want to know about? ";
                cin >> courseSelection;
                cout << endl;

                transform(courseSelection.begin(), courseSelection.end(), courseSelection.begin(), ::toupper);
                searchTree->Search(courseSelection);

                cout << endl;
                break;

            case 4:
                cout << "Thank you for using the course planner!" << endl;
                break;

            default:
                cout << userSelection << " is not a valid option. Try again." << endl << endl;
                break;

        }
    }

}
