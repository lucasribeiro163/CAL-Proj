
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "POI.h"
#include "Passenger.h"



using namespace std;

class Bus {
	int id;
	vector<Passenger> passengers;
	vector<POI> route;


public:

	Bus();

	Bus(int id);

	Bus(int id, vector<Passenger> passengers);

	bool operator==(Bus rhs) {

		return this->id == rhs.getId();

	}
	bool operator==(Bus& rhs) {

		return this->id == rhs.getId();

	}
	bool operator!=(Bus& rhs) {

		return this->id != rhs.getId();

	}

	int getId();
	void setId(int id);
	void addPassenger(Passenger *passenger);
	void addToRoute(POI *poi);
	bool isBeingUsed();

};



Bus::Bus() {}


Bus::Bus(int id) {

	this->id = id;

}


Bus::Bus(int id, vector<Passenger> passengers) {

	this->id = id;

	this->passengers = passengers;
}



int Bus::getId() {

	return this->id;

}


void Bus::addPassenger(Passenger *passenger){

	this->passengers.push_back(*passenger);

}


void Bus::setId(int id) {

	this->id = id;

}



void Bus::addToRoute(POI *poi) {

	route.push_back(*poi);


}


bool Bus::isBeingUsed() {

	if (this->route.empty())
		return false;
	else
		return true;
	
}


#endif /*SRC_BUS_H_*/