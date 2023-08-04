#include <iostream>
#include <fstream>
#include <string>

//function to check if given user input is a number or not, returns a long long int since phone numbers are large
long long int returnNum(std::string num){
    bool isNum = true;
    long long int number;
    for(int i = 0; i < num.length(); i++){

        if(num[i] < 48 || num[i] > 57){

            isNum = false;
            break;

        }

    }
    if(isNum){
        number = std::stoll(num);
        return number;
    }else{
        return 0;
    }

}

int main() {

    std::ifstream data;
    data.open("../maindata.csv");
    std::string line;
    std::getline(data, line);
    //clear header data

    std::cout << "Welcome to Don't Call Me!" << std::endl << std::endl;
    std::cout << "Reading data..." << std::endl << std::endl;


    while(std::getline(data, line)) {
        //need to parse out just an integer for phone number
        //since formatting is constant just += each space onto string
        std::string num = "";
        std::string name = "";
        std::string code = "";
        for(int i = 0; i < line.length(); i++){
            if(line[i] >= 48 && line[i] <= 57){
                num += line[i];
                if(code.length() < 3){
                    code += line[i];
                }
            }else if(line[i] == ','){
                name = line.substr(i+1, line.length()-1);
                break;
            }
        }
        long long int pNum;
        int aCode;
        pNum = std::stoll(num);
        aCode = std::stoi(code);

        //below is commented out since it was used in testing only
        std::cout << aCode << " " << pNum << " " << name << std::endl;

        //here would be inserting each into the created map functions


    }
    data.close();
    std::cout << "Success!" << std::endl << std::endl;

    //create a menu for the user to interface with to choose options
    int user = -1;
    while(user != 0){

        //menu
        std::cout << "Please make a selection" << std::endl;
        std::cout << "0. Exit program" << std::endl;
        std::cout << "1. Search for number" << std::endl;
        std::cout << "2. Search for name" << std::endl;
        std::cout << "3. Print all numbers in given Area Code" << std::endl;
        //std::cout << "4. Print full list" << std::endl;
        std::cout << "4. Add number and name" << std::endl;
        std::cin >> user;
        std::cout << std::endl;


        if(user == 0){

        break;

        }else if(user == 1){

            std::string number;
            std::cout << "Please enter a number (10 digits no delimiters): ";
            std::cin >> number;
            std::cout << std::endl;
            long long int num = returnNum(number);

            if(number.length() != 10 || num == 0){

                std::cout<< "Invalid number!" << std::endl;

            }else{

                //use find function to get number and name
                std::cout << "Searching for " << num << std::endl;

            }

        }else if(user == 2){

            std::string fName, lName;
            std::cout << "Please enter a name in the format First Last: ";
            std::cin >> fName;
            std::cin >> lName;
            std::string name = fName + " " + lName;
            std::cout << std::endl;

            //make call to search for name
            std::cout << "Searching for numbers associated with " << name << std::endl;

        }else if(user == 3){

            std::string code;
            std::cout << "Please enter 3 digit area code you wish to print: ";
            std::cin >> code;
            std::cout << std::endl;

            if(code.length() != 3 || returnNum(code) == 0){

                std::cout << "Invalid Area Code!" << std::endl;

            }else{

                int aCode = std::stoi(code);

                std::cout << "Searching for all numbers in " << aCode << std::endl;
                //make call to search area code

            }

        }else if(user == 4){

            std::string num;
            std::string name;
            std::cout << "Please enter a 10 digit number with no delimiters: ";
            std::cin >> num;
            std::cout << std::endl;

            std::string fName, lName;
            std::cout << "Please enter a name in the format First Last: ";
            std::cin >> fName;
            std::cin >> lName;
            name = fName + " " + lName;
            std::cout << std::endl;
            long long int pNum = returnNum(num);

            if(num.length() != 10 || pNum == 0){

                std::cout << "Invalid Number!" << std::endl;

            }else{

                //make call to insert name a number
                //Test to make sure inputs work
                std::cout << "Inserting " << name << " " << pNum << " into DNC list" << std::endl;

            }

        }else{

            std::cout << "Invalid selection please enter another number" << std::endl;

        }

        std::cout << std::endl;




    }


    return 0;
}
