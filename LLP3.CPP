#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class LinkedList
{
public:

	struct Node
	{
        string name;
		int sumDelay;
        double avg;
        int totalFlights;
		Node* next;
		Node* prev;

		Node() {
			next = nullptr;
			prev = nullptr;
            string name = "";
		    int sumDelay = 0;
            double avg = 0;
            int totalFlights = 0;
		};
		//~Node();*/

	};
	
	//============================================== P A R T 1 ===========================================================
	LinkedList();

    //add Node
    void addNode(string name, int delay);

    //sort
    void BubbleSort();
    void MergeSort();
    void mergeSortLL(Node*& head);
    Node* merge(Node*& A, Node*& B) ;
    

	void PrintForward();


	Node* Find(string& name);

	

private:

	unsigned int _count;
	Node* _head;
	Node* _tail;

};

LinkedList::LinkedList(){
	_head = nullptr;
	_tail = nullptr;
	_count = 0;
}

void LinkedList::addNode(string name, int delay){

    Node* avgNode;

    if(_count == 0){
        Node* newNode = new Node();
		newNode->name = name;
        newNode->sumDelay = delay;
        newNode->totalFlights = 1;
		_head = newNode;
		_tail = newNode; 
        avgNode = newNode;
        _count++;
    }else{
        Node* temp = Find(name);
        if(temp){
            temp->sumDelay += delay;
            temp->totalFlights++;
            avgNode = temp;;
        }else{
            Node* newNode = new Node();
		    _tail->next = newNode;
            newNode->name = name;
            newNode->sumDelay = delay;
            newNode->totalFlights = 1;
            newNode->prev = _tail;
		    newNode->next = nullptr;
		    _tail = newNode;
            avgNode = newNode;
            _count++;
        }
    }

    avgNode->avg = (double)avgNode->sumDelay/avgNode->totalFlights;
    
}

LinkedList::Node* LinkedList::Find(string& name){

    Node* temp = _head;
    while(temp != nullptr){
        if(temp->name == name){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void LinkedList::BubbleSort(){
    bool done = false;
    Node* temp = _head;
while(!done){
    done = true;
    while(temp != nullptr){       
        if(temp->next != nullptr ){
            
            if(temp->avg > temp->next->avg){
                if(temp == _head){
                    _head = temp->next;
                    Node* temp1 = _head->next;
                    _head->next = temp;
                    _head->prev = nullptr;
                    temp->next = temp1;
                    temp->prev = _head;
                    temp1->prev = temp;
                    temp = _head;
                }else{
                  Node* node2 = temp->next;
                  Node* nPrev = temp->prev;
                  Node* temp1 = node2->next;

                  node2->next = temp;
                  node2->prev = temp->prev;
                   
                  temp->prev = node2;
                  temp->next = temp1;

                  nPrev->next = node2;

                  temp = node2;
                }
                done = false;
            }
        } else if(!done){
            temp = _head;
            done = true;
            continue;
        }

        temp = temp->next;
    }
}
}

void LinkedList::MergeSort(){
    mergeSortLL(_head);
}


void LinkedList::mergeSortLL(Node*& head){
    if (head->next != nullptr)
	{
		Node* A;
		Node* B = head;				
		
		//Calculate length of the linked list
		int len = 0; 
		Node* curr = head;
		while (curr != nullptr)
		{
			len++;
			curr = curr->next;
		}

		for (int i = 0; i < len / 2; i++)		
		{
			A = B;				
			B = B->next;	
		}

		A->next = nullptr;
		A = head;

		mergeSortLL(A);
		mergeSortLL(B);
		head = merge(A, B);
	}
	
}

LinkedList::Node* LinkedList::merge(Node*& A, Node*& B){
    Node* mergedNode; //returned merged node

	if (A == nullptr) return B;
	else if (B == nullptr) return A;

	if (A->avg < B->avg) 
	{
		mergedNode = A;
		mergedNode->next = merge(A->next, B);
	}
	else 
	{
		mergedNode = B;
		mergedNode->next = merge(A, B->next);
	}

	return mergedNode;

}

void LinkedList::PrintForward(){
     Node* temp = _head;
    while(temp != nullptr){
       cout << temp->name << ": " << temp->avg << endl;
       temp = temp->next;
    }

    cout << "total node: " << _count << endl;
}