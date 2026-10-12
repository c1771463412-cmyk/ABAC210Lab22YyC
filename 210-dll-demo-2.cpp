
// COMSC-210-5293 | Lab 22 | Yuyi Chen

#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;

        // Node() creates a new node with a value and two pointers
        // arguments: val - node value, p - previous node, n - next node
        // returns: none
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // DoublyLinkedList() creates an empty doubly linked list
    // arguments: none
    // returns: none
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // push_back() adds a new node to the end of the list
    // arguments: value - number to add
    // returns: none
    void push_back(int value) {
        Node* newNode = new Node(value);

        if (!tail)  // If the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // push_front() adds a new node to the beginning of the list
    // arguments: value - number to add
    // returns: none
    void push_front(int value) {
        Node* newNode = new Node(value);

        if (!head)  // If the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // pop_front() deletes the first node in the list
    // arguments: none
    // returns: none
    void pop_front() {
        if (!head) {
            return; // Nothing to delete
        }

        Node* temp = head;
        head = head->next;

        // Update the new head or clear the tail
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }

        delete temp; // Free the old head
    }

    // pop_back() deletes the last node in the list
    // arguments: none
    // returns: none
    void pop_back() {
        if (!tail) {
            return; // Nothing to delete
        }

        Node* temp = tail;
        tail = tail->prev;

        // Update the new tail or clear the head
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }

        delete temp; // Free the old tail
    }

    // delete_pos() deletes a node at the given position
    // arguments: position - index of the node to delete
    // returns: none
    void delete_pos(int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        if (!head) {
            return; // Empty list
        }

        Node* temp = head;

        // Find the node at the given position
        for (int i = 0; i < position && temp; ++i) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "Position exceeds list size." << endl;
            return;
        }

        // Connect the previous node to the next node
        // If there is no previous node, update head
        if (temp->prev) {
            temp->prev->next = temp->next;
        }
        else {
            head = temp->next;
        }

        // Connect the next node to the previous node
        // If there is no next node, update tail
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        else {
            tail = temp->prev;
        }

        delete temp; // Free the selected node
    }

    // insert_after() inserts a new node after the given position
    // arguments: value - number to add, position - insertion position
    // returns: none
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);

        // If the list is empty, the new node becomes head and tail
        if (!head) {
            head = tail = newNode;
            return;
        }

        // Find the node at the given position
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        // Connect the new node to the surrounding nodes
        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end

        temp->next = newNode;
    }

    // delete_val() deletes the first node with the given value
    // arguments: value - number to delete
    // returns: none
    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;

        // Search for the first node with the matching value
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        // Update the previous node or head
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        // Update the next node or tail
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp; // Free the selected node
    }

    // print() displays all nodes from head to tail
    // arguments: none
    // returns: none
    void print() {
        Node* current = head;

        if (!current) return;

        // Move forward through the list
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }

    // print_reverse() displays all nodes from tail to head
    // arguments: none
    // returns: none
    void print_reverse() {
        Node* current = tail;

        if (!current) return;

        // Move backward through the list
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }

        cout << endl;
    }

    // ~DoublyLinkedList() deletes all nodes to free memory
    // arguments: none
    // returns: none
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList list;

    // Create a list with five nodes
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);

    cout << "Original list: ";
    list.print();

    // Test deleting a middle node by position
    cout << "\nDelete position 2:" << endl;
    list.delete_pos(2);
    list.print();

    // Test deleting the head by position
    cout << "\nDelete position 0 (head):" << endl;
    list.delete_pos(0);
    list.print();

    // Test deleting the tail by position
    cout << "\nDelete position 2 (tail):" << endl;
    list.delete_pos(2);
    list.print();

    // Test pop_front()
    cout << "\nPop front:" << endl;
    list.pop_front();
    list.print();

    // Test pop_back()
    cout << "\nPop back:" << endl;
    list.pop_back();
    list.print();

    // Test deleting from an empty list
    cout << "\nTest empty list:" << endl;
    list.pop_front();
    list.pop_back();
    list.delete_pos(0);
    list.print();

    // Test deleting an invalid position
    cout << "\nTest invalid positions:" << endl;
    list.push_back(60);
    list.push_back(70);
    list.delete_pos(-1);
    list.delete_pos(10);
    list.print();

    // Test delete_val() with the head node
    cout << "\nDelete value 60 (head):" << endl;
    list.delete_val(60);
    list.print();

    // Test delete_val() with the tail node
    cout << "\nDelete value 70 (tail):" << endl;
    list.delete_val(70);
    list.print();

    // Test delete_val() with a middle node
    cout << "\nDelete middle value 90:" << endl;
    list.push_back(80);
    list.push_back(90);
    list.push_back(100);
    list.delete_val(90);
    list.print();

    // Test forward and backward traversal
    cout << "\nList forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    // Test pop_front() with only one node
    cout << "\nPop front with one node:" << endl;
    DoublyLinkedList test1;
    test1.push_back(10);
    test1.pop_front();
    test1.print();

    // Test pop_back() with only one node
    cout << "\nPop back with one node:" << endl;
    DoublyLinkedList test2;
    test2.push_back(20);
    test2.pop_back();
    test2.print();

    // Test delete_pos() with only one node
    cout << "\nDelete position 0 with one node:" << endl;
    DoublyLinkedList test3;
    test3.push_back(30);
    test3.delete_pos(0);
    test3.print();

    return 0;
}
