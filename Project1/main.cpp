/*
 Name: Richard Lee
 Date: 04/09/2018
 
 Project Description: 
  This program uses singly linked lists to implement stacks and queues.
  The program accepts commands through and input file, and writes the output to a file.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "SimpleList.hpp" //definition/declaration of SimpleList
#include "StackAndQueue.hpp"

/* Globals */

//file streams
std::ifstream inFile;
std::ofstream outFile;

//lists
std::list<SimpleList<int> *> listSLi; // all integer stacks and queues
std::list<SimpleList<double> *> listSLd; // all double stacks and queues
std::list<SimpleList<std::string> *> listSLs; // all string stacks and queues

/* Function Prototypes */
void getWords();
void commandCreate(std::string command[]);
void commandPush(std::string t[]);
void commandPop(std::string t[]);

void cleanUp() {
    for (std::list<SimpleList<int>* >::iterator it=listSLi.begin(); it != listSLi.end(); ++it) {
        //std::cout << (*it)->getListName() << std::endl;
        delete *it;
    }
    for (std::list<SimpleList<double>* >::iterator it=listSLd.begin(); it != listSLd.end(); ++it) {
        //std::cout << (*it)->getListName() << std::endl;
        delete *it;
    }
    for (std::list<SimpleList<std::string>* >::iterator it=listSLs.begin(); it != listSLs.end(); ++it) {
        //std::cout << (*it)->getListName() << std::endl;
        delete *it;
    }

}

int main(int argc, char* argv[]) {

    //open the file
    std::string ifName;
    std::cout << "Enter name of input file: ";
    std::cin >> ifName;
    inFile.open(ifName.c_str());

    std::string ofName;
    std::cout << "Enter name of output file: ";
    std::cin >> ofName;
    outFile.open(ofName.c_str());
    
    getWords(); //parse the input commands
    
    cleanUp(); //iterate through each of the lists and delete the pointer. Invokes the destructors for SimpleList
    
    return 0;
}

template <typename dataType>
SimpleList<dataType>* searchList(std::list<SimpleList<dataType> *> &searchList, std::string name){
    for(typename std::list<SimpleList<dataType> *>::iterator it = searchList.begin(); it != searchList.end(); ++it){
        if((*it)->getListName() == name){
            return *it;
        }
    }
    return nullptr;
}


void commandCreate(std::string command[]) {
    //identify whether we are dealing with ints, doubles or strings
    if(command[1][0] == 'i') {
        if(searchList(listSLi, command[1]) != nullptr) { //if we can find the listname
            outFile << "ERROR: This name already exists!" << std::endl; //flush the output --------------
            return;
        }
        
        //check if stack or queue using the third word
        if(command[2] == "stack") {
            listSLi.push_front( new Stack<int>(command[1]) );
        }
        else if(command[2] == "queue") {
            listSLi.push_front( new Queue<int>(command[1]) );
        }
    }
    
    else if(command[1][0] == 'd') {
        if(searchList(listSLd, command[1]) != nullptr) { //if we can find the listname
            outFile << "ERROR: This name already exists!" << std::endl; //flush the output --------------
            return;
        }
        
        //check if stack or queue using the third word
        if(command[2] == "stack") {
            listSLd.push_front( new Stack<double>(command[1]) );
        }
        else if(command[2] == "queue") {
            listSLd.push_front( new Queue<double>(command[1]) );
        }
    }
    
    else if(command[1][0] == 's') {
        if(searchList(listSLs, command[1]) != nullptr) { //if we can find the listname
            outFile << "ERROR: This name already exists!" << std::endl; //flush the output --------------
            return;
        }
        
        //check if stack or queue using the third word
        if(command[2] == "stack") {
            listSLs.push_front( new Stack<std::string>(command[1]) );
        }
        else if(command[2] == "queue") {
            listSLs.push_front( new Queue<std::string>(command[1]) );
        }
    }
}

void commandPush(std::string command[]) {
    //identify whether we are dealing with ints, doubles or strings
    if(command[1][0] == 'i') {
        auto * listptr = searchList(listSLi, command[1]); //create a ptr to the list of interest
        if(listptr == nullptr) { //if we cannot find the listname
            outFile << "ERROR: This name does not exist!" << std::endl; //flush the output --------------
            return;
        }
        listptr->push( stoi(command[2]) );
    }
    
    else if(command[1][0] == 'd') {
        auto * listptr = searchList(listSLd, command[1]);
        if(listptr == nullptr) { //if we can find the listname
            outFile << "ERROR: This name does not exist!" << std::endl; //flush the output --------------
            return;
        }
        listptr->push( stof(command[2]) );
    }

    else if(command[1][0] == 's') {
        auto * listptr = searchList(listSLs, command[1]);
        if(listptr == nullptr) { //if we can find the listname
            outFile << "ERROR: This name does not exist!" << std::endl; //flush the output --------------
            return;
        }
        listptr->push( command[2] );
    }
}



void commandPop(std::string command[]) {
    //identify whether we are dealing with ints, doubles or strings
    if(command[1][0] == 'i') {
        auto * listptr = searchList(listSLi, command[1]); //create a ptr to the list of interest
        if(listptr == nullptr) { //if we can find the listname
            outFile << "ERROR: This name does not exist!" << std::endl; //flush the output --------------
            return;
        }
        else if (listptr->listEmpty()) {
            outFile << "ERROR: This list is empty!\n";
            return;
        }
        outFile << "Value popped: " << listptr->pop() << std::endl;
    }
    
    else if(command[1][0] == 'd') {
        auto * listptr = searchList(listSLd, command[1]);
        if(listptr == nullptr) { //if we can find the listname
            outFile << "ERROR: This name does not exist!" << std::endl; //flush the output --------------
            return;
        }
        else if (listptr->listEmpty()) {
            outFile << "ERROR: This list is empty!\n";
            return;
        }
        outFile << "Value popped: " << listptr->pop() << std::endl;
    }

    else if(command[1][0] == 's') {
        auto * listptr = searchList(listSLs, command[1]);
        if(listptr == nullptr) { //if we can find the listname
            outFile << "ERROR: This name does not exist!" << std::endl; //flush the output --------------
            return;
        }
        else if (listptr->listEmpty() == true) {
            outFile << "ERROR: This list is empty!\n";
            return;
        }
        outFile << "Value popped: " << listptr->pop() << std::endl;
    }
}

void getWords() {
    
    std::string command;
    std::string entries[3]; //create an array of strings to store the commands
    std::string delimiter = " "; //split on spaces
    std::string token;

    if(inFile.is_open()) { //some error checking
        while(getline(inFile, command)) { //takes input from left into the right
            size_t pos = 0;
            int counter = 0; //this counts how many words there are
            
            outFile << "PROCESSING COMMAND: " << command << "\n"; /////////////////////////////----------
            
            //begin to split the string up:
            //npos is highest amount possible for a string
            while ((pos = command.find(delimiter)) != std::string::npos) { 
                entries[counter++] = command.substr(0, pos);
                command.erase(0, pos + delimiter.length()); //delete the part that we have already extracted
            }
            //when we exit the while loop, we still have the last word in the original input string, so we set it here:
            entries[counter++] = command;
                
            //now that we have the command, we have to find its type //split it up into its respective category
            if(entries[0] == "create") {
                commandCreate(entries);
            }
            else if (entries[0] == "push") {
                commandPush(entries);
            }
            else if (entries[0] == "pop") {
                commandPop(entries);
            }

            //clean up the entries array for safety
            for(int i = 0; i < 3 ; i++) {
                entries[i] = "";
            }
        }
    }
}
