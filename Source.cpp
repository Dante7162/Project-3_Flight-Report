// Simplified Page Rank; last edited by DYL 04.14.2022
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iterator>
#include <iomanip>

using namespace std;

class Graph {
private:
	int n;
	int p;
	map<string, int> indegrees;
	map<string, vector<pair<string, float>>> adjacencyList;
	map<string, float> pageRank;
public:
	Graph(int lines, int iterations) {
		n = lines;
		p = iterations - 1;
	}

	void takeInput(string from, string to) {
		if (indegrees.find(from) != indegrees.end())
			//if in indegrees than increase the indegree for that node
			indegrees[from]++;
		else //else initialize indegree to 1
			indegrees[from] = 1;

		//add to adjacency list
		adjacencyList[to].push_back(make_pair(from, 1));

		//line from TA 
		if (adjacencyList.find(from) == adjacencyList.end())
			adjacencyList[from] = {};
	}

	void replaceAdjacencyList() {
		for (auto index = adjacencyList.begin(); index != adjacencyList.end(); index++) {
			//for every node in adjacency list
			vector<pair<string, float>> edges = adjacencyList[index->first];

			for (int i = 0; i < edges.size(); i++) {
				//for every edge in the current node

				//give the edge the weight from indegree
				index->second.at(i).second = indegrees[index->second.at(i).first];

				//if only one edge to this node
				if (indegrees.count(edges[i].first) == 1) {
					int val = indegrees[edges[i].first];
					string name = edges[i].first;
					//erase this node
					adjacencyList[index->first].erase(adjacencyList[index->first].begin() + i);
					//reset node with updated indegree
					adjacencyList[index->first].insert(adjacencyList[index->first].begin() + i, make_pair(name, 1.0 / val));
				}
			}
		}
	}

	void initializePageRank() {
		//initialize page rank to 1/|v|
		for (auto index = adjacencyList.begin(); index != adjacencyList.end(); index++)
			pageRank[index->first] = 1.0 / adjacencyList.size();
	}

	void powerIterations() {
		map < string, float> temp;
		for (int i = p; i > 0; i--) {
			//for however many number of iterations
			for (auto index = pageRank.begin(); index != pageRank.end(); index++) {
				//for every map pair of page rank
				float sum = 0.0;

				//if unique edge
				if (adjacencyList.count(index->first) == 1) {
					vector<pair<string, float>> edges = adjacencyList[index->first];

					for (int j = 0; j < edges.size(); j++) {
						//for every edge

						//rank formula
						float valInMap2 = edges[j].second;
						float valInMap3 = pageRank[edges[j].first];
						sum += valInMap2 * valInMap3;
					}
					//add to a new page rank template
					temp[index->first] = sum;
				}
			}
			//transfer to page rank
			pageRank = temp;
			temp.clear();
		}
	}

	void display() {
		for (auto index = pageRank.begin(); index != pageRank.end(); index++) {
			cout << index->first << " " << fixed << setprecision(2) << index->second << endl;
		}
	}
};

int main() {
	int n;
	int p;
	
	cin >> n >> p;

	Graph webpages(n, p);

	string from; 
	string to;
	for (int i = 0; i < n; i++) {
		cin >> from >> to;
		webpages.takeInput(from, to);
	}
	
	webpages.replaceAdjacencyList();

	webpages.initializePageRank();

	webpages.powerIterations();

	webpages.display();

	return 0;
}
