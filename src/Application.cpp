
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
#include <float.h>
#include <algorithm>
#include "graphviewer.h"


using namespace std;



vector<Passenger*> pending_pass;
vector<Bus*> buses;
vector<vector<Vertex<POI>*>*> pending_routes;

int departure = 0;



#define MAIN_MENU 0
#define MAP_LOADER_SUBMENU 1
#define PASSENGER_LOADER_SUBMENU 2
#define BUS_ADDER_MENU 3


void viewPath(){

	int busId;

	cout << "\nEnter Bus Id: ";

	cin >> busId;

	cout << "\nFinding bus\n";

	Bus* bus = new Bus();
	bool bus_found = false;

	for (int i = 0; i < buses.size(); i++) {

		if (buses.at(i)->getId() == busId) {
			bus = buses.at(i);
			bus_found = true;
		}

	}

	if (!bus_found) {
		cout << "\nBus of id: " << busId << " not found\n";
		return;
	}

	GraphViewer *gv = new GraphViewer(600,600,true);

	gv->setBackground("background.jpg");

		gv->createWindow(600, 600);

		gv->defineEdgeDashed(true);
		gv->defineVertexColor("blue");
		gv->defineEdgeColor("black");



		cout << "BTW" << bus->getOptimalPath().size();

		gv->addNode(bus->getOptimalPath().at(0).getId());

		for(int i=1; i < bus->getOptimalPath().size();i++){


			cout << "\nID: " << bus->getOptimalPath().at(i).getId();
			gv->addNode(bus->getOptimalPath().at(i).getId());

			gv->addEdge(i,bus->getOptimalPath().at(i-1).getId(), bus->getOptimalPath().at(i).getId(), EdgeType::UNDIRECTED);


		}


}


void findFastPath(Bus* bus, Graph<POI>* map) {

	vector<POI> totalPath;


	for (int i = 1; i < bus->getBestSequence().size(); i++) {

		POI poi1(bus->getBestSequence().at(i-1));
		POI poi2(bus->getBestSequence().at(i));


		cout << "\nUsing dijkstra to analyze graph\n";

		map->dijkstraShortestPath(*map->findVertex(poi1)->getInfo());

		vector<POI> temp_path;

		cout << "\nGetting path between points\n";

		temp_path = map->getPath(poi1, poi2);


		cout << "\nConcatenating paths\n";



		totalPath.insert(totalPath.end(), temp_path.begin()+1, temp_path.end());

	}
	
	bus->setOptimalPath(totalPath);


}

double poiDistance(POI x, POI y) {

	double x1 = y.getX();
	double y1 = y.getY();
	double y2 = x.getY();
	double x2 = x.getX();
/*
	cout << "\nDistancia info:\n";

	cout << "X1: " << x1 << endl;
	cout << "Y1: " << y1 << endl;
	cout << "X2: " << x2 << endl;
	cout << "Y2: " << y2 << endl;
	cout << "Distancia: " << sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0) << endl;*/
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);


}

void display(int a[], int n)
{
	cout << "Uno: ";
	for (int i = 0; i < n; i++) {
		cout << "aqui:" << a[i] << "  ";
	}
	cout << endl;
}

vector<vector<int>> findPermutations(int a[], int n)
{
	vector<vector<int>> possibilities;



	int index = 0;

	sort(a, a + n);

	do {

		possibilities.push_back(*new vector<int>);
		for (int i = 0; i < n; i++) {
			possibilities.at(index).push_back(a[i]);
		}
		index++;

	} while (next_permutation(a, a + n));

	return possibilities;
}

void getBestSequence(Bus* bus, Graph<POI> *map) {

	cout << "\nGetting all points...\n";


	int nr_of_poi = bus->getRoute().size();

	int* array = new int[nr_of_poi];

	for (int i = 0; i < nr_of_poi; i++){

		array[i] = bus->getRoute().at(i)->getInfo()->getId();

	}


	cout << "\nFinding all sequences of points...\n";


	vector<vector<int>> possibilities;
	possibilities = findPermutations(array, nr_of_poi);

	for (int x = 0; x < possibilities.size(); x++) {

		possibilities.at(x).insert(possibilities.at(x).begin(), bus->getDeparturePOI()->getInfo()->getId());
		possibilities.at(x).push_back(bus->getArrivalPOI()->getInfo()->getId());

	}
	

	/*for (int i = 0; i < possibilities.size(); i++) {

		cout << "\nPermutations at " << i << endl;

		for (int j = 0; j < possibilities.at(i).size(); j++) {

			cout << possibilities.at(i).at(j) << " ";


		}

		cout << endl;

	}*/


	cout << "\nFinding best sequence...\n";

	double shortest_distance = DBL_MAX;
	double current_distance = 0;
	vector<int> best_sequence;


	//cout << "        Distance: " << current_distance << endl;

	//Sequencia a sequencia
	for (int i = 0; i < possibilities.size(); i++) {

		//cout << "\nTesting sequence number: "<< i << " \n";

		//cout << "Best Distance: " << shortest_distance << endl;

		//elemento da sequencia a elemento da sequecnia
		for (int j = 1; j < possibilities.at(i).size(); j++) {


			//cout << "\n       Testing element number: " << j << " \n";


			POI poi2(possibilities.at(i).at(j - 1));

			POI poi1(possibilities.at(i).at(j));



			//cout << "\n        Updating distance\n";

			//cout << "        Distance: " << poiDistance(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo()) << endl;

			current_distance += poiDistance(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo());

			//cout << "        Distance: " << current_distance << endl;
		}

		if (current_distance < shortest_distance) {
			shortest_distance = current_distance;
			best_sequence = possibilities.at(i);
		}

		current_distance = 0;

	}


	cout << "\nShortest distance: " <<  shortest_distance << endl;

	for (int x = 0; x < best_sequence.size(); x++) {

		cout << "Ponto " << x << ": " << best_sequence.at(x) << endl;

	}
	

	bus->setBestSequence(best_sequence);


}

void defineFastPathOfBus(int busId, Graph<POI> *map) {

	cout << "\nFinding bus\n";

	Bus* bus = new Bus();
	bool bus_found = false;

	for (int i = 0; i < buses.size(); i++) {

		if (buses.at(i)->getId() == busId) {
			bus = buses.at(i);
			bus_found = true;
		}

	}

	if (!bus_found) {
		cout << "\nBus of id: " << busId << " not found\n";
		return;
	}

	cout << "\nGetting best sequence\n";

	getBestSequence(bus, map);

	cout << "\nFinding fastest path\n";

	findFastPath(bus, map);
}

void definePathOfBus(int busId, Graph<POI> *map) {

	Bus* bus = new Bus();
	bool bus_found = false;

	for (int i = 0; i < buses.size(); i++) {

		if (buses.at(i)->getId() == busId) {
			bus = buses.at(i);
			bus_found = true;
		}

	}

	if (!bus_found) {
		cout << "\nBus of id: " << busId << " not found\n";
		return;
	}

}

vector<POI> findShort(POI poiD, POI poiA, Graph<POI> *map){
	auto v = map->getPath(poiD, poiA);
	for(unsigned int i = 0; i < v.size(); i++){
		cout << v[i].getId() << " -> ";
	}
	cout << endl;
	return v;
}

void applyDijkstra(Graph<POI> *map){
	
	map->dijkstraShortestPath(POI(departure));
	// stringstream ss;

	// vector<Vertex<POI>* > vs = map->getVertexSet();
	// for(unsigned int i = 0; i < vs.size(); i++) {
	// 	ss << vs[i]->getInfo()->getId() << "<-";
	// 	if ( vs[i]->getPath() != NULL )
	// 		ss << vs[i]->getPath()->getInfo()->getId();
	// 	ss << "|";
	// }
	// cout << endl << endl << ss.str() << endl << endl;
}

void setPoints(Graph<POI>* map) {


	Bus* bus = new Bus();

	int  bus_id;

	cout << "\nEnter bus id: ";

	cin >> bus_id;

	for (int i = 0; i < buses.size(); i++) {

		if (buses.at(i)->getId() == bus_id) {
			bus = buses.at(i);
			break;
		}
	}

	int departure_id;
	int arrival_id;

	cout << "\nEnter Departure Point Id: ";

	cin >> departure_id;

	departure = departure_id;
	applyDijkstra(map);

	POI poi(departure_id);

	bus->setDeparturePOI(map->findVertex(poi));

	cout << "\nEnter Arrival Point Id: ";

	cin >> arrival_id;

	POI poi2(arrival_id);

	bus->setArrivalPOI(map->findVertex(poi2));

}

bool checkNextRouteForID(int id) {


	for (int i = 0; i < pending_routes.at(0)->size(); i++) {


			if (pending_routes.at(0)->at(i)->getInfo()->getId() == id)
				return true;

		
	}
	   
	return false;
}

Bus* getNextUnusedBus() {

	cout << "\nFinding unused bus" << endl;


	for (int i = 0; i < buses.size(); i++) {

		if (!buses.at(i)->isBeingUsed()) {
			return buses.at(i);
			cout << "\nFound a bus" << endl;
		}

	}

	return NULL;
}

void distributeNextRouteToBus() {

	cout << "\nDistributing next route to bus..." << endl;

	cout << "\nMoving route from pending list into bus..." << endl;

	Bus* unusedBus = new Bus();

	unusedBus = getNextUnusedBus();

	unusedBus->setRoute(*pending_routes.at(0));


	pending_routes.erase(pending_routes.begin()); 


	cout << "\nRoute has been moved" << endl;

	for (int j = 0; j < pending_pass.size(); j++) {

		int numberOfCommonNodes = 0;

		for (int x = 0; x < pending_pass.at(j)->getNodes()->size(); x++) {

			if (checkNextRouteForID(pending_pass.at(j)->getNodes()->at(x))) {

				numberOfCommonNodes++;
				cout << "\ncommon node found\n";
			}


		}


		if (numberOfCommonNodes > pending_pass.at(j)->getNodes()->size() * 0) {

			if (j == 0)
				cout << "\nAdding respective passengers to bus..." << endl;

			cout << "\nAdding passenger " << pending_pass.at(j)->getId() <<  endl;
			
			if (unusedBus->full()) {

				unusedBus = new Bus();

				unusedBus = getNextUnusedBus();
			}
				
			unusedBus->addPassenger(pending_pass.at(j));
			pending_pass.erase(pending_pass.begin());
		}


	}


	cout << "\nPassangers have been distributed." << endl;


}

void determineInterest(Graph<POI> *map) {

	for (unsigned int i = 0; i < pending_pass.size(); i++) {

		for (unsigned int j = 0; j < pending_pass.at(i)->getNodes()->size(); j++) {

			POI poi1(pending_pass.at(i)->getNodes()->at(j));

			map->findVertex(poi1)->getInfo();

			cout << map->findVertex(poi1)->getInfo()->getInterest();

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

		cout << "\nPending passenger: " << i ;

		for (unsigned int j = 0; j < pending_pass.at(i)->getNodes()->size(); j++) {


			cout << "\nPassenger Node nr: " << j;


			POI poi1(pending_pass.at(i)->getNodes()->at(j));

			if (map->findVertex(poi1)->getInfo()->getInterest() > pending_pass.size() * 0.5) {
				cout << "\nPOI: " << map->findVertex(poi1)->getInfo()->getId() << endl;


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


	int capacity;

	cout << "\nEnter capacity? ";
	cin >> capacity;


	Bus* bus = new Bus(busId, capacity);


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


				if (!map->addEdge(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo(), poiDistance(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo())))
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



	cout << endl << "\nName of Tag file? ";
	cin >> tag_file;
	loadTag(tag_file, map);

	
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
	loadEdges(edge_file, map);

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

			cout << "| 3 - Add bus\n";

			cout << "| 4 - Determine what POI's must be visited\n";

			cout << "| 5 - Allocate people to buses\n";

			cout << "| 6 - Set Departure and Arrival points\n";

			cout <<"| 7 - Define fastest path for bus\n";

			cout << "| 8 - Define fastest path for bus (faster but less precise)\n";

			cout << "| 9 - View Path\n";

			cout << "| 10 - Exit\n";

			cout << "|_\n\nEnter one of the options above: ";



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

			else if (option == 5) {

				



				distributeNextRouteToBus();

				cout << endl << "BUS id: " << buses.at(0)->getId() << endl;


				buses.at(0)->printpassengers();

			
			}

			else if (option == 6) {

				setPoints(&map);
				/*
				cout << endl << buses.at(0)->getDeparturePOI()->getInfo()->getId() << endl;

				cout << endl << buses.at(0)->getArrivalPOI()->getInfo()->getId() << endl;
				*/

			}

			else if (option == 7) {

				int busId;


				cout << "\nInsert Bus number: ";
				 
				cin >> busId;

				definePathOfBus(busId, &map);


			}
			
			else if (option == 8) {


				/*int busId;


				cout << "\nInsert Bus number: ";

				cin >> busId;

				defineFastPathOfBus(busId, &map);
				*/

				cout << "\nCreated Bus\n";

				Bus* bus = new Bus(1234);

				cout << "\nsetting departure and arrival pois\n";

				POI poi1(111443920);

				POI poi2(480482921);

				bus->setArrivalPOI(map.findVertex(poi2));

				bus->setDeparturePOI(map.findVertex(poi1));
				
				cout << "\Insetting route points\n";

				vector<Vertex<POI>*> route1;

				POI poi3(122528341);
				route1.push_back(map.findVertex(poi3));

				POI poi4(311887518);
				route1.push_back(map.findVertex(poi4));

				POI poi5(311887521);
				route1.push_back(map.findVertex(poi5));

				POI poi6(428208843);
				route1.push_back(map.findVertex(poi6));


				bus->setRoute(route1);

				buses.push_back(bus);

				cout << "\nDefining path of bus\n";


				defineFastPathOfBus(1234, &map);

				/*for (int i = 0; i < bus->getOptimalPath().size(); i++) {

					cout << "Path node nr: " << i << " " << bus->getOptimalPath().at(i).getId() << endl;
					

				}*/


				viewPath();

			}

			else if(option == 9){


				viewPath();


			}

			else if(option == 10){
				break;
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
