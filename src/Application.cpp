
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
//#include "graphviewer.h"


using namespace std;



vector<Passenger*> pending_pass;
vector<Bus*> buses;
vector<vector<Vertex<POI>*>*> pending_routes;

double poi_perc = 0.5;
double pass_perc = 0.5;

int departure = 0;



#define MAIN_MENU 0
#define MAP_LOADER_SUBMENU 1
#define PASSENGER_LOADER_SUBMENU 2
#define BUS_ADDER_MENU 3


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

double poiDistanceDijkstra(POI poi1, POI poi2, Graph<POI>* map) {

	int res;

	map->dijkstraShortestPath(poi1);


	res = map->findVertex(poi2)->getDist();


	return res;
}

void getBestSequenceDijkstra(Bus* bus, Graph<POI> *map) {

	cout << "\nGetting all points...\n";


	int nr_of_poi = bus->getRoute().size();

	int* array = new int[nr_of_poi];

	for (int i = 0; i < nr_of_poi; i++) {

		array[i] = bus->getRoute().at(i)->getInfo()->getId();

	}


	cout << "\nFinding all sequences of points...\n";


	vector<vector<int>> possibilities;
	possibilities = findPermutations(array, nr_of_poi);

	for (int x = 0; x < possibilities.size(); x++) {

		possibilities.at(x).insert(possibilities.at(x).begin(), bus->getDeparturePOI()->getInfo()->getId());
		possibilities.at(x).push_back(bus->getArrivalPOI()->getInfo()->getId());

	}





	cout << "\nFinding best sequence...\n";

	double shortest_distance = DBL_MAX;
	double current_distance = 0;
	vector<int> best_sequence;



	//Sequencia a sequencia
	for (int i = 0; i < possibilities.size(); i++) {


		//elemento da sequencia a elemento da sequecnia
		for (int j = 1; j < possibilities.at(i).size(); j++) {




			POI poi2(possibilities.at(i).at(j - 1));

			POI poi1(possibilities.at(i).at(j));


			current_distance += poiDistanceDijkstra(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo(), map);

		}

		if (current_distance < shortest_distance) {
			shortest_distance = current_distance;
			best_sequence = possibilities.at(i);
		}

		current_distance = 0;

	}


	cout << "\nShortest distance: " << shortest_distance << endl;



	bus->setBestSequence(best_sequence);


}

void findSlowPath(Bus* bus, Graph<POI>* map) {

	vector<POI> totalPath;



	cout << "\nUsing dijkstra to analyze graph\n";

	for (int i = 1; i < bus->getBestSequence().size(); i++) {

		POI poi1(bus->getBestSequence().at(i - 1));
		POI poi2(bus->getBestSequence().at(i));



		map->dijkstraShortestPath(*map->findVertex(poi1)->getInfo());

		vector<POI> temp_path;


		temp_path = map->getPath(poi1, poi2);





		totalPath.insert(totalPath.end(), temp_path.begin() + 1, temp_path.end());

	}

	bus->setOptimalPath(totalPath);


}


void defineSlowPathOfBus(int busId, Graph<POI> *map) {

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


	cout << "\nFinding fastest path\n";

	getBestSequenceDijkstra(bus, map);

	findSlowPath(bus, map);
}


void viewPath(){
	/*
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

		*/
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

	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);

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
	



	cout << "\nFinding best sequence...\n";

	double shortest_distance = DBL_MAX;
	double current_distance = 0;

	double real_distance = 0;
	double cur_real_distance = 0;
	vector<int> best_sequence;



	//Sequencia a sequencia
	for (int i = 0; i < possibilities.size(); i++) {


		//elemento da sequencia a elemento da sequecnia
		for (int j = 1; j < possibilities.at(i).size(); j++) {

					   
			POI poi2(possibilities.at(i).at(j - 1));

			POI poi1(possibilities.at(i).at(j));



			current_distance += poiDistance(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo());
			real_distance += poiDistanceDijkstra(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo(),map);


		}

		if (current_distance < shortest_distance) {
			shortest_distance = current_distance;
			real_distance = cur_real_distance;
			best_sequence = possibilities.at(i);
		}

		current_distance = 0;
		cur_real_distance = 0;

	}


	cout << "\nShortest distance: " <<  shortest_distance << endl;

	cout << "\nReal distance: " << real_distance << endl;


	

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
			}


		}


		if (numberOfCommonNodes > pending_pass.at(j)->getNodes()->size() * pass_perc) {

			if (j == 0)
				cout << "\nAdding respective passengers to bus..." << endl;

			
			if (unusedBus->full()) {

				unusedBus = new Bus();

				unusedBus = getNextUnusedBus();
			}
				
			unusedBus->addPassenger(pending_pass.at(j));
			pending_pass.erase(pending_pass.begin());
		}


	}


	cout << "\nPassengers have been distributed." << endl;


}

void determineInterest(Graph<POI> *map) {

	for (unsigned int i = 0; i < pending_pass.size(); i++) {

		for (unsigned int j = 0; j < pending_pass.at(i)->getNodes()->size(); j++) {

			POI poi1(pending_pass.at(i)->getNodes()->at(j));

			map->findVertex(poi1)->getInfo();


			map->findVertex(poi1)->getInfo()->addInterested();

		}


	}

}

void eraseLooseEnds(vector<Vertex<POI>*>* v, Graph<POI> *map) {


	for (int i = 0; i < v->size(); i++) {

		map->dijkstraShortestPath(*v->at(i)->getInfo());
		
		for (int j = 0; j < v->size(); j++) {
			
			if (i != j) {
				
				if (v->at(j)->getPath() == NULL)
					v->erase(v->begin() + j);


			}
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


		for (unsigned int j = 0; j < pending_pass.at(i)->getNodes()->size(); j++) {




			POI poi1(pending_pass.at(i)->getNodes()->at(j));

			if (map->findVertex(poi1)->getInfo()->getInterest() > pending_pass.size() * poi_perc) {
				


				v->push_back(map->findVertex(poi1));


			}

			

			eraseLooseEnds(v, map);


			pending_routes.push_back(v);



			

		}

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


	cout << "\nAdded bus of Id=" << busId << ".\n\n";



}

string parseId(string line) {

	int element = 0;
	string ret;

	for (unsigned int i = 0; i < line.length(); i++) {

		if (isdigit(line.at(i))) {
			ret.push_back(line[i]);
		}

	}


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
	
	

	cout << "\nFinished reading passenger file. \n";

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


					if (tag == "tourism=information") {
						map->findVertex(poi1)->getInfo()->enableInformation();

						map->findVertex(poi1)->getInfo()->enableInformation();
						
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

					tag = "tourism=information";
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


				POI poi1(stoi(ret[0]));
				POI poi2(stoi(ret[1]));




				POI *poi = map->findVertex(poi1)->getInfo();


				if (!map->addEdge(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo(), poiDistance(*map->findVertex(poi1)->getInfo(), *map->findVertex(poi2)->getInfo())))
					cout << "Source or destination vertex doesnt exist";


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

			POI poi(stoi(ret[0]),stod(ret[1]), stod(ret[2]));
			if (!map->addVertex(poi))
				cout << "Vertex already exists.\n";
	

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






	cout << endl << "\nName of Tag file? ";
	cin >> tag_file;
	loadTag(tag_file, map);

	
	

	cout << endl << "\nName of Edge file? ";
	cin >> edge_file;
	loadEdges(edge_file, map);


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

			cout << "| 10 - Define Choice variables\n";

			cout << "| 11 - Exit\n";

			cout << "|_\n\nEnter one of the options above: ";



			cin>> option;

			if(option ==1)
				Displayed_screen = MAP_LOADER_SUBMENU;

			else if (option == 2)
				Displayed_screen = PASSENGER_LOADER_SUBMENU;

			else if (option == 3)
				Displayed_screen = BUS_ADDER_MENU;


			else if (option == 4) {

				addNextRoute(&map);

			}

			else if (option == 5) {

				distributeNextRouteToBus();

				cout << endl << "BUS id: " << buses.at(0)->getId() << endl;


				buses.at(0)->printpassengers();

			
			}

			else if (option == 6) {

				setPoints(&map);
			}

			else if (option == 7) {


				int busId;


				cout << "\nInsert Bus number: ";

				cin >> busId;

				defineSlowPathOfBus(busId, &map);
							
				for (int i = 0; i < buses.at(0)->getOptimalPath().size(); i++) {

					cout << "Path node nr: " << i << " " << buses.at(0)->getOptimalPath().at(i).getId() << endl;


				}

			}
			
			else if (option == 8) {
			

				int busId;


				cout << "\nInsert Bus number: ";

				cin >> busId;

				defineFastPathOfBus(busId, &map);
				
				for (int i = 0; i < buses.at(0)->getOptimalPath().size(); i++) {

					cout << "Path node nr: " << i << " " << buses.at(0)->getOptimalPath().at(i).getId() << endl;
					

				}


			}

			else if (option == 9) {

				viewPath();

			}

			else if (option == 10) {


			cout << "\nWhat percentage (in decimal) of common nodes must a passenger and the route of a \nbus have so that the passenger gets put into that bus? ";
			cin >> pass_perc;

			cout << "\n\nWhat percentage (in decimal) of passengers must want to visit a node so that the \nnode gets added to the route of the next bus? ";
			cin >> poi_perc;


			}

			else if(option == 11){
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



			


		}

		

	}




	return 1;


}

#endif /* SRC_APPLICATION_H_ */
