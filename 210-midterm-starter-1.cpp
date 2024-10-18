#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;

        /// @brief Node constructor takes the data and constructs the node
        /// @param val the nodes data
        /// @param p the previous ptr (automatically set to nullptr)
        /// @param n 
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // The start of the list
    Node* tail; // The end of the list

public:
    /// @brief creates the list with head/tail pointing to a nullptr indicating its empty
    DoublyLinkedList() { head = nullptr; tail = nullptr; } 

    /// @brief Inserts a node with the given value after the given position
    /// @param value The value node will contain as its data
    /// @param position The new node is inserted after this position
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

    /// @brief Searches for a node containing the given value and deletes it
    /// @param value the data to be removed from the node
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
            return; // exits 
        }

        // Checks if we are before the end of the list
        if (!temp->next) {
            pop_back(); // If we are simply popsback the end node
            return; // exits
        }
    
        // Creates a tempPrev ptr point to the node before temp
        Node* tempPrev = temp->prev; 

        // Sets the node (before temp) next ptr to point to temps next node the node after temp
        tempPrev->next = temp->next;

        // Sets node (after temp) previous ptr to point to the node before temp
        temp->next->prev = tempPrev;

        delete temp; // Deletes the node at temp as all nodes around it have been redirected
    }

    /// @brief puts a new node containing our data v to the end of the list
    /// @param v the data to be put in the new node
    void push_back(int v) {
        Node* newNode = new Node(v); // Creates our new node with our v data in it

        // You could also do this test with the head if you wanted as they both will return nullptr if the list is empty
        // Checks if the list is empty by checking it tail is a nullptr
        if (!tail)
            head = tail = newNode; // If the list is empty it will set the tail/head to point to our new node
        
        // Runs when the list is not empty
        else {
            tail->next = newNode; // sets the tail's next ptr ot h
            newNode->prev = tail; // sets our new node previous ptr to our tail connecting our list
            tail = newNode; // Moves the tail to the new node to keep it up to date
        }
    }
    
    /// @brief Adds a new node to the front/head of our list containing the given data v
    /// @param v The data to be put in the new node
    void push_front(int v) {
        Node* newNode = new Node(v); // Creates our new node with the given data

        // You can also do this test with the tail ptr as they both return nullptr when the list is empty
        // Checks if the list is empty by checking if head points to a nullptr
        if (!head)
            head = tail = newNode; // If empty establishes the list with both the tail and head pointing at our new node
        
        // Runs when the list is not empty
        else {
            newNode->next = head; // sets the newNode next ptr to the head
            head->prev = newNode; // sets the redirects the node the head is currently pointing to so that its previous ptr points at the new node
            head = newNode; // Moves the head left to the new node to keep it current pointing to the zeroth node 
        }
    }
    
    /// @brief Removes the node at the head the front of the list
    void pop_front() {

        // Checks if the list is empty
        if (!head) {
            cout << "List is empty." << endl;
            return; // Exits if empty as the list is already cleared
        }

        // Creates a temporary node ptr to head so that node can be deleted after the head is redirected
        Node * temp = head;

        // Checks if their is only 1 node
        if (head->next) {
            head = head->next; // When there is not 1 node it moves head to the next node
            head->prev = nullptr; // Sets head previous ptr to a nullptr
        }
        else
            head = tail = nullptr; // If the list does have just 1 node it will set both head and tail to be nullptrs
        delete temp; // deletes our temporary node that head used to point to
    }

    /// @brief Removes node at the tail of the list the back
    void pop_back() {
        // Checks if the list is empty
        if (!tail) {
            cout << "List is empty." << endl;
            return; // Exits if the list is empty: nothing to delete
        }
        Node * temp = tail; // Creates a temp ptr to the tail so it can delete the node tail is at after tail is redirected

        // Checks if there is only 1 node in the list
        if (tail->prev) {
            tail = tail->prev; // If there isn't just 1 node it will move tail back 1 node
            tail->next = nullptr; // It will make the node that tail not points to no longer point the formerly tail node by changing its next ptr to a nullptr
        }
        else
            head = tail = nullptr; // if there is only 1 node in the list it will set both tail/head to nullptr to clean the list
        delete temp; // Deletes the temp node as tail has been redirected
    }

    /// @brief Our DoublyLinkedList deconstructor which clears out our list clearing out the heap
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    /// @brief Prints out our linked list
    void print() {
        // Sets a current node ptr to head to iterate through the list
        Node* current = head;

        // Checks if the list is empty
        if (!current) {
            cout << "List is empty." << endl;
            return; // Exits if it is
        }

        // Iterates through printing the list while current points to a nullptr (end of list)
        while (current) {
            cout << current->data << " "; // Prints out data while iterating
            current = current->next; // Iterates our current ptr thorough the list
        }
        cout << endl; 
    }

    /// @brief Prints the linked list reversed
    void print_reverse() {
        // Creates a current node ptr pointing to tail to iterate through the linked list
        Node* current = tail;

        // Checks if current is empty
        if (!current) { 
            cout << "List is empty." << endl;
            return; // If it is exit the list: Nothing to print
        }

        // Checks if current is at the begining of the list
        while (current) {
            cout << current->data << " "; // if not print the data inside current
            current = current->prev; // Iterate current to previous node
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}