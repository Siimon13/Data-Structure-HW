// CS2134 Fall 2016
// Homework 10 PQ2 Solution

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "catch.hpp"
using namespace std;



/*
There were a lot of questions about why we needed to read two files. 
the MTA_trainstop_data.txt file includes some stops that DON'T have an adjacent stop. 
While it is possible to pass the unit test with reading just the transfer.txt file,
for grading purposes we will be checking whether both files have been read. 
*/
class trainStopData {
public:
    trainStopData(const string& id, const string& name, double lat, double lon)
                  : stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon) {}
    string get_id()         const { return stop_id; }
    string get_stop_name()  const { return stop_name; }
    double get_latitude()   const { return stop_lat; }
    double get_longitude()  const { return stop_lon; }
private:
    string stop_id;
    string stop_name;
    double stop_lat;
    double stop_lon;
};

// Fill up all the keys with the stop_ids from MTA_train_stop_data
void initializeMap (unordered_map < string, list<string> >& adjList) {
    // Open the MTA_train_stop_data.txt file
    ifstream stopFile("MTA_train_stop_data.txt");
    if (!stopFile) {
        cerr << "The file for train stop data cannot be found.\n";
        exit(1);
    }
    // Read the file line-by-line
    string line;
    getline(stopFile, line);

    // Note: I'm going to fill up a vector first, so that I can add adjacencies for stops on the same line
    // You don't have to do it this way, and this may not be the best approach
    vector<string> stops;

    while (getline(stopFile, line)) {
        // Get the stop_id, which is the first element on each line
        stringstream eachLine(line);
        string element;

        // We use comma-delimiting to get the stop_id, which is before the first comma
        // This will store the stop_id into element
        getline(eachLine, element, ',');

        // Get rid of the stops that have 'N' or 'S' after them
        // If you don't do this, it's totally fine, since it won't break the rest of our code

        // Note: I'm going to fill up a vector first, so that I can add adjacencies for stops on the same route
        // You don't have to do it this way, and this may not be the best approach
        if (element[element.size() - 1] != 'N' && element[element.size() - 1] != 'S')
            stops.push_back(element);
    }

    // Sort the vector of stops, so you ensure that all the stops on the same route are listed in order
    sort(stops.begin(), stops.end());

    // At this point, I have a vector that's sorted in order, so the stops on the same line that are one stop away 
    // from each other are listed together, in order.
    for (int i = 0; i < stops.size(); i++) {
        // Create the adjacency list for this stop
        list<string> adj;

        // For the first element, we can't check the element before us, so this is an edge case
        if (i == 0) {
            // Make sure that there's actually a next stop, and that the first character of that stop
            // is the same as the first character of this stop. If so, it's on the same route and we add
            // it to our adjacency list.
            if (stops.size() > 0 && stops[i][0] == stops[i+1][0]) adj.push_back(stops[i+1]);

        // For the last element, we can't check the element after us, so this is an edge case
        } else if (i == stops.size() - 1) {
            // Make sure that there's more than just one stop, and that the first character of the
            // last stop is the same as the first character of this stop (that means they're on the same route)
            if (stops.size() > 0 && stops[i-1][0] == stops[i][0]) adj.push_back(stops[i-1]);

        // Otherwise, check the element both before and after
        } else {
            // Add the previous stop if it's on the same route
            if (stops[i-1][0] == stops[i][0]) adj.push_back(stops[i-1]);

            // Add the following stop if it's on the same route
            if (stops[i][0] == stops[i+1][0]) adj.push_back(stops[i+1]);
        }

        // Insert this stop into the map
        adjList.insert( {stops[i], adj} );
    }
    stopFile.close();
}

// Add the transfers to each adjacency list 
void addTransfers (unordered_map < string, list<string> >& adjList) {
    // Open the transfers.txt file
    ifstream transfersFile("transfers.txt");
    if (!transfersFile) {
        cerr << "The file for train stop data cannot be found.\n";
        exit(1);
    }
    // Read the file line-by-line
    string line;
    getline(transfersFile, line);
    while (getline(transfersFile, line)) {
        // Get the first two elements in each line
        stringstream eachLine(line);
        string fromStop;
        string toStop;
        // Get the from_stop_id
        getline(eachLine, fromStop, ',');
        // Get the to_stop_id
        getline(eachLine, toStop, ',');
        // Add the toStop to the adjacency list of the fromStop
        // Make sure that the two are different stops
        if (fromStop != toStop) adjList[fromStop].push_back(toStop);
    }
    transfersFile.close();
}

// This is for testing purposes, to print the adjacency list
void printList (const list<string>& ls) {
    for (list<string>::const_iterator a = ls.begin(); a != ls.end(); a++)
        cout << *a << " ";
    cout << endl;
}

SCENARIO("Checking for adjacency") {
	GIVEN("Some subways with adjacency are tested") {
		unordered_map < string, list<string>> adjList;
		initializeMap(adjList);
		addTransfers(adjList);
		WHEN("The container has been populated") {

			//checking if stop 125 is there
			unordered_map < string, list<string>> ::iterator adjListItr = adjList.find("125");
			THEN("125 is a stop in the container ") {
				//make sure find returns a true
				REQUIRE(adjListItr != adjList.end());
			}
			THEN("The adjacency list of stop 125 is correctly stored") {
				//go through and check all of adjacency list of station 125 
				vector<string> adjVec;
				//putting all the adjacent stops in a vector so that the order in which they were inserted into the map doesn't matter
				for (list<string>::iterator litr = adjListItr->second.begin(); litr != adjListItr->second.end(); litr++) {
					adjVec.push_back(*litr);
				}

				//Checking to see if stops 124, A24, and 126 are there 
				bool stop124 = false;
				bool stopA24 = false;
				bool stop126 = false;
				for (int i = 0; i < adjVec.size(); i++) {
					if (adjVec[i] == "124") stop124 = true;
					else if (adjVec[i] == "A24") stopA24 = true;
					else if (adjVec[i] == "126") stop126 = true;
				}
				REQUIRE(stop124);
				REQUIRE(stopA24);
				REQUIRE(stop126);

			}

			//checking if stop B16 is there
			unordered_map < string, list<string>> ::iterator adjListItr2 = adjList.find("B16");
			THEN("B16 is a stop in the container ") {
				//make sure find returns a true
				REQUIRE(adjListItr2 != adjList.end());
			}
			THEN("The adjacency list of stop B16 is correctly stored") {
				//go through and check all of adjacency list of station 125 
				vector<string> adjVec;
				//putting all the adjacent stops in a vector so that the order in which they were inserted into the map doesn't matter
				for (list<string>::iterator litr = adjListItr2->second.begin(); litr != adjListItr2->second.end(); litr++) {
					adjVec.push_back(*litr);
				}

				//Checking to see if stops B15, N04 and B17 are there 
				bool stopB15 = false;
				bool stopN04 = false;
				bool stopB17 = false;
				for (int i = 0; i < adjVec.size(); i++) {
					if (adjVec[i] == "B15") stopB15 = true;
					else if (adjVec[i] == "N04") stopN04 = true;
					else if (adjVec[i] == "B17")stopB17 = true;
				}
				REQUIRE(stopB15);
				REQUIRE(stopN04);
				REQUIRE(stopB17);

			}
		}
	}
}
