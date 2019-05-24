
#ifndef SRC_APPLICATION_H_
#define SRC_APPLICATION_H_

#include <vector>
#include <string>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <iostream>
//#include <sstream>
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



vector<Passenger*> pending_pass;
vector<Bus*> buses;
vector<vector<Vertex<POI>*>*> pending_routes;



#define MAIN_MENU 0
#define MAP_LOADER_SUBMENU 1
#define PASSENGER_LOADER_SUBMENU 2
#define BUS_ADDER_MENU 3


//Bus* getNextUnusedBus()



/*void distributeNextRouteToBus() {




}*/


void determineInterest(Graph<POI> *map) {

	for (unsigned int i = 0; i < pending_pass.size(); i++) {

		for (unsigned int j = 0; j < pending_pass.at(i)->getNodes()->size(); j++) {

			POI poi1(pending_pass.at(i)->getNodes()->at(j));





			cout << "\n111111111111111111111111\n";
			map->findVertex(poi1)->getInfo();
			cout << "\n22222222222222222222221\n";


			cout << map->findVertex(poi1)->getInfo()->getInterest();


			cout << "\n33333333333333333333\n";

			map->findVertex(poi1)->getInfo()->addInterested();


		}


	}

}





void addNextRoute(Graph<POI> *map) {

	cout << "\nDetermining Interest...\n";


	determineInterest(map);

	


	int nextIndex = 0;


	cout << "\nAccessing route slot...\n";

	for (unsigned int x = 0; x < pending_routes.size(); x++) {

		if (!pending_routes.at(x)->empty())
			nextIndex++;


	}


	cout << "\nDetermining route points...\n";

	for (unsigned int i = 0; i < pending_pass.size(); i++) {


		vector<Vertex<POI>*>* v = new vector<Vertex<POI>*>();

		//cout << "\nPending passenger: " << i ;

		for (unsigned int j = 0; j < pending_pass.at(i)->getNodes()->size(); j++) {


			//cout << "\nPassenger Node nr: " << j;


			POI poi1(pending_pass.at(i)->getNodes()->at(j));

			if (map->findVertex(poi1)->getInfo()->getInterest() > pending_pass.size() * 0.7) {
				//cout << "\nPOI: " << map->findVertex(poi1)->getInfo()->getId() << endl;


				v->push_back(map->findVertex(poi1));


			}


			pending_routes.push_back(v);



			

			cout << "\nchega aqui\n";

		}
		/*
		cout << "\nTESTTTT 1 na variavel local: \n";

		for (unsigned int j = 0; j < v->size(); j++) {

			cout << "Member of route" << v->at(j)->getInfo()->getId() << endl;


		}
		*/


	}


	cout << "\nPOIs determined.\n";




}


void addBus() {

	int busId;

	cout << "\nEnter bus Id? ";
	cin >> busId;


	Bus* bus = new Bus(busId);


	buses.push_back(bus);


	cout << "\n Added bus of Id=" << busId << ".\n";



}

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

		Passenger* pass = new Passenger();

		while (getline(infile, r_content)) {

			if (r_content[0] == 'i') {

				if (!first_line)
					pending_pass.push_back(pass);
				else
					first_line = false;


				pass = new Passenger();
				pass->setId(stoi(parseId(r_content)));
			}

			else {
				pass->addNode(stoi(r_content));
			}

		}

	}
	
	if (!pending_pass.empty()) {
		pending_pass.at(1)->printNodes();

		cout << endl << pending_pass.at(0)->getId() << endl;

		cout << endl << pending_pass.at(1)->getId() << endl;
	}



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

		bool first_line = true;

		while (getline(infile, r_content)) {

			if (first_line)
				first_line = false;
			else {



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
		}


		infile.close();
	}
	cout << "\nFinished reading Tags.\n";



	//determineInterest(map);
	//addNextRoute(map);


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
	bool first_line = true;
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

			if (first_line)
				first_line = false;
			else {

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



void loadX(Graph<POI> *map) {


	addNextRoute(map);




}





void loadMap (Graph<POI> *map){

	string node_file;
	string edge_file;
	string tag_file;
	
	cout << endl << "Name of Node file? ";
	cin >> node_file;
	loadNodes(node_file, map);

	if (map->getVertexSet().empty())
		cout << "\nVertex set is empty, loadNodes failed.\n";



	//cout << "\nX: \n" << map.findVertex(poi)->getInfo().getX();



	//cout << endl << "\nName of Tag file? ";
	//cin >> tag_file;
	//loadTag(tag_file, map);

	
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

	//cout << endl << "\nName of Edge file? ";
	//cin >> edge_file;
	//loadEdges(edge_file, map);

	/*
	cout << "PESOOOOOOOOOOOOOOOOO: ";
	Edge<POI> e = map.getVertexSet().at(23)-> getEdgeAt(0);
	cout << "PESOOOOOOOOOOOOOOOOO: " << e.getWeight();*/


}


int main(){


	int option;

	bool map_loaded = false;
	bool POI_loaded = false;
	bool PassList_loaded = false;


	Graph<POI> map;



	while(true){




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

			cout<<"| 3 - Add bus\n";

			cout<<"| 4 - Determine what POI's must be visited\n";

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

			else if (option == 3)
				Displayed_screen = BUS_ADDER_MENU;

			//OPTION 4 route adder

			else if (option == 4) {


				addNextRoute(&map);

				/*
				cout << "\nTESTTTT 2 na variavel global: \n";

				for (unsigned int j = 0; j < pending_routes.at(0)->size(); j++) {

					cout << "Member of route" << pending_routes.at(0)->at(j)->getInfo()->getId() << endl;


				}
				cout << "\nPOIs determined.\n";*/


			}

		}

		if(Displayed_screen == MAP_LOADER_SUBMENU){


			cout<<"----------City Sightseeing - Load Map -------------";

			cout << "\n\n\n _\n";

			cout<<"| 1 - Select files\n";

			cout<<"| 2 - Back\n";

			cout<<"|_\n\nEnter one of the options above: ";

			cin>> option;

			if (option == 1) {
	
				loadMap(&map);


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

		if (Displayed_screen == BUS_ADDER_MENU) {


			cout << "----------City Sightseeing - Add Bus -------------";

			cout << "\n\n\n _\n";

			cout << "| 1 - Enter Info\n";

			cout << "| 2 - Back\n";

			cout << "|_\n\nEnter one of the options above: ";

			cin >> option;

			if (option == 1)
				addBus();


			cout << "BUS: " << buses.at(0)->getId() << endl;


			


		}

		

	}




	return 1;


}

#endif /* SRC_APPLICATION_H_ */
