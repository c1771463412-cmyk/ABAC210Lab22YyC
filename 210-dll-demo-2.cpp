// COMSC-210-5293 | Lab 22 | Yuyi Chen

#include <iostream>
using namespace std;

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
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {
        if (!head) {
            return;
        }

        Node* temp = head;
        head = head->next;

        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }

        delete temp;
    }

    void pop_back() {
        if (!tail) {
            return;
        }

        Node* temp = tail;
        tail = tail->prev;

        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }

        delete temp;
    }

    void delete_pos(int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        if (!head) {
            return;
        }

        Node* temp = head;

        for (int i = 0; i < position && temp; ++i) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "Position exceeds list size." << endl;
            return;
        }

        if (temp->prev) {
            temp->prev->next = temp->next;
        }
        else {
            head = temp->next;
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        else {
            tail = temp->prev;
        }

        delete temp;
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
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
