#ifndef STACKANDQUEUE_H
#define STACKANDQUEUE_H

template <typename dataType>
class Stack : public SimpleList<dataType> {
    //properties like name have already been inherited
    public:
        Stack(std::string stackName) : SimpleList<dataType>(stackName) {}
        
        void push(dataType t) {
            SimpleList<dataType>::insertAtHead(t);
        }
        
        dataType pop() {
            return SimpleList<dataType>::removeFromHead();
        }
};

template <typename dataType>
class Queue : public SimpleList<dataType> {
    //properties like name have already been inherited
    public:
        Queue(std::string queueName) : SimpleList<dataType>(queueName) { }
        
        void push(dataType t) override {
            SimpleList<dataType>::insertAtTail(t);
        }
        
        dataType pop() override {
            return SimpleList<dataType>::removeFromHead();
        }
};

#endif
