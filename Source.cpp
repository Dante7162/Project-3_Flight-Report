#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "SortInPlace.h"
#include "SortAfter.h"

using namespace std;
using namespace std::chrono;

void runCode(SortInPlace inPlace) {
    string name;
    int delay;

    SortAfter merge;
    SortAfter bubble;

    cout << "Time it takes to take input and sort-" << endl;

    auto start = high_resolution_clock::now();

    ifstream file("flights_data.csv");

    for (int i = 0; i < 100049; i++) {
        getline(file, name);

        delay = stoi(name.substr(name.find(',') + 1, name.size() - name.find(',')));
        if (i == 0)
            name = name.substr(3, 3);
        else
            name = name.substr(0, 3);

        inPlace.newNode(name, delay);
    }
    file.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "In place sort: " << duration.count() << " milliseconds" << endl;


    start = high_resolution_clock::now();

    ifstream fileTwo("flights_data.csv");

    for (int i = 0; i < 100049; i++) {
        getline(fileTwo, name);

        delay = stoi(name.substr(name.find(',') + 1, name.size() - name.find(',')));
        if (i == 0)
            name = name.substr(3, 3);
        else
            name = name.substr(0, 3);

        merge.addNode(name, delay);
    }
    fileTwo.close();

    merge.MergeSort();
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Merge sort: " << duration.count() << " milliseconds" << endl;


    start = high_resolution_clock::now();

    ifstream fileThree("flights_data.csv");

    for (int i = 0; i < 100049; i++) {
        getline(fileThree, name);

        delay = stoi(name.substr(name.find(',') + 1, name.size() - name.find(',')));
        if (i == 0)
            name = name.substr(3, 3);
        else
            name = name.substr(0, 3);

        bubble.addNode(name, delay);
    }
    fileThree.close();

    bubble.BubbleSort();
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Bubble sort: " << duration.count() << " milliseconds" << endl;

    cout << endl << endl;
}

int main() {
    string name;
    int delay;

    SortAfter merge;
    SortAfter bubble;
    SortInPlace inPlace;

    cout << "Time it takes to take input and sort-" << endl;

    auto start = high_resolution_clock::now();

    ifstream file("flights_data.csv");

    for (int i = 0; i < 100049; i++) {
        getline(file, name);

        delay = stoi(name.substr(name.find(',') + 1, name.size() - name.find(',')));
        if (i == 0)
            name = name.substr(3, 3);
        else
            name = name.substr(0, 3);

        inPlace.newNode(name, delay);
    }
    file.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "In place sort: " << duration.count() << " milliseconds" << endl;


    start = high_resolution_clock::now();

    ifstream fileTwo("flights_data.csv");

    for (int i = 0; i < 100049; i++) {
        getline(fileTwo, name);

        delay = stoi(name.substr(name.find(',') + 1, name.size() - name.find(',')));
        if (i == 0)
            name = name.substr(3, 3);
        else
            name = name.substr(0, 3);

        merge.addNode(name, delay);
    }
    fileTwo.close();

    merge.MergeSort();
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Merge sort: " << duration.count() << " milliseconds" << endl;


    start = high_resolution_clock::now();

    ifstream fileThree("flights_data.csv");

    for (int i = 0; i < 100049; i++) {
        getline(fileThree, name);

        delay = stoi(name.substr(name.find(',') + 1, name.size() - name.find(',')));
        if (i == 0)
            name = name.substr(3, 3);
        else
            name = name.substr(0, 3);

        bubble.addNode(name, delay);
    }
    fileThree.close();

    bubble.BubbleSort();
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Bubble sort: " << duration.count() << " milliseconds" << endl;

    cout << endl << endl;

    while (true) {
        cout << "Options:" << endl << "1. Print the 10 most efficient airports" << endl << "2. Print the 10 least efficient airports" << endl << "3. Print both" << endl << "4. Print all" << endl << "5. Run again" << endl << "Enter any other value to exit" << endl;
        int option;
        cin >> option;
        cout << endl << endl;
        if (option == 1)
            inPlace.PrintEfficent();
        else if (option == 2)
            inPlace.PrintInefficent();
        else if (option == 3) {
            inPlace.PrintEfficent();
            cout << endl;
            inPlace.PrintInefficent();
        }
        else if (option == 4)
            inPlace.PrintAll();
        else if (option == 5) {
            SortInPlace newList;
            runCode(newList);
        }
        else
            break;
    }
    

    return 0;
}




