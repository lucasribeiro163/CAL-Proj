
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

	vector<int> *getNodes();


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


	cout << "\nNodes of " << this->id << ": \n";

	if (this->nodes.empty())
		cout << "\nNodes vector is empty\n";

	for (unsigned int i = 0; i < this->nodes.size(); i++) {

		cout << this->nodes.at(i) << endl;

	}

}


vector<int>* Passenger::getNodes() {

	return &this->nodes;

}




#endif /*SRC_PASSENGER_H_*/
