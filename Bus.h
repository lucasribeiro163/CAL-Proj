
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "Passenger.h"


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx



using namespace std;

class Bus {
	int id;
	vector<Passenger> passengers;


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
	void addPassenger(Passenger *passenger);

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





#endif /*SRC_BUS_H_*/