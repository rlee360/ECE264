#ifndef LISTS_H
#define LISTS_H

#include <iostream>
#include <string>

template <typename dataType>
class SimpleList {

                    /* Node class definition */
                    class Node {
                        public:
                            dataType data;
                            Node* next;
                            
                            Node(dataType d, Node* n) {
                                data = d;
                                next = n;
                            }
                    };
                    /* end definition */
    
    Node* head;
    Node* tail;
    int numElements;
    std::string name;
    
    public:
        //Basic constructor, accepts name of SimpleList
        SimpleList(std::string n);

        //Virtual Destructor - traverses list and deletes nodes
        virtual ~SimpleList() {
            Node* current = head;
            while(current != nullptr) {
                Node* garbage = current;
                current = current->next; 
                delete garbage;
            }
        }
        
        std::string getListName() { return name; }
        
        //push and pop functions
        virtual void push(dataType t) = 0;
        virtual dataType pop() = 0;
        
        //returns true if list is empty, false if not empty
        bool listEmpty();
        
        //prints the entire list
        void print(); 
        
    protected:
        void insertAtHead(dataType data);
        
        void insertAtTail(dataType data);
        
        dataType removeFromHead();
        
};

template <typename dataType>
SimpleList<dataType>::SimpleList(std::string n) {
    numElements = 0;
    head = nullptr;
    tail = nullptr;
    name = n;

}

template <typename dataType>
void SimpleList<dataType>::insertAtHead(dataType data) {
    Node* newNode = new Node(data, head);
    if(listEmpty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        head = newNode;
    }
    numElements++;
}

template <typename dataType>
void SimpleList<dataType>::insertAtTail(dataType data) {
    Node* newNode = new Node(data, nullptr);
    if(listEmpty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    
    numElements++;
}

template <typename dataType>
dataType SimpleList<dataType>::removeFromHead() {
    if(!listEmpty()) {
        Node* tmp = head;
        dataType d = head->data;
        head = head->next;
        delete tmp;
        numElements--;
        return d;
    }
}

template <typename dataType>
bool SimpleList<dataType>::listEmpty() {
    if(numElements == 0) {
        return true;
    }
    return false;
}

template <typename dataType>
void SimpleList<dataType>::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << "\n";
        current = current->next;
    }
}

#endif
