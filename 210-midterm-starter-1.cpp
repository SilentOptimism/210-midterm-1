#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // A constructor for our doublyLinked list: Sets Head/Tail nodes to nullptr so we know its empty and to avoid floating ptrs

    void insert_after(int value, int position) {

        // User validation: Checks if the position isn't negative as you can't have a negative position for a Singularly linked list
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        // Creates a new node on the heap so to be added to the linked list
        Node* newNode = new Node(value);

        // Checks if the list is empty
        if (!head) {
            head = tail = newNode; // if empty it will point the head and tail to the new node establishing the list 
            return; // Exits insert_after as the task is completed
        }

        // Creates a temporary node and points it to the head so that we can iterate through the list with out moving the head ptr
        Node* temp = head;

        // Iterates through postion/temp and checks if we are at the correct position of the temp node has reached the end of the list
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next; // Iterates temp

        // Checks if temp points to a nullptr to see if the position was out of bounds
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // Deletes the node as we have allocated it to the heap and it would remain there if we didn't deallocated it
            return; // Exits the program
        }

        // Sets our new nodes next ptr to the next ptr of the temp node thats at the position where we want to insert the new node
        newNode->next = temp->next;
        // Sets our new nodes prev ptr to our temp node putting it after the desired position
        newNode->prev = temp;

        // Checks if we are at the end of the list
        if (temp->next)
            temp->next->prev = newNode; // If we are not it will set the prev ptr of the node after our newNode to our previous node connecting the list from the right side
        else
            tail = newNode; // If we are at the end it moves the tail to the newNode to keep it current
        temp->next = newNode; // Sets the previous node next ptr to our new node reconnecting our list from the left
    }

    void delete_val(int value) {
        // Checks if list is empty if it is returns immediately
        if (!head) return;

        // Creates a temp node to iterate through the list
        Node* temp = head;
        
        // Checks if the data in the temep is the desired value and if temp has reached the end of the list; meaning is temp a nullptr
        while (temp && temp->data != value)
            temp = temp->next; // Iterates temp

        // Temp being a nullptr means we haven't found the value in the list will return as nothing to delete
        if (!temp) return; 

        // Checks if we are at the head
        if (temp->prev)
            temp->prev->next = temp->next; // If we are not it will redirect the previous node next ptr to the node after the node we are trying to delete which is our current node
        else
            head = temp->next; // If we are at the head it will iterate the head to the next node keeping it current

        // Checks if we are at the tail
        if (temp->next)
            temp->next->prev = temp->prev; // if we are not at the tail it will redirect the next node prev ptr to the node before the node we are trying to delete which is our current node
        else
            tail = temp->prev; // If we are at the tail it will iterate the tail to the left of our soon to be deleted node so it actually points to the tail

        delete temp; // Deletes the temp node which has the data we are trying to remove
    }

    void delete_pos(int pos) {
        // Checks if the list is empty and exits if it is
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        // Checks if we are at the front and will call pop_front to delete that node
        if (pos == 1) {
            pop_front();
            return;
        }
    
        // Creates a Node ptr temp pointing at head to iterate through the list
        Node* temp = head;
    
        // Starts iterating position and our temp node through the list
        for (int i = 1; i < pos; i++){

            // Checks if our temp node points to a nullptr which would be past our tail out of bounds
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return; // Exits program as we are out of bounds
            }
            else
                temp = temp->next; // Iterates our temp node ptr through the list
        }

        // Checks if our temp node ptr is a nullptr
        // This is done as when we last call "temp = temp->next" we can be moved past the end (nullptr) and have also reached our desired position
        // This will cause the for loop to end with out temp being checked to be past the end of the list which it is so we do that test here 
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }


        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    /// @brief puts a new node containing our data v to the end of the list
    /// @param v the data to be put in the node
    void push_back(int v) {
        Node* newNode = new Node(v); // Creates our new node with our v data in it

        // Checks if the list is empty
        // You could also do this test with the head if you wanted as they both will return nullptr if the list is empty
        if (!tail)
            head = tail = newNode; // If the list is empty it will set the tail/head to point to our new node
        else {
            tail->next = newNode; // When the list is not empty it will set the tail's next ptr ot h
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}