#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int area_Code; //value with the key
    vector<long long int> phone_Numbers;
    Node* next; //used to handle collisions in data;

    //constructor
    Node(int areaCode, long long int phoneNum, Node* n) : area_Code(areaCode), phone_Numbers({phoneNum}), next(n){}

};

class HashMap{
    // Size of hash map
    int size;
    // Number of phone # in the map;
    int amount;
    // Array of pointers to Nodes, if there is ever a collision;
    Node** map;

    public:

    //Constructor
    HashMap(int s): size(s), amount(0){
        map = new Node*[size];
        for (int i = 0; i < size; i++){
            map[i] = nullptr;
        }
    }

    //Destructor
    ~HashMap(){
        for (int i = 0; i < size; ++i) {
            Node* current = map[i];
            while (current != nullptr) {
                Node* deletion = current;
                current = current->next;
                delete deletion;
            }
            map[i] = nullptr;
        }
        delete[] map;
    }

    //resizing the map if it ever gets full
    void resize() {
        if ((float)amount / size > 0.8) {
            // Save old map
            Node** oldMap = map;
            int oldSize = size;

            // Create new, larger table
            size *= 2;
            amount = 0;
            map = new Node*[size];
            for (int i = 0; i < size; i++) {
                map[i] = nullptr;
            }

            // Rehash all keys
            for (int i = 0; i < oldSize; i++) {
                Node* node = oldMap[i];
                while (node != nullptr) {
                    for(long long int phoneNumber : node->phone_Numbers) {
                    insert(node->area_Code, phoneNumber);
                    }
                    Node* toDelete = node;
                    node = node->next;
                    delete toDelete;
                }
            }

            // Delete old Map
            delete[] oldMap;
        }
    }


    //Hash function to hash the keys
    int hash(long long phone_Number){
        return phone_Number % size;
    }


    // Inserting values into the map
    void insert(int areaCode, long long phoneNum){
        int hashVal = hash(areaCode);
        Node* prev = nullptr;
        Node* current = map[hashVal];
        while (current != nullptr && current->area_Code != areaCode) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            current = new Node(areaCode, phoneNum, nullptr);
            if (prev == nullptr) {
                // Inserting into empty bucket
                map[hashVal] = current;
            } else {
                // Appending to existing chain
                prev->next = current;
            }
           amount++;
        } else {
            // Adding phone number to existing area code
            current->phone_Numbers.push_back(phoneNum);
        }
    }


    //Get function. Retrieve phone numbers from one area code
    vector<long long int> get(int areaCode){
        int hashVal = hash(areaCode);
        Node* current = map[hashVal];
        while (current != nullptr) {
            if (current->area_Code == areaCode) {
                return current->phone_Numbers;
            }
            current = current->next;
        }
        return {}; // Return empty vector if not found
    }


    // Print function
    void printNumOfAreaCode(int areaCode) {
        vector<long long> phoneNumbers = get(areaCode);
        cout << "Phone numbers of " << areaCode << ":\n";
        for (long long phoneNumber : phoneNumbers) {
            std::cout << phoneNumber << "\n";
        }
    }
};

//extract first three digits of the phone number
/*long long extractAreaCode(long long int number) {
    while (number >= 1000) {
        number /= 10;
    }
    return number;
}
*/
/*int main() {
    HashMap hm(2);  // Start with a small table to test resizing

    int areaCode1 = extractAreaCode(2125678901);
    int areaCode2 = extractAreaCode(1234567890);
    int areaCode3 = extractAreaCode(4567890123);

    
    // Test inserting  values
    //insert(area code, phone number)
    hm.insert(areaCode1, 2125678901);
    hm.insert(areaCode1, 2123458349);
    hm.insert(areaCode1, 2123452143);
    hm.insert(areaCode1, 2123456789);

    hm.insert(areaCode2, 1234567890);
    hm.insert(areaCode2, 1234567690);
    hm.insert(areaCode2, 1234581890);
    hm.insert(areaCode2, 1234564560);

    hm.insert(areaCode3, 4567890123);
    hm.insert(areaCode3, 4567420123);
    hm.insert(areaCode3, 4567899123);
    hm.insert(areaCode3, 4567898923);
    hm.insert(areaCode3, 4567897893);

    hm.printNumOfAreaCode(areaCode1);
    hm.printNumOfAreaCode(areaCode2);
    hm.printNumOfAreaCode(areaCode3);

    return 0;
}
 */