/*
    Custom Linked List Library by Darkuz69

    These library was made as my preparation for the
    DSA Subject (2nd Year College). I'm very interested
    in this subject, that's why I've spent weeks after weeks
    of practicing pointers. This is the result of those weeks.

    For the future me, or anyone that finds this library,
    enjoy!! Or approach me if something's wrong...
*/

#ifndef CUSTOMLINKEDLIST_H
#define CUSTOMLINKEDLIST_H

#include <iostream>
#include <vector>
#include <exception>

// Exceptions
class LinkedListisEmptyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Linked List is empty!!";
    }
};

class LinkedListIndexOutofRangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Index out of range!!";
    }
};

class LinkedListMemoryAllocationException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Memory Allocation has failed!!";
    }
};

class LinkedListMaximumLimitException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Maximum limit reached!!";
    }
};

class LinkedListNodeNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Node with such data was not found!!";
    }
};
// End (Exceptions)


template <typename Type>
struct Node {
    Type data;
    Node *next_node;
};

template <typename Type>
class LinkedList { 
    Node<Type> *head_node;
    Node<Type> *tail_node;
    size_t size;
    static const size_t maximum_size = SIZE_MAX / sizeof(Node<Type>);

public:
    LinkedList() {
        this->head_node = nullptr;
        this->tail_node = nullptr;
        this->size = 0;
    }

    bool isEmpty() const {
        return (this->head_node == nullptr);
    }

    int indexOf(Type data) {
        if(this->isEmpty()) {
            throw LinkedListisEmptyException();
        }

        int counter = -1;
        for(Node<Type> *temp_node = this->head_node; temp_node != nullptr; temp_node = temp_node->next_node) {
            counter++;
            if(temp_node->data == data) {
                return counter;
            }
        }

        return -1;
    }

    void push(Type data) {
        if(this->size > this->maximum_size) {
            throw LinkedListMaximumLimitException();
        }

        Node<Type> *new_node = new(std::nothrow) Node<Type>;
        if(new_node == NULL) {
            throw LinkedListMemoryAllocationException();
        }

        new_node->data = data;
        new_node->next_node = nullptr;

        if(this->head_node == nullptr) {
            this->head_node = new_node;
            this->tail_node = new_node;
            this->size++;
            return;
        }

        this->tail_node->next_node = new_node;
        this->tail_node = new_node;
        this->size++;
    }

    void offer(Type data) {
        if(this->size > this->maximum_size) {
            throw LinkedListMaximumLimitException();
        }

        Node<Type> *new_node = new(std::nothrow) Node<Type>;
        if(new_node == NULL) {
            throw LinkedListMemoryAllocationException();
        }

        if(this->head_node == nullptr) {
            this->push(data);
            return;
        }

        new_node->data = data;
        new_node->next_node = this->head_node;
        this->head_node = new_node;
        this->size++;
    }

    void insert(size_t index, Type data) {
        if(this->size > this->maximum_size) {
            throw LinkedListMaximumLimitException();
        }

        if(index > this->size) {
            throw LinkedListIndexOutofRangeException();
        }

        if(index == 0) {
            this->offer(data);
            return;
        } else if(index == this->size) {
            this->push(data);
            return;
        }

        Node<Type> *previous_node = this->head_node;
        for(size_t i = 1; i < index; i++) {
            previous_node = previous_node->next_node;
        }
        Node<Type> *temp_node = previous_node->next_node;

        Node<Type> *new_node = new(std::nothrow) Node<Type>;
        if(new_node == NULL) {
            throw LinkedListMemoryAllocationException();
        }

        new_node->data = data;
        new_node->next_node = temp_node;
        previous_node->next_node = new_node;
        this->size++;
    }

    Type pop() {
        if(this->isEmpty()) {
            throw LinkedListisEmptyException();
        }

        Type return_data;

        if(this->head_node == this->tail_node) {
            return_data = this->head_node->data;
            delete this->head_node;
            this->head_node = nullptr;
            this->tail_node = nullptr;
        } else {
            Node<Type> *temp_node = this->head_node;
            while(temp_node->next_node != this->tail_node) {
                temp_node = temp_node->next_node;
            }

            return_data = this->tail_node->data;
            delete this->tail_node;
            this->tail_node = temp_node;
            this->tail_node->next_node = nullptr;
        }

        this->size--;
        return return_data;
    }

    Type poll() {
        if(this->isEmpty()) {
            throw LinkedListisEmptyException();
        }
        
        Node<Type> *temp_node = this->head_node->next_node;
        Type return_data = this->head_node->data;
        delete this->head_node;
        this->head_node = temp_node;
        this->size--;

        return return_data;
    }

    Type remove(Type data) {
        if(this->isEmpty()) {
            throw LinkedListisEmptyException();
        }

        int index = this->indexOf(data);
        if(index == -1) {
            throw LinkedListNodeNotFoundException();
        } else if (index == 0) {
            return this->poll();
        } else if(index == (int)(this->size - 1)) {
            return this->pop();
        }

        Node<Type> *temp_node = this->head_node;
        int counter = 0;
        while(temp_node != nullptr && counter < index - 1) {
            temp_node = temp_node->next_node;
            counter++;
        }

        Node<Type> *delete_node = temp_node->next_node;
        Type return_data = delete_node->data;
        temp_node->next_node = delete_node->next_node;
        delete delete_node;

        return return_data;
    }

    std::string toString() {
        if(this->isEmpty()) {
            return "[]";
        }

        std::string toStr = "[";
        for(Node<Type> *temp_node = this->head_node; temp_node != nullptr; temp_node = temp_node->next_node) {
            if(typeid(temp_node->data) == typeid(std::string)) {
                toStr += "\"" + temp_node->data + "\"";
            } else {
                toStr += temp_node->data;
            }
            if(temp_node->next_node != nullptr) {
                toStr += ", ";
            }
        }
        toStr += "]\n";

        return toStr;
    }

    std::string toStringReversed() {
        Type temp_list[this->size];
        int i = 0;
        for(Node<Type> *temp_node = this->head_node; temp_node != nullptr; temp_node = temp_node->next_node) {
            temp_list[i++] = temp_node->data;
        }

        std::string revStr = "[";
        for(int i = this->size - 1; i >= 0; i--) {
            if(typeid(temp_list[i]) == typeid(std::string)) {
                revStr += "\"" + temp_list[i] + "\"";
            } else {
                revStr += temp_list[i];
            }
            if(i > 0) {
                revStr += ", ";
            }
        }
        revStr += "]\n";

        return revStr;
    }

    size_t getSize() const { return this->size; }

    Type peekFirst() const {
        if(this->isEmpty()) {
            throw LinkedListisEmptyException();
        }
        return this->head_node->data; 
    }

    Type peekLast() const { 
        if(this->isEmpty()) {
            throw LinkedListisEmptyException();
        }
        return this->tail_node->data; 
    }

    Type peekAtIndex(size_t index) const {
        if(index > this->size - 1) {
            throw LinkedListIndexOutofRangeException();
        }

        if(index == 0) {
            return peekFirst();
        } else if (index == this->size - 1) {
            return peekLast();
        }

        Node<Type> *temp_node = this->head_node;
        size_t counter = 0;
        while(temp_node != nullptr && counter < index) {
            temp_node = temp_node->next_node;
            counter++;
        }

        return temp_node->data;
    }
private:
    void delete_list(Node<Type> *temp_node) {
        if(temp_node == nullptr) {
            return;
        }

        this->delete_list(temp_node->next_node);
        delete temp_node;
    }

public:
    ~LinkedList() {
        this->delete_list(this->head_node);
    }
};

#endif //CUSTOMLINKEDLIST_H
