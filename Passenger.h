
#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include <vector>
#include <string>
//#include "Graph.h"



using namespace std;

class Passenger {
	int id;
	vector<int> nodes;


public:

	Passenger();

	Passenger(int id);

	Passenger(int id, vector<int> nodes);

	bool operator==(Passenger rhs) {

		return this->id == rhs.getId();

	}
	bool operator==(Passenger& rhs) {

		return this->id == rhs.getId();

	}
	bool operator!=(Passenger& rhs) {

		return this->id != rhs.getId();

	}

	int getId();
	void addNode(int node);
	void setId(int id);
	void printNodes();

};



Passenger::Passenger() {}


Passenger::Passenger(int id) {

	this->id = id;

}


Passenger::Passenger(int id, vector<int> nodes) {

	this->id = id;

	this->nodes = nodes;
}



int Passenger::getId() {

	return this->id;

}

void Passenger::addNode(int node) {

	this->nodes.push_back(node);



}


void Passenger::setId(int id) {

	this->id = id;

}

void Passenger::printNodes() {

	cout << "Nodes of " << this->id << ": \n";

	for (int i = 0; i < this->nodes.size(); i++) {

		cout << this->nodes.at(i) << endl;

	}

}




#endif /*SRC_PASSENGER_H_*/
