#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <cctype>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;
#include "LLP3.CPP"


int main(){

    LinkedList g, a;
    string val, line = "";
	int delay = 0;
    int count = 0;


	ifstream file("flights_data.csv");


	if (!file.is_open()) cout << "COULD NOT OPEN FILE" << endl;

	while (getline(file, line))
	{
		stringstream str(line);
		
		string word;

		getline(str, word, ',');
		val = word;

		getline(str, word, ',');
       // cout << "word: " << word << endl;
		delay = stoi(word);

        g.addNode(val, delay);
        a.addNode(val, delay);

		count++;

	}
    
    cout << "totla: " << count << endl;
    //g.BubbleSort();
    auto start = high_resolution_clock::now();
    a.BubbleSort();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Bubble sort --> Time: " << duration.count() << " ms" << endl;

    //===============================
    auto mstart = high_resolution_clock::now();
    a.MergeSort();
    auto mstop = high_resolution_clock::now();
    auto mduration = duration_cast<microseconds>(mstop - mstart);

    cout << "Merge sort --> Time: " << mduration.count() << " ms" << endl;



    //g.PrintForward();


    return 0;
}