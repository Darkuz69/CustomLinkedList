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
    size_t length;
    size_t maximum_size = SIZE_MAX / sizeof(Node);

public:
    LinkedList() {
        this->head_node = nullptr;
        this->tail_node = nullptr;
        this->length = 0;
    }

    bool is_empty() const {
        return (this->length == 0);
    }

    void push_back(Type data) {
        if(this->length > this->maximum_size) {
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
            this->length++;
            return;
        }

        this->tail_node->next_node = new_node;
        this->tail_node = new_node;
        this->length++;
    }

    void push_front(Type data) {
        if(this->length > this->maximum_size) {
            throw LinkedListMaximumLimitException();
        }

        Node *new_node = new(std::nothrow) Node;
        if(new_node == NULL) {
            throw LinkedListMemoryAllocationExcpetion();
        }

        if(this->head_node == nullptr) {
            this->push_back(data);
            return;
        }

        new_node->data = data;
        new_node->next_node = this->head_node;
        this->head_node = new_node;
        this->length++;
    }

    void push_at_nth(size_t nth, Type data) {
        if(this->length > this->maximum_size) {
            throw LinkedListMaximumLimitException();
        }

        if(nth <= 0 || nth > this->length) {
            throw LinkedListIndexOutofRangeException();
        }

        if(nth == 1) {
            this->push_front(data);
            return;
        } else if(nth == this->length) {
            this->push_back(data);
            return;
        }

        Node *previous_node = this->head_node;
        for(size_t i = 1; i < nth - 1; i++) {
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
        this->length++;
    }

    Type remove_back() {
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
        this->length--;

        return return_data;
    }

    Type remove_front() {
        if(this->head_node == nullptr) {
            throw LinkedListisEmptyException();
        }
        
        Node *temp_node = this->head_node->next_node;
        Type return_data = this->head_node->data;
        delete this->head_node;
        this->head_node = temp_node;
        this->length--;

        return return_data;
    }

    Type remove_nth(size_t index) {
        if(index <= 0 || index > this->length) {
            throw LinkedListIndexOutofRangeException();
        }

        if(index == 1) {
            return this->remove_front();
        } else if (index == this->length) {
            return this->remove_back();
        }

        Node *previous_node = this->head_node;
        for(size_t i = 1; i < index - 1; i++) {
            previous_node = previous_node->next_node;
        }
        Node *temp_node = previous_node->next_node;
        Type return_data = temp_node->data;

        previous_node->next_node = temp_node->next_node;
        delete temp_node;
        this->length--;

        return return_data;
    }

private:
    void __print_list__(Node *temp_node) {
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
    void print_list() {
        this->__print_list__(this->head_node);
    }

    void print_list_reversed() {
        this->__print_list_reversed__(this->head_node);
    }

    size_t get_length() const { return this->length; }

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
        this->length = 0;
    }

public:
    ~LinkedList() {
        this->delete_list(this->head_node);
    }
};

#endif //CUSTOMLINKEDLIST_H
