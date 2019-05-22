
#ifndef SRC_POI_H_
#define SRC_POI_H_

#include <vector>
#include <string>
#include "Graph.h"


using namespace std;

class POI {
	int x;
	int y;
public:
	POI(int x, int y);
	bool operator==(POI& rhs) {

		return this->x == rhs.getX();

	}
	int getX();
	int getY();
};


POI::POI(int x, int y) {

	this->x = x;
	this->y = y;
}

int POI::getX() {

	return this->x;
}


int POI::getY() {

	return this->y;
}






#endif /* SRC_POI_H_ */
