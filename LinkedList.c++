/*
    Darkuz_69 here...

    Details and developments about these are on the log file (log.txt)
*/

#include <iostream>

template <typename T>
class LinkedList {
private:
    // Structure for the nodes
    typedef struct node {
        T data;
        struct node *next;
    } Node;

    Node *head; // Head - Start of the List
    Node *tail; // Tail - End of the List
    
    size_t list_size;

public:
    LinkedList<T>() { // Constructor
        this->head = nullptr; // Initalize head to nullptr
        this->tail = nullptr; // Initialize tail to nullptr
        this->list_size = 0;
    }

    void add_node(T data) {
        Node *new_node = new Node; // Create a new node for the given data then initialize the variables
        new_node->data = data;
        new_node->next = nullptr;
        
        if(head == nullptr) {
            // If the new node is the first node to be made, it will be the head and the tail for the meantime
            this->head = new_node;
            this->tail = new_node;
            return;
        }
        
        // If not, we update the tail to point to the new node
        this->tail->next = new_node;
        this->tail = new_node;
        this->list_size++;
    }

    void print_nodes(Node *ptr) {
        // Print the nodes in order, using recursion
        if(ptr == nullptr) {
            return;
        }

        std::cout << ptr->data << " ";
        print_nodes(ptr->next);
    }

    void print_nodesReversed(Node *ptr) {
        // Print the nodes in reversed order, using recursion
        if(ptr == nullptr) {
            return;
        }

        print_nodesReversed(ptr->next);
        std::cout << ptr->data << " ";
    }

    void remove_node(T data) {
        // Remove a node of the given data
        if(this->head == NULL) {
            // This means that the list is still empty
            throw std::runtime_error("Error: LinkedList is empty!!\n");
        }

        if(this->head->data == data) {
            // If the given data has the same data as the head node, we make the head the next node
            Node *temp = this->head->next;
            delete head;
            this->head = temp;
            this->list_size--;
            return;
        }

        if(this->tail->data == data) {
            // If the given data has the same data as the tail node, we make the tail node the node before the tail
            Node *before_tail = this->head;
            while(before_tail->next != this->tail) {
                before_tail = before_tail->next;
            }

            delete this->tail;
            this->tail = before_tail;
            this->tail->next = nullptr;
            this->list_size--;
            return;
        }

        // We scan the list, find the match, then connect the previous node to the next node of the node searched
        Node *prev = nullptr;
        Node *temp = this->head;
        while(temp != nullptr) {
            if(temp->data == data) {
                Node *new_temp = temp->next;
                delete temp;
                prev->next = new_temp;
                this->list_size--;
                return;
            }
            temp = temp->next;
        }

        // If given data was not found
        std::cerr << "Error: Data not found!!\n";
    }

    Node* get_head() {
        // Getter method for the head pointer
        return this->head;
    }

    Node* get_tail() {
        // Getter method for the tail pointer
        return this->tail;
    }

    size_t get_size() {
        //Getter method for the size of the list
        return this->list_size + 1;
    }

    T operator[](size_t index) const{
        if(this->head == NULL) {
            throw std::runtime_error("Error: LinkedList is empty!!\n");
        }

        if(index < 0) {
            throw std::runtime_error("Error: Given index is a negative number!!\n");
        }

        if(index == 0) {
            return this->head->data;
        }

        if(index == list_size) {
            return this->tail->data;
        }

        Node *temp = this->head;
        size_t flag = 0;
        while(flag < index && temp != nullptr) {
            temp = temp->next;
            flag++;
        }

        if(temp == NULL) {
            throw std::runtime_error("Error: Given index is out of bounds!!\n");
        }

        return temp->data;
    }

private:
    void free_node() {
        // This functions frees all the allocated nodes
        Node *temp = this->head;
        while(temp != nullptr) {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }

        this->head = NULL;
    }

public:
    ~LinkedList<T>() { // Deconstructor (called before program ends)
        free_node();
    }
};

// Driver Code
int main() {

    LinkedList<char*> myList;

}