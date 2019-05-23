
#ifndef SRC_POI_H_
#define SRC_POI_H_

#include <vector>
#include <string>
#include "Graph.h"


using namespace std;

class POI {
	int id;
	double x;
	double y;
	int people_interested;


	bool information;
	bool hotel;
	bool attraction;
	bool viewpoint;
	bool guest;
	bool picnic;
	bool artwork;
	bool camp;
	bool museum;
	bool ast;

public:

	POI();

	POI(int id);

	POI(int id, double x, double y);

	bool operator==(POI rhs) {

		return this->id == rhs.getId();

	}
	bool operator==(POI& rhs) {

		return this->id == rhs.getId();

	}
	bool operator!=(POI& rhs) {

		return this->id != rhs.getId();

	}
	double getX();
	double getY();
	int getId();

	void enableInformation();
	void enableHotel();
	void enableAttraction();
	void enableViewpoint();
	void enableGuest();
	void enableArtwork();
	void enablePicnic();
	void enableCamp();
	void enableMuseum();
	void enableAst();
	string getAmmenities();
	bool isInfo();

	void displayAllInfo();

	void addInterested();


	int getInterest();

};


POI::POI() {

	this->information = false;
	this->hotel = false;
	this->attraction = false;
	this->viewpoint = false;
	this->guest = false;
	this->picnic = false;
	this->artwork = false;
	this->camp = false;
	this->museum = false;
	this->ast = false;
	this->people_interested = 0;
};

POI::POI(int id) {


	this->people_interested = 0;

	this->id = id;
	this->information = false;
	this->hotel = false;
	this->attraction = false;
	this->viewpoint = false;
	this->guest = false;
	this->picnic = false;
	this->artwork = false;
	this->camp = false;
	this->museum = false;
	this->ast = false;
};

POI::POI(int id, double x, double y) {
	this->people_interested = 0;



	this->id = id;
	this->x = x;
	this->y = y;
	this->information = false;
	this->hotel = false;
	this->attraction = false;
	this->viewpoint = false;
	this->guest = false;
	this->picnic = false;
	this->artwork = false;
	this->camp = false;
	this->museum = false;
	this->ast = false;
}


bool POI::isInfo() {

	return information;
}


int POI::getId() {

	return this->id;
}




void POI::enableInformation() {
	
	/*
	if (isInfo())
		cout << "YUP indeed" << endl;
	else
		cout << "nope sorry m8" << endl;
		*/
	information = true;
	/*cout << "POI: " << id << " is true." << endl;
	

	if (isInfo())
		cout << "YUP indeed" << endl;
	else
		cout << "nope sorry m8\n" << endl;*/
}

void POI::enableHotel() {

	this->hotel = true;
}

void POI::enableAttraction() {

	this->attraction = true;
}

void POI::enableViewpoint() {

	this->viewpoint = true;
}

void POI::enableGuest() {

	this->guest = true;
}

void POI::enablePicnic() {

	this->picnic = true;
}

void POI::enableArtwork() {

	this->artwork = true;
}

void POI::enableCamp() {

	this->camp = true;
}


void POI::enableMuseum() {

	this->museum = true;
}

void POI::enableAst() {

	this->ast = true;
}


double POI::getX() {

	return this->x;
}


double POI::getY() {

	return this->y;
}

//for testing purposes

string POI::getAmmenities() {
	string ret = "Vazio: ";

	if (!information)
		ret += "no info";

	if (artwork)
		ret += "artwork";

	if (guest)
		ret += " guest";

	if (viewpoint)
		ret += " view";

	if (picnic)
		ret += " picnic";

	if (museum)
		ret += " museum";

	if (ast)
		ret += " *";

	if (information)
		ret += " info";

	return ret;

}

void POI::displayAllInfo() {

	cout << "\n\nINFO of Vertex:\n";

	cout << "ID: "<<  this->id << endl;

	cout << "X coord: " << this->x << endl;

	cout << "Y coord: " << setprecision(10) << this->y << endl;

	cout << "People Interested: " << this->people_interested << endl;

	cout << "Information: ";

	if (information)
		cout << "true\n";
	else cout << "false\n";


	cout << "Artwork: ";

	if (artwork)
		cout << "true\n";
	else cout << "false\n";


	cout << "Museum: ";

	if (museum)
		cout << "true\n";
	else cout << "false\n";



	cout << endl;

}

void POI::addInterested() {

	cout << "\n incrementing \n";
	people_interested++;

	cout << "\n incremented \n";

}

int POI::getInterest() {

	return this->people_interested;

}




#endif /* SRC_POI_H_ */
