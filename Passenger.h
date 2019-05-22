
#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include <vector>
#include <string>
//#include "Graph.h"


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx


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



#endif /*SRC_PASSENGER_H_*/
