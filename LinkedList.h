/*
    Custom Linked List Library by Darkuz69

    These library was made as my preparation for the
    DSA Subject (2nd Year College). I'm very interested
    in this subject, that's why I've spent weeks after weeks
    of practicing pointers. This is the result of those weeks.

    For the future me, or anyone that finds this library,
    enjoy!! Or approach me if something's wrong...
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

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

    void push_back(Type data) {
        if(this->length > this->maximum_size) {
            throw std::runtime_error("LinkedListError: Maximum nodes has been reached\n");
        }

        Node *new_node = new(std::nothrow) Node;
        if(new_node == NULL) {
            throw std::runtime_error("LinkedListError: Memory allocation has failed\n");
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
            throw std::runtime_error("LinkedListError: Maximum nodes has been reached\n");
        }

        Node *new_node = new(std::nothrow) Node;
        if(new_node == NULL) {
            throw std::runtime_error("LinkedListError: Memory allocation has failed\n");
        }

        if(this->head_node == nullptr) {
            this->push_back(data);
            return;
        }

        new_node->data = data;
        new_node->next_node = this->head_node;
        this->head_node = new_node;
    }

    Type remove_back() {
        if(this->head_node == nullptr) {
            throw std::runtime_error("LinkedListError: Linked list is empty\n");
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
            throw std::runtime_error("LinkedListError: Linked list is empty\n");
        }
        
        Node *temp_node = this->head_node->next_node;
        Type return_data = this->head_node->data;
        delete this->head_node;
        this->head_node = temp_node;
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

    const Node* get_head() { return this->head_node; }

    size_t get_length() { return this->length; }

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

#endif //LINKEDLIST_H