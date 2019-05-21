
#ifndef SRC_APPLICATION_H_
#define SRC_APPLICATION_H_

#include <vector>
#include <string>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "Graph.h"
#include "POI.h"
#include <cctype>

using namespace std;

#define MAIN_MENU 0
#define MAP_LOADER_SUBMENU 1

double distance(POI x, POI y) {

	double x1 = y.getX();
	double y1 = y.getY();
	double y2 = x.getY();
	double x2 = x.getX();

	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);


}


void parseEdgeline(string line, string ret[3]) {

	int element = 0;

	for (unsigned int i = 0; i < line.length(); i++) {

		if (line[i] == ',')
			element++;

		if (isdigit(line.at(i))) {
			ret[element].push_back(line.at(i));
		}

		//cout << ret[0] << " e " << ret[1] << endl;
	}

}


int loadEdges(string file_name, Graph<POI> map) {

	string r_content;
	fstream infile;
	infile.open(file_name + ".txt");
	if (!infile)
	{
		cout << "\nError reading Edge file!";
		return 1;
	}
	else
	{
		cout << "\nReading from Edge file...\n";

		int j = 1;

		while (getline(infile, r_content)) {

			string ret[2];



			parseEdgeline(r_content, ret);
			//cout << "Sai da nodeline:" << ret[0] << " e " << ret[1] << endl;


			POI poi1(stoi(ret[0]));
			POI poi2(stoi(ret[1]));


			

			POI poi = map.findVertex(poi1)->getInfo();


			if (!map.addEdge(map.findVertex(poi1)->getInfo(), map.findVertex(poi2)->getInfo(), distance(map.findVertex(poi1)->getInfo(), map.findVertex(poi2)->getInfo())))
				cout << "Source or destination vertex doesnt exist";

			//cout << "Sai do stod:" << stoi(ret[0]) << " e " << stod(ret[1]) << " e " << stod(ret[2]) << endl;

			j++;

		}



		infile.close();
	}
	cout << "\nFinished reading Edges.\n";


	return 0;
}

void parseNodeline(string line, string ret[3]) {

	int element = 0;
	
	for (unsigned int i = 0; i < line.length(); i++) {

		if (line[i] == ',')
			element++;

		if (isdigit(line.at(i)) || line[i] == '.') {
				ret[element].push_back(line.at(i));
		}

		//cout << ret[0] << " e " << ret[1] << endl;
	}

}


int loadNodes(string file_name, Graph<POI> *map) {

	string r_content;
	fstream infile;
	infile.open(file_name + ".txt");
	if (!infile)
	{
		cout << "\nError reading Node file!";
		return 1;
	}
	else
	{
		cout << "\nReading from Node file...\n";


		while (getline(infile, r_content)) {


			string ret[3];

			parseNodeline(r_content, ret);
			//cout << "Sai da nodeline:" << ret[0] << " e " << ret[1] << endl;

			POI poi(stoi(ret[0]),stod(ret[1]), stod(ret[2]));
			if (!map->addVertex(poi))
				cout << "Vertex already exists.\n";
			//cout << "Sai do stod:" << stoi(ret[0]) << " e " << stod(ret[1]) << " e " << stod(ret[2]) << endl;
	

			if (map->getVertexSet().empty())
				cout << "\nvertex set is empty\n";
		}



		infile.close();


	}
	cout << "\nFinished reading nodes.\n";


	return 0;
}


void loadMap (){


	string node_file;
	string edge_file;
	Graph<POI> map;
	
	cout << endl << "Name of Node file? ";
	cin >> node_file;
	loadNodes(node_file, &map);


	if (map.getVertexSet().empty())
		cout << "\nVertex set is empty, loadNodes failed.\n";

	cout << endl << "\nName of Edge file? ";
	cin >> edge_file;
	loadEdges(edge_file, map);


	

}





int main(){
	while(true){



		int option;

		bool map_loaded = false;
		bool POI_loaded = false;
		bool PassList_loaded = false;
		int Displayed_screen = MAIN_MENU;


		if(Displayed_screen == MAIN_MENU){
			cout<<"----------City Sightseeing - Main Menu -------------";

			if(map_loaded)
				cout << "Map Loaded";

			if(POI_loaded)
				cout << "POI's Loaded";

			if(PassList_loaded)
				cout << "Passenger list Loaded";

			cout << "\n\n _\n";


			if(!map_loaded)
				cout<<"| 1 - Load Map\n";
			else
				cout<<"| 1 - Reload Map\n";


			if(!POI_loaded)
				cout<<"| 2 - Load POI's\n";
			else
				cout<<"| 2 - Reload POI's\n";

			if(!PassList_loaded)
				cout<<"| 3 - Load Passenger list w/ respective POI's\n";
			else
				cout<<"| 3 - Reload  Passenger list w/ respective POI's\n";


			cout<<"| 4 - View Map\n";

			cout<<"| 4 - View Accessible POI's\n";

			cout<<"| 5 - Sort Passengers\n";

			cout<<"| 6 - Trace Optimal Route\n";

			cout<<"| 7 - Exit\n";

			cout<<"|_\n\nEnter one of the options above: ";

			cin>> option;

			if(option ==1)
				Displayed_screen = MAP_LOADER_SUBMENU;
		}

		if(Displayed_screen == MAP_LOADER_SUBMENU){


			cout<<"----------City Sightseeing - Load Map -------------";

			cout << "2\n\n\n _\n";

			cout<<"| 1 - Select files\n";

			cout<<"| 2 - Back\n";

			cout<<"|_\n\nEnter one of the options above: ";

			cin>> option;

			if (option == 1) {
	
				loadMap();


				/*string ret[2];
				parseNodeline("(12345,1234.234)", ret);*/


			}
				



		}


	}




	return 1;


}

#endif /* SRC_APPLICATION_H_ */
