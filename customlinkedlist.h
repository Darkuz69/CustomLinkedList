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

class LinkedListMemoryAllocationExcpetion : public std::exception {
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
// End (Exceptions)


template <typename Type>
struct Node {
    Type data;
    struct Node *next_node;  
};

template <typename Type>
class LinkedList {
public:
    typedef struct node {
        Type data;
        struct node *next_node;
    } Node;

protected:
    Node *head_node;
    Node *tail_node;
    size_t size;
    size_t maximum_size = SIZE_MAX / sizeof(Node);

public:
    LinkedList() {
        this->head_node = nullptr;
        this->tail_node = nullptr;
        this->size = 0;
    }

    bool isEmpty() const {
        return (this->size == 0);
    }

    size_t indexOf(Type data) {
        if(this->head_node == nullptr) {
            throw LinkedListisEmptyException();
        }

        size_t counter = -1;
        for(Node *temp_node = this->head_node; temp_node != nullptr; temp_node = temp_node->next_node) {
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

        Node *new_node = new(std::nothrow) Node;
        if(new_node == NULL) {
            throw LinkedListMemoryAllocationExcpetion();
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

        Node *new_node = new(std::nothrow) Node;
        if(new_node == NULL) {
            throw LinkedListMemoryAllocationExcpetion();
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

    void insert(size_t nth, Type data) {
        if(this->size > this->maximum_size) {
            throw LinkedListMaximumLimitException();
        }

        if(nth < 0 || nth > this->size - 1) {
            throw LinkedListIndexOutofRangeException();
        }

        if(nth == 0) {
            this->offer(data);
            return;
        } else if(nth == this->size) {
            this->push(data);
            return;
        }

        Node *previous_node = this->head_node;
        for(size_t i = 1; i < nth; i++) {
            previous_node = previous_node->next_node;
        }
        Node *temp_node = previous_node->next_node;

        Node *new_node = new(std::nothrow) Node;
        if(new_node == NULL) {
            throw LinkedListMemoryAllocationExcpetion();
        }

        new_node->data = data;
        new_node->next_node = temp_node;
        previous_node->next_node = new_node;
        this->size++;
    }

    Type pop() {
        if(this->head_node == nullptr) {
            throw LinkedListisEmptyException();
        }

        Node *temp_node = this->head_node;
        while(temp_node->next_node != this->tail_node) {
            temp_node = temp_node->next_node;
        }

        Type return_data = this->tail_node->data;
        delete this->tail_node;        
        this->tail_node = temp_node;
        this->tail_node->next_node = nullptr;
        this->size--;

        return return_data;
    }

    Type poll() {
        if(this->head_node == nullptr) {
            throw LinkedListisEmptyException();
        }
        
        Node *temp_node = this->head_node->next_node;
        Type return_data = this->head_node->data;
        delete this->head_node;
        this->head_node = temp_node;
        this->size--;

        return return_data;
    }

    Type remove(Type data) {
        if(this->head_node == nullptr) {
            throw LinkedListisEmptyException();
        }

        int index = this->indexOf(data);
        if(index == -1) {
            return NULL;
        } else if (index == 0) {
            return this->poll();
        } else if(index == (int)(this->size - 1)) {
            return this->pop();
        }

        Node *temp_node = this->head_node;
        int counter = 0;
        while(temp_node != nullptr && counter < index - 1) {
            temp_node = temp_node->next_node;
            counter++;
        }

        Node *delete_node = temp_node->next_node;
        Type return_data = delete_node->data;
        temp_node->next_node = delete_node->next_node;
        delete delete_node;

        return return_data;
    }

private:
    void __print_list__(Node *temp_node) {
        if(this->size == 0) {
            std::cout << "[]\n";
            return;
        }

        if(this->head_node == nullptr) {
            return;
        }

        if(temp_node == nullptr) {
            std::cout << "]\n";
            return;
        }

        if(temp_node == this->head_node) {
            std::cout << "[";
        }
        std::cout << temp_node->data;
        if(temp_node->next_node != nullptr) {
            std::cout << ", ";
        }
        
        __print_list__(temp_node->next_node);
    }

    void __print_list_reversed__(Node *temp_node) {
        if(this->size == 0) {
            std::cout << "[]\n";
            return;
        }

        if(this->head_node == nullptr) {
            return;
        }

        if(temp_node == nullptr) {
            std::cout << "[";
            return;
        }

        __print_list_reversed__(temp_node->next_node);
        std::cout << temp_node->data;
        if(temp_node != this->head_node) {
            std::cout << ", ";
        } else {
            std::cout << "]\n";
        }
    }

public:
    void printList() {
        this->__print_list__(this->head_node);
    }

    void printListReversed() {
        this->__print_list_reversed__(this->head_node);
    }

    size_t getSize() const { return this->size; }

    Type peekFirst() const { return this->head_node->data; }

    Type peekLast() const { return this->tail_node->data; }

    Type peekAtIndex(size_t index) const {
        if(index < 0 || index > this->size - 1) {
            throw LinkedListIndexOutofRangeException();
        }

        if(index == 0) {
            return peekFirst();
        } else if (index == this->size - 1) {
            return peekLast();
        }

        Node *temp_node = this->head_node;
        size_t counter = 0;
        while(temp_node != nullptr && counter < index) {
            temp_node = temp_node->next_node;
            counter++;
        }

        return temp_node->data;
    }
private:
    void delete_list(Node *temp_node) {
        if(temp_node == nullptr) {
            return;
        }

        Node *next = temp_node->next_node;
        delete temp_node;
        delete_list(next);

        this->head_node = nullptr;
        this->tail_node = nullptr;
        this->size = 0;
    }

public:
    ~LinkedList() {
        this->delete_list(this->head_node);
    }
};

#endif //CUSTOMLINKEDLIST_H
