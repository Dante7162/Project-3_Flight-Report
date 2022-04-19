#pragma once
#include <iomanip>

using namespace std;

class SortInPlace {
public:
    struct Node {
        int sum;
        int flights;
        float avg;
        string name;
        Node* next;
        Node* prev;
    public:
        Node() {
            sum = 0;
            flights = 0;
            avg = 0;
            name = "";
            next = nullptr;
            prev = nullptr;
        }
    };
private:
    unsigned int numNodes;
    Node* head;
    Node* tail;
public:
    /*=== Constructors / Big 3 ===*/
    SortInPlace() {
        numNodes = 0;
        head = nullptr;
        tail = nullptr;
    }
    ~SortInPlace() {
        if (numNodes > 0) {
            head->prev = nullptr;
            tail->next = nullptr;
        }
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        tail = nullptr;
        numNodes = 0;
    }
    /*=== Insertion ===*/

    void newNode(string name, int delay) {
        Node* node = this->Find(name);
        if (node == nullptr) {
            Node* node = new Node;
            node->name = name;
            node->sum += delay;
            node->flights++;
            node->avg = delay;
            insertNode(node);
            numNodes++;
        }
        else {
            node->sum += delay;
            node->flights++;
            node->avg = (float)node->sum / (float)node->flights;
            if (numNodes > 1 && ((node->prev != tail && node->next != head && (node->avg < node->prev->avg || node->avg > node->next->avg)) || ((node == head && node->next->avg < node->avg) || (node == tail && node->prev->avg > node->avg)))) {
                Remove(node);
                insertNode(node);
            }
        }

    }
    void insertNode(Node* node) {
        //changes pointers to put node in the correct spot
        Node* toAdd = node;
        if (numNodes == 0) {
            head = toAdd;
            tail = toAdd;

            tail->next = head;
            head->prev = tail;
        }
        else {
            Node* curr = head;

            while (node->avg > curr->avg && curr != tail)
                curr = curr->next;

            if (node->avg < curr->avg) {
                toAdd->prev = curr->prev;
                curr->prev = toAdd;
                toAdd->next = curr;
                toAdd->prev->next = toAdd;

                if (curr == head) {
                    head = node;
                    tail->next = head;
                    head->prev = tail;
                }
            }
            else {
                node->prev = curr;
                node->next = curr->next;
                curr->next = node;
                node->next->prev = node;

                if (curr == tail) {
                    tail = node;
                    head->prev = tail;
                    tail->next = head;
                }
            }
        }

    }
    void Remove(Node* node) {
        Node* curr = head;
        for (unsigned int i = 0; i < numNodes; i++) {
            if (curr->name == node->name && numNodes > 1) {
                Node* toBeRemoved = curr;
                Node* left = toBeRemoved->prev;
                Node* right = toBeRemoved->next;
                if (i == 0) {
                    head = toBeRemoved->next;
                    head->prev = tail;
                }
                else if (i == numNodes - 1) {
                    tail = toBeRemoved->prev;
                    tail->next = head;
                }
                else {
                    left->next = right;
                    right->prev = left;
                }
                toBeRemoved->prev = nullptr;
                toBeRemoved->next = nullptr;
                curr = right;
                break;
            }
            else
                curr = curr->next;
        }

    }
    /*=== Accessors ===*/
    Node* Find(const string& name) {
        Node* curr = head;
        for (unsigned int i = 1; i <= numNodes; i++) {
            if (curr->name == name)
                return curr;
            curr = curr->next;
        }
        return nullptr;
    }
    /*=== Behaviors ===*/
    void PrintEfficent() const {
        Node* curr = head;
        cout << "10 Most Efficient Airports" << endl << "Airports | Average Delay(minutes)" << endl << "------------------------" << endl;
        for (unsigned int i = 0; i < 10; i++) {
            cout << i + 1 << ".  " << curr->name << "         " << setprecision(3) << curr->avg << endl;
            curr = curr->next;
        }
    }
    void PrintInefficent() const {
        Node* curr = tail;
        cout << "10 Most Inefficient Airports" << endl << "Airports | Average Delay(minutes)" << endl << "------------------------" << endl;
        for (unsigned int i = 0; i < 10; i++) {
            cout << i + 1 << ".  " << curr->name << "         " << setprecision(3) << curr->avg << endl;
            curr = curr->prev;
        }
    }
    void PrintAll() const {
        Node* curr = head;
        cout << "All Airports" << endl << "Airports | Average Delay(minutes)" << endl << "------------------------" << endl;
        for (unsigned int i = 0; i < numNodes; i++) {
            cout << i + 1 << ".  " << curr->name << "         " << setprecision(3) << curr->avg << endl;
            curr = curr->next;
        }
    }
};