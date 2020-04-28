// Graphs - Use Dijkstra's algorithm to find the shortest path (int)
//			between two airports (strings)
// Author: Raphael Juco
// Purpose:		 
// Notes:		Used geeksforgeeks for reference on how to tackle
//				the Dijkstra's algorithm

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
using namespace std;

class Graph {
	// creates a hashmap with a key (from airport) 
	// to pairs of (to airport, distance between them)
	unordered_map <string, list<pair<string, int>>> map;

public:
	// addEdge: adds the pair - airport codes and distance 
	//			between them into the map
	// Precondition: passed in int must be non-negative number
	// Postcondition: map contains data of the distance
	//				  between two airports if successful
	void addEdge(string from, string to, int dist) {		
		map[from].push_back(make_pair(to, dist));
		map[to].push_back(make_pair(from, dist));
	}

	// findShortestPath: finds the shortest distance between two 
	//					 airport codes passed in using Dijkstra's
	//					 algorithm
	// Precondition: passed in string must be valid airport codes
	//				 or function will not work
	// Postcondition: distances contains a map of distances between 
	//				  the from airport code to all other airport codes
	void findShortestPath(string from, string toFind) {			
		unordered_map<string, int> distances;

		// set all distances to infinity
		for (auto i : map) {
			distances[i.first] = INT_MAX;
		}

		// make a set to find the min distance
		set <pair<int, string>> setds;
		distances[from] = 0;
		setds.insert(make_pair(0, from));

		while (!setds.empty()) {
			// saves the pair in front of the set
			auto p = *(setds.begin());
			string node = p.second;

			int nodeDist = p.first;
			// deletes the pair in front of the set
			setds.erase(setds.begin());

			// iterate over neighbors of the current node
			for (auto neighborPair : map[node]) {
				if (nodeDist + neighborPair.second < distances[neighborPair.first]) {
					string destination = neighborPair.first;
					auto j = setds.find(make_pair(distances[destination], destination));
					if (j != setds.end()) {
						setds.erase(j);
					}
					// insert new pair
					distances[destination] = nodeDist + neighborPair.second;
					setds.insert(make_pair(distances[destination], destination));
				}
			}
		}
		// find and print distance from initial airport to dest airport
		bool fromFound = false;
		bool destFound = false;
		int distFound;
		for (auto d : distances) {
			if (d.first == from) {
				fromFound = true;
			}
			if (d.first == toFind) {
				destFound = true;
				distFound = d.second;
			}
		}
		if (fromFound == true && destFound == true) {
				cout << toFind << " is located at distance of " << distFound;
				cout << " from " << from << endl;
		}
		else {
			cout << "At least one airport input cannot be found" << endl;
		}
	}
};

// main: creates an instance of class Graph and opens a file to read in airport
//		 codes and distances and stores it in the instance of Graph using it's
//		 functions. Prompts the user to enter airport codes and prints the 
//		 distance between them.
// Precondition: Graph class is defined and read in textfile name is valid 
// Postcondition: none
int main() {
	Graph g;
	ifstream inFile;
	string from, to;
	int current;

	inFile.open("AirportDistances.txt");

	if (!inFile) {
		cout << "File cannot be opened";
		return 0;
	}
	while (inFile >> from >> to >> current) {
		g.addEdge(from, to, current);
	}
	cout << "Enter the first location of airport." << endl;
	cin >> from;
	cout << "Enter the airport destination." << endl;
	cin >> to;
	g.findShortestPath(from, to);
}
