
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
#include "Bus.h"
#include "Passenger.h"
#include "POI.h"
#include <cctype>


using namespace std;


/*
Next step is to go trough all the pois in the passengers lists, and make sure more than half
the passengers have a poi, if so had it to a list , then that is a list that has to be used for the route creation
*/

vector<Passenger> passengers;
vector<Bus> buses;



#define MAIN_MENU 0
#define MAP_LOADER_SUBMENU 1
#define PASSENGER_LOADER_SUBMENU 2


string parseId(string line) {

	int element = 0;
	string ret;

	for (unsigned int i = 0; i < line.length(); i++) {

		if (isdigit(line.at(i))) {
			ret.push_back(line[i]);
		}

	}

	cout << "HERE BITCH " <<ret << endl;

	return ret;
}

int loadPassengers() {

	string passenger_file;

	cout << endl << "Name of Passenger file? ";
	cin >> passenger_file;

	string r_content;
	fstream infile;
	infile.open(passenger_file + ".txt");

	if (!infile)
	{
		cout << "\nError reading Passenger file!\n";
		return 1;
	}
	else
	{
		cout << "\nReading from Passenger file...\n";

		bool first_line = true;

		Passenger pass;

		while (getline(infile, r_content)) {

			if (r_content[0] == 'i') {

				if (!first_line)
					passengers.push_back(pass);
				else
					first_line = false;

				pass.setId(stoi(parseId(r_content)));
			}

			else {
				pass.addNode(stoi(r_content));
			}


		}

	}
	/*
	if (!passengers.empty()) {
		cout << "NOT EMPTY: ";
		passengers.at(0).printNodes();
	}*/


	return 0;

}

int loadTag(string file_name, Graph<POI> *map) {

	string r_content;
	fstream infile;
	infile.open(file_name + ".txt");
	if (!infile)
	{
		cout << "\nError reading Tag file!";
		return 1;
	}
	else
	{
		cout << "\nReading from Tag file...\n";

		int bota = 200;

		string tag = "Vazio ";
		int tag_num = 0;

		while (getline(infile, r_content)) {




			if (tag_num > 0) {



				POI poi1(stoi(r_content));

				/*
				POI poi(497922579);
				cout << "HEREEEEEE " << map->findVertex(poi)->getInfo().getAmmenities() << endl;*/

				if (tag == "tourism=information") {

					//cout << "\nsetting poi1 info to true \n";

					//cout << "\nHEREEEEEErrrr " << map->findVertex(poi1)->getInfo()->isInfo() << endl;
					map->findVertex(poi1)->getInfo()->enableInformation();
					
					map->findVertex(poi1)->getInfo()->enableInformation();
					//cout << "\nHEREEEEEE ";
					/*if(!map->findVertex(poi1)->getInfo()->isInfo())
						cout << "Not here tho" << endl;
					else
						cout << "here too" << endl;
						*/
					//cout << "Vertex id: " << map->findVertex(poi1)->getInfo().getId();

					//cout << "\nHEREEEEEE " << map->findVertex(poi)->getInfo().getAmmenities() << endl;
				}

				else if (tag == "tourism=hotel")
					map->findVertex(poi1)->getInfo()->enableHotel();

				else if (tag == "tourism=attraction")
					map->findVertex(poi1)->getInfo()->enableAttraction();

				else if (tag == "tourism=viewpoint")
					map->findVertex(poi1)->getInfo()->enableViewpoint();

				else if (tag == "tourism=guest_house")
					map->findVertex(poi1)->getInfo()->enableGuest();

				else if (tag == "tourism=picnic_site")
					map->findVertex(poi1)->getInfo()->enablePicnic();

				else if (tag == "tourism=artwork")
					map->findVertex(poi1)->getInfo()->enableArtwork();

				else if (tag == "tourism=camp_site")
					map->findVertex(poi1)->getInfo()->enableCamp();

				else if (tag == "tourism=museum")
					map->findVertex(poi1)->getInfo()->enableMuseum();

				else if (tag == "tourism=*")
					map->findVertex(poi1)->getInfo()->enableAst();


				tag_num--;

				if (tag_num == 0)
					tag = "Vazio ";
			}


			if (tag_num == 0 && tag != "Vazio ") {

				tag_num = stoi(r_content);

			}

			if (r_content == "tourism=information") {

				//cout << "HERE info\n";
				tag = "tourism=information";
				//cout << "Tag set to: " << tag << endl;
			}
			else if (r_content == "tourism=hotel") {

				tag = "tourism=hotel";
			}
			else if (r_content == "tourism=attraction") {

				tag = "tourism=attraction";
			}
			else if (r_content == "tourism=viewpoint") {

				tag = "tourism=viewpoint";
			}
			else if (r_content == "tourism=guest_house") {

				tag = "tourism=guest_house";
			}
			else if (r_content == "tourism=picnic_site") {

				tag = "tourism=picnic_site";
			}
			else if (r_content == "tourism=artwork") {

				tag = "tourism=artwork";
			}
			else if (r_content == "tourism=camp_site") {

				tag = "tourism=camp_site";
			}
			else if (r_content == "tourism=museum") {

				tag = "tourism=museum";
			}
			else if (r_content == "tourism=*") {

				tag = "tourism=*";
			}

			

			

		}



		infile.close();
	}
	cout << "\nFinished reading Tags.\n";


	return 0;
}

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

int loadEdges(string file_name, Graph<POI> *map) {

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


			

			POI *poi = map->findVertex(poi1)->getInfo();


			if (!map->addEdge(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo(), distance(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo())))
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
	string tag_file;
	Graph<POI> map;
	
	cout << endl << "Name of Node file? ";
	cin >> node_file;
	loadNodes(node_file, &map);

	if (map.getVertexSet().empty())
		cout << "\nVertex set is empty, loadNodes failed.\n";



	//cout << "\nX: \n" << map.findVertex(poi)->getInfo().getX();



	cout << endl << "\nName of Tag file? ";
	cin >> tag_file;
	loadTag(tag_file, &map);

	
	/*
	POI poi(414957020);

	Vertex<POI> *v = map.findVertex(poi);


	v->getInfo()->displayAllInfo();*/



	//v->getInfo()->enableInformation();

	//v->getInfo()->displayAllInfo();


	/*
	int index = 0;
	while (true) {

		cout << "Amenitiesss of: ";
		string ret = "Esta aqui: ";
		cin >> index;
		POI poi1(index);
		//ret += map.findVertex(poi1)->getInfo()->getAmmenities();
		cout << "\nAmmenitiesss: " << ret << endl << endl;

	}*/

	cout << endl << "\nName of Edge file? ";
	cin >> edge_file;
	loadEdges(edge_file, &map);

	/*
	cout << "PESOOOOOOOOOOOOOOOOO: ";
	Edge<POI> e = map.getVertexSet().at(23)-> getEdgeAt(0);
	cout << "PESOOOOOOOOOOOOOOOOO: " << e.getWeight();*/


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
				cout<<"| 2 - Load Passengers info\n";
			else
				cout<<"| 2 - Reload Passengers info\n";

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

			else if (option == 2)
				Displayed_screen = PASSENGER_LOADER_SUBMENU;
		}

		if(Displayed_screen == MAP_LOADER_SUBMENU){


			cout<<"----------City Sightseeing - Load Map -------------";

			cout << "\n\n\n _\n";

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

		if (Displayed_screen == PASSENGER_LOADER_SUBMENU) {


			cout << "----------City Sightseeing - Load Passenger -------------";

			cout << "\n\n\n _\n";

			cout << "| 1 - Select files\n";

			cout << "| 2 - Back\n";

			cout << "|_\n\nEnter one of the options above: ";

			cin >> option;

			if (option == 1) {

				loadPassengers();



			}




		}


	}




	return 1;


}

#endif /* SRC_APPLICATION_H_ */
