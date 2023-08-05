#include "redBlackTree.h"
#include <iomanip>
#include <vector>
redBlackTree::redBlackTree() {
    root = nullptr;
}

void redBlackTree::insert(long long phoneNumber, const string& name){
    node* newNode = new node(phoneNumber, name);
    node* parent = nullptr;
    node* current = root;
   
    while (current != nullptr){
        parent = current;
        if (phoneNumber < current->phoneNumber){
            current = current->left;
        } 
        else if (phoneNumber > current->phoneNumber){
            current = current->right;
        } 
        else{ // No Duplicates
            delete newNode;
            return;
        }
    }

    newNode->parent = parent;
    if (parent == nullptr){
        root = newNode;
    } 
    else if (phoneNumber < parent->phoneNumber){
        parent->left = newNode;
    } 
    else{
        parent->right = newNode;
    }

    maintainProperties(newNode); // Make sure it's a valid red black tree
}

void redBlackTree::maintainProperties(node* currentNode){
    // Case 1: The current node is the root
    if (currentNode == root){
        currentNode->isRed = false;
        return;
    }

    // Case 2: The parent node is black (no violation)
    if (!currentNode->parent->isRed){
        return;
    }

    // Needed for future Cases
    node* parent = currentNode->parent;
    node* grandParent = parent->parent;
    node* uncle;
    
    if (parent == grandParent->left){
        uncle = grandParent->right;
    } 
    else{
        uncle = grandParent->left;
    }

    // Case 3: The parent and uncle are both red
    if (uncle != nullptr && uncle->isRed){
        parent->isRed = false;
        uncle->isRed = false;
        grandParent->isRed = true;
        maintainProperties(grandParent);
        return;
    }

    // Case 4: Node is an inside child (LR or RL case) 
    bool case4Done = false;
    if (currentNode == parent->right && parent == grandParent->left){
        if (grandParent->parent != nullptr){
            if (grandParent->parent->left == grandParent){
                grandParent->parent->left = rotateLeftRight(grandParent);
                case4Done = true;
            }
            else {
                grandParent->parent->right = rotateLeftRight(grandParent);
                case4Done = true;
            }
        }
        else{
           this->root = rotateLeftRight(grandParent); 
           case4Done = true;
        }
    }
    else if (currentNode == parent->left && parent == grandParent->right){
        if (grandParent->parent != nullptr){
            if (grandParent->parent->left == grandParent){
                grandParent->parent->left = rotateRightLeft(grandParent);
                case4Done = true;
            }
            else {
                grandParent->parent->right = rotateRightLeft(grandParent);
                case4Done = true;
            }
        }
        else{
           this->root = rotateRightLeft(grandParent); 
           case4Done = true;
        }
    }

    if (case4Done = true){
        return;
    }

    // Case 5: Node is an outside child (LL or RR case)
    parent->isRed = false;
    grandParent->isRed = true;
    if (currentNode == parent->left){
        if (grandParent->parent != nullptr){
            grandParent->parent->left = rotateRight(grandParent);
        }
        else{
           this->root = rotateRight(grandParent); 
        }
    } 
    else{
        if (grandParent->parent != nullptr){
            grandParent->parent->right = rotateLeft(grandParent);
        }
        else{
           this->root = rotateLeft(grandParent); 
        }
        
    }
}

void redBlackTree::searchNumber(long long phoneNumber){
    node* currentNode = root;
    while (currentNode != nullptr && currentNode->phoneNumber != phoneNumber) {
        if (phoneNumber < currentNode->phoneNumber) {
            currentNode = currentNode->left;
        }else if( phoneNumber > currentNode->phoneNumber ){

            currentNode = currentNode->right;

        } else {
            cout << currentNode->name << endl;
            return;
        }
    }
    if (currentNode != nullptr){
        cout << currentNode->name << endl;
    }
    else{
        cout << "number not found" << endl;
    }
}

void redBlackTree::searchName(const string& name){
    bool hasPrinted = false;
    vector<long long int> nums;
    searchNameHelper(name, this->root, hasPrinted, nums);
    for(auto iter = nums.begin(); iter != nums.end(); iter++){
        cout << *iter << endl;
    }
    if (!hasPrinted){
        cout << "Name Not Found" << endl;
    }
}

void redBlackTree::searchNameHelper(const string& name, node* currentNode, bool& exists, vector<long long int>& nums) { // full in order traversal since tree is sorted by phonenumber, not name. Name locations are not relative to each other
    if (currentNode == nullptr) {
        return;
    }
    searchNameHelper(name, currentNode->left, exists, nums);
    if (currentNode->name == name) {
        exists = true;
        bool isIn = false;
        for(auto iter = nums.begin(); iter != nums.end(); iter++){
            if(*iter == currentNode->phoneNumber){
                isIn = true;
                break;
            }
        }
        if(!isIn){
            nums.push_back(currentNode->phoneNumber);
        }
    }
    searchNameHelper(name, currentNode->right, exists, nums);
}


void redBlackTree::inOrderTraversal(node* currentNode){
    if (currentNode != nullptr) {
        inOrderTraversal(currentNode->left);
        cout << currentNode->phoneNumber << " - " << currentNode->name << endl;
        inOrderTraversal(currentNode->right);
    }
}

void redBlackTree::inOrderTraversal(node* currentNode, int wantedAreaCode){ // Prints all nodes in a given area code.
    if (currentNode != nullptr){
        int currentAreaCode = currentNode->phoneNumber/10000000; // Gets first three digits, aka area code.
        if (currentAreaCode == wantedAreaCode) {
            inOrderTraversal(currentNode->left, wantedAreaCode);
            cout << currentNode->phoneNumber << " - " << currentNode->name << endl;
            inOrderTraversal(currentNode->right, wantedAreaCode);
        }
    }
}

void redBlackTree::getFullAreaCode(node* currentNode, int wantedAreaCode, bool& exists){
    int areaCodeDivisor = 10000000; // Magic number turns phone number into area code
    while (currentNode != nullptr){
        int currentAreaCode = currentNode->phoneNumber/areaCodeDivisor; // Gets first three digits, aka area code.
        if (currentNode->phoneNumber/areaCodeDivisor > wantedAreaCode){ 
            currentNode = currentNode->left;
        }
        else if (currentNode->phoneNumber/areaCodeDivisor < wantedAreaCode){ 
            currentNode = currentNode->right;
        }
        else{
            inOrderTraversal(currentNode, wantedAreaCode);
            exists = true;
            break;
        }
    }   
}

void redBlackTree::printAreaCode(int wantedAreaCode){
    bool exists = false;
    getFullAreaCode(this->root, wantedAreaCode, exists);
    if (!exists){
        cout << "There are no numbers with that area code in the registry" << endl;
    }
}

void redBlackTree::printAllNumbers(){
    inOrderTraversal(this->root);
}

redBlackTree::~redBlackTree(){
    destructorHelper(this->root);
}

void redBlackTree::destructorHelper(node* currentNode){
    if (currentNode != nullptr){
        destructorHelper(currentNode->left);
        destructorHelper(currentNode->right);
        delete currentNode;
    }
}

node* redBlackTree::rotateLeft(node* parent){
    node* grandChild = parent->right->left;
    node* newParent = parent->right;
    newParent->left = parent;
    parent->right = grandChild;
    return newParent;
}

node* redBlackTree::rotateRight(node* parent){
    node* grandChild = parent->left->right;
    node* newParent = parent->left;
    newParent->right = parent;
    parent->left = grandChild;
    return newParent;
}

node* redBlackTree::rotateRightLeft(node* parent){
    node* newParent = parent->right->left;
    parent->right = rotateRight(parent->right);
    rotateLeft(parent);
    return newParent;
}

node* redBlackTree::rotateLeftRight(node* parent){
    node* newParent = parent->left->right;
    parent->left = rotateLeft(parent->left);
    rotateRight(parent);
    return newParent;
}