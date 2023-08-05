#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;


struct node {
    long long phoneNumber;
    string name;
    bool isRed; // Color of node: true for red, false for black
    node* left;
    node* right;
    node* parent;

    // Constructor for creating a new node
    node(long long phoneNumber, const string& name) : phoneNumber(phoneNumber), name(name), isRed(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

class redBlackTree {

private:
    node* root;

    // Helper functions for balancing the tree
    node* rotateLeft(node* currentNode); // Done
    node* rotateRight(node* currentNode); // Done
    node* rotateRightLeft(node* parent); // Done
    node* rotateLeftRight(node* parent); // Done
    void maintainProperties(node* currentNode); // Done

    //Implementation Helpers
    void searchNameHelper(const string& name,  node* currentNode, bool& exists); // Done
    void getFullAreaCode(node* currentNode, int wantedAreaCode, bool& exists); // Done

    //Destructor Helper
    void destructorHelper(node* currentNode); // Done

    //Traversal
    void inOrderTraversal(node* currentNode); // Done
    void inOrderTraversal(node* currentNode, int wantedAreaCode); // Done

public:
    
    //Constructor
    redBlackTree(); // Done

    //Destructor
    ~redBlackTree(); // Done

    // Public functions for the required operations
    void insert(long long phoneNumber, const string& name); // Done
    void searchNumber(long long phoneNumber); // Done
    void searchName(const string& name); // Done
    void printAreaCode(int wantedAreaCode); // Done
    void printAllNumbers(); // Done
};