//
// assignment4.h  (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
#include <list>
#include <vector>
#include <iterator>
#include <map>
#include <functional>
#include <limits>
#include "AdjacencyListDirectedGraph.h"
#include "FlightMap.h"



/*
* Calculate the total distance of a route, which is a list of airport names
* including both the origin and the destination.
* Throw an exception if any airport in the route does not exist.
* Throw an exception if some edges on the route do not exist.
*
* route - a route
* Return the total distance of the route
*/
double FlightMap::calcRouteDistance(const list<string> route) {
	if (route.size() < 2) { throw runtime_error("Route does not exist"); }
	
	vertex v;
	list<string> croute = route;
	vector<string> copy_route;
	for (int i=0; i<route.size(); ++i) {
		copy_route.push_back(croute.front());
		croute.pop_front();
	}

	int s = (this->flight_graph).vertices().size();
	vector<double> dist(s, INT_MAX);
	vector<int> parent(s, -1);
	VList vlist = (this->flight_graph).vertices();

	Dijkstra(copy_route[0], dist, parent);
	findAirport(v, copy_route[copy_route.size() - 1]);
	

	double tdist = dist[distance(vlist.begin(), find(vlist.begin(), vlist.end(), v))];

	if (tdist == INT_MAX) { throw runtime_error("Origin to destination is not reachable"); }

	return tdist;

}


/*
* Find a route between two airports. The route must be
* a simple path that contains no cycle. The route does not have
* to be the shortest route. If there is no route connecting
* the airports, return an empty list.
* Throw an exception if some of the given airports does not exist.
*
* airport1 - the name of an airport at the origin
* airport2 - the name of an airport at the destination
* Return a route connecting airport1 to airport2; return an empty list
* if no route exists.
*/
list<string> FlightMap::findRoute(const string &airport1, const string &airport2) {
	list<string> tmp = findShortestRoute(airport1, airport2);
	return tmp;
}

/*
* Find the set of all airports reachable from an airport (i.e.,
* all airports that have routes to connect from the given airport to them).
* The set should *exclude* the given airport.
* Throw an exception if the airport do not exist.
*
* airport - the name of an airport
* Return a set of all reachable airport (in any order).
*/
list<string> FlightMap::findReachableAirports(const string &airport) {
	bool chk;
	vertex v;
	FlightMap::FlightGraph::EdgeList outedge;
	list<string> adjlist;
	chk = findAirport(v, airport);
	if(!chk) { throw runtime_error("Airport does not exist"); }
	outedge = v.outgoingEdges();
	for (FlightMap::FlightGraph::EdgeItor iter = outedge.begin(); iter != outedge.end(); ++iter) {
		adjlist.push_back( *((*iter).dest()) );
	}

	return adjlist;

}

/*
* Find the shortest route between two airports.  If there exist
* more than one shortest routes, return any one of them.
* If there is no route connecting the airports, return an empty list.
* Throw an exception if some of the given airports does not exist.
*
* airport1 - the name of an airport at the origin
* airport2 - the name of an airport at the destination
* Return the shortest route connecting airport1 to airport2;
* return an empty list if no route exists.
*/
list<string> FlightMap::findShortestRoute(const string &airport1, const string &airport2) {
	vertex u, v;
	bool chk;
	list<string> route;

	chk = findAirport(u, airport1);
	if (!chk) { throw runtime_error("Airport does not exist"); }
	chk = findAirport(v, airport2);
	if (!chk) { throw runtime_error("Airport does not exist"); }

	VList vlist = (this->flight_graph).vertices();
	vector<vertex> copy_list;
    for(VItor iter = vlist.begin() ; iter != vlist.end() ; ++iter){
        copy_list.push_back(*iter);
    }
	
	int s = (this->flight_graph).vertices().size();
	vector<double> dist(s, INT_MAX);
	vector<int> parent(s, -1);

	Dijkstra(airport1, dist, parent);

	int dist_origin = distance(vlist.begin(), find(vlist.begin(), vlist.end(), u));

	if (dist[distance(vlist.begin(), find(vlist.begin(), vlist.end(), v))] == INT_MAX) return route;

	while ( 1 ) {
		int dist_dest = distance(vlist.begin(), find(vlist.begin(), vlist.end(), v));
		if (dist_origin == dist_dest) {
			route.push_front(*v);
			break;
		}
		route.push_front(*v);
		v = copy_list[parent[dist_dest]];
	}
	
	return route;
}

/*
* Print all shortest routes to all airports reachable from a given airport
* between two airports. This function should print one route per line to
* stdout using printRoute(). At the end of each line, print
* the distance of the route in the format "(Distance = XXX)",
* where XXX is the distance returned by calcRouteDistance().
* If there exist more than o*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_pos*e.e_obj.origin_inc_edges_posne shortest routes of an airport, print any one of them.
* If there is no route to any other airport, just print nothing.
* Do not print anything for unreachable airport.
* Do not print the route to the given airport *itself*.
* Throw an exception if the given airport do not exist.
*
* airport - the name of an airport
*/
void FlightMap::printAllShortestRoutes(const string &airport) {
	VList vlist = (this->flight_graph).vertices();
	vertex u;

	bool chk;
	chk = findAirport(u, airport);
	if (!chk) { throw runtime_error("Airport does not exist"); }

	for (VItor iter = vlist.begin(); iter != vlist.end(); ++iter) {
		if (*(*iter) != airport) {
			list<string> route = findShortestRoute(airport, *(*iter));
			cout << "  ";
			printRoute(route);
			cout << "  (Distance = " << calcRouteDistance(route) << ")" << endl;
		}
	}

}



void FlightMap::Dijkstra(const string& airport, vector<double> &dist, vector<int>& parent) {
	//typedef pair<double, FlightMap::FlightGraph::Vertex> Pair;
	VList vlist = (this->flight_graph).vertices();
	vertex src;
	VItor viter;

	bool chk = findAirport(src, airport);
	if (!chk) { throw runtime_error("Airport does not exist"); }

	
	viter = find(vlist.begin(), vlist.end(), src);
	dist[distance(vlist.begin(), viter)] = 0;
	parent[distance(vlist.begin(), viter)] = -1;

	vertex_pq v_pq;
	v_pq.push(make_pair(0, *src));

	while (!v_pq.empty()) {
		double cost = v_pq.top().first;
		string here = v_pq.top().second;
		vertex v_here; findAirport(v_here, here);
		v_pq.pop();

		if (dist[distance(vlist.begin(), find(vlist.begin(), vlist.end(), v_here))] < cost) continue;
		EList inc = v_here.incidentEdges();
		for (FlightMap::FlightGraph::EdgeItor iter = inc.begin(); iter != inc.end(); ++iter) {
			vertex there = (*iter).dest();
			VItor there_itor = find(vlist.begin(), vlist.end(), there);
			double nextDist = cost + *(*iter);

			if (dist[distance(vlist.begin(), there_itor)] > nextDist) {
				dist[distance(vlist.begin(), there_itor)] = nextDist;
				parent[distance(vlist.begin(), there_itor)] = distance(vlist.begin(), find(vlist.begin(), vlist.end(), v_here));
				v_pq.push(make_pair(nextDist, *there));
			}
		}
	
	}


	
}
