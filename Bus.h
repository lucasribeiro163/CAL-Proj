
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
	int capacity;
	int nr_people_in = 0;
	vector<Passenger*> passengers;
	vector<Vertex<POI>*> route;


public:

	Bus();

	Bus(int id);

	Bus(int id, int capacity);

	Bus(int id, vector<Passenger*> passengers);

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
	bool isBeingUsed();

	void printpassengers();

	int getNrPeopleIn();

	void setRoute(vector<Vertex<POI>*> newRoute);

};



Bus::Bus() {}


Bus::Bus(int id) {

	this->id = id;

}

Bus::Bus(int id, int capacity) {

	this->id = id;

	this->capacity = capacity;

}


Bus::Bus(int id, vector<Passenger*> passengers) {

	this->id = id;

	this->passengers = passengers;
}



int Bus::getId() {

	return this->id;

}


void Bus::addPassenger(Passenger *passenger){

	this->passengers.push_back(passenger);
	nr_people_in++;

}


void Bus::setId(int id) {

	this->id = id;

}


int Bus::getNrPeopleIn() {

	return this->nr_people_in;


}



bool Bus::isBeingUsed() {

	if (this->route.empty())
		return false;
	else
		return true;
	
}


void Bus::setRoute(vector<Vertex<POI>*> newRoute) {


	this->route = newRoute;


}


void Bus::printpassengers() {

	for (int i = 0; i < passengers.size(); i++) {


		cout << "Passenger nr " << i << ": " << passengers.at(i)->getId() << endl;


	}


}




#endif /*SRC_BUS_H_*/