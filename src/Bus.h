
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
	Vertex<POI>* departure_poi;
	Vertex<POI>* arrival_poi;
	vector<int> best_sequence;
	vector<POI> optimal_path;




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
	int getCapacity();
	int getNrPeopleIn();

	bool full();

	Vertex<POI>* getDeparturePOI();
	Vertex<POI>* getArrivalPOI();
	void setDeparturePOI(Vertex<POI>* poi);
	void setArrivalPOI(Vertex<POI>* poi);


	void setRoute(vector<Vertex<POI>*> newRoute);
	vector<Vertex<POI>*> getRoute();
	void setBestSequence(vector<int> best_sequence);
	vector<int> getBestSequence();

	vector<POI> getOptimalPath();
	void setOptimalPath(vector<POI> path);

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

void Bus::setBestSequence(vector<int> best_sequence) {

	this->best_sequence = best_sequence;

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


int Bus::getCapacity() {

	return this->capacity;


}


bool Bus::full() {

	if (capacity == nr_people_in)
		return true;
	else
		return false;


}

vector<Vertex<POI>*> Bus::getRoute(){
	return this->route;
}



Vertex<POI>* Bus::getDeparturePOI() {

	return this->departure_poi;

}


Vertex<POI>* Bus::getArrivalPOI(){

	return this->arrival_poi;

}

void Bus::setDeparturePOI(Vertex<POI>* poi) {

	this->departure_poi = poi;

}

void Bus::setArrivalPOI(Vertex<POI>* poi) {

	this->arrival_poi = poi;

}

vector<int> Bus::getBestSequence() {


	return this->best_sequence;


}

vector<POI> Bus::getOptimalPath() {

	return this->optimal_path;
}


void Bus::setOptimalPath(vector<POI> path) {

	this->optimal_path = path;
}


#endif /*SRC_BUS_H_*/