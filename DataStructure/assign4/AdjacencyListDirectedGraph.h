/*
20161248 JEON WOONGBAE
wbjeon2k@gmail.com
*/

//
// AdjacencyListDirectedGraph.h  (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#ifndef ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H
#define ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H

#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

template<typename V, typename E>
class AdjacencyListDirectedGraph {

  // ---------------------------------------------------------------------------------
  // You *cannot* add any additional public or private member functions in this class.
  // You *cannot* add any additional public or private member variables in this class.
  // ---------------------------------------------------------------------------------

public:

  // Define public data types of Vertex and Edge and the associated iterators.

  class Vertex;
  class Edge;

  typedef list<Vertex> VertexList;
  typedef list<Edge> EdgeList;
  typedef typename VertexList::iterator VertexItor;
  typedef typename EdgeList::iterator EdgeItor;
  typedef typename VertexList::const_iterator VertexConstItor;
  typedef typename EdgeList::const_iterator EdgeConstItor;

private:

  // Define private data types of VertexObject and EdgeObject and the associated iterators.
  // The type of IncidenceEdgesList and its iterator are defined as well.

  struct VertexObject;
  struct EdgeObject;

  typedef list<VertexObject> VertexObjectList;
  typedef list<EdgeObject> EdgeObjectList;
  typedef list<EdgeList> IncidenceEdgesList;

  typedef typename VertexObjectList::iterator VertexObjectItor;
  typedef typename EdgeObjectList::iterator EdgeObjectItor;
  typedef typename IncidenceEdgesList::iterator IncidenceEdgesItor;

  /*
   * VertexObject stores data of a vertex.
   */
  struct VertexObject {
    V elt;                             // the element stored at this vertex
    VertexObjectItor pos;              // position in vertex_collection
    IncidenceEdgesItor inc_edges_pos;  // position in inc_edges_collection

    VertexObject(V _elt) : elt(_elt) {}  // pos and inc_edges_pos are initially "NULL".
  };

  /*
   * EdgeObject stores data of an edge.
   */
  struct EdgeObject {
    E elt;                          // the element stored at this edge
    Vertex origin_vertex;           // the vertex at the origin
    Vertex dest_vertex;             // the vertex at the destination
    EdgeObjectItor pos;             // position in edge_collection
    EdgeItor origin_inc_edges_pos;  // position in an edge list in inc_edges_collection
    EdgeItor dest_inc_edges_pos;    // position in an edge list in inc_edges_collection

    EdgeObject(const Vertex& v, const Vertex& w, E _elt) : origin_vertex(v), dest_vertex(w), elt(_elt) {} // pos origin_inc_edges_pos, and dest_inc_edges_pos are initially "NULL".
  };

  // ---------------------------------------------------------------------------------
  // This class should contain the following three member variables only:
  // vertex_collection, edge_collection, and inc_edges_collection
  // You are not allowed to define any other member variables (public or private).
  // ---------------------------------------------------------------------------------

  VertexObjectList vertex_collection;
  EdgeObjectList edge_collection;
  IncidenceEdgesList inc_edges_collection;

public:

  /*
   * Vertex is a position class of a vertex in AdjacencyListDirectedGraph.
   * Internally, a vertex is a pointer to an entry in vertex_collection.
   */
  class Vertex {

    VertexObject *v_obj;

  public:

    /*
     * The constructor of Vertex. This subsumes the default constructor.
     *
     * v - a pointer to a VertexObject
     */
    Vertex(VertexObject* v = NULL) : v_obj(v) {}


    /*
     * Return the element stored at this vertex.
     */
    V& operator*() const {
		return this->v_obj->elt ;
    }

    /*
     * Return a list of edges incident to this vertex.
     */
    EdgeList incidentEdges() const {
		EdgeList tmp = *(this->v_obj->inc_edges_pos);
 		return tmp;
    }

    /*
     * Check whether a vertex is adjacent to this vertex.
     * This means whether there is an edge that has this vertex
     * and the given vertex as the end points.
     *
     * v - the given vertex
     */
    bool isAdjacentTo(const Vertex& v) const {
		EdgeList inc = v.incidentEdges();
		for (EdgeItor iter = inc.begin(); iter != inc.end(); ++iter) {
			if ((*iter).opposite(v) == (*this)) {
				return true;
				break;
			}
		}

		return false;

    }

    /*
     * Check whether there is a directed edge connecting this vertex to the given vertex.
     *
     * v - the given vertex
     */
    bool isOutgoingTo(const Vertex& v) const {

		EdgeList inc = v.incidentEdges();
		if (inc.size() == 0) return false;

		for (EdgeItor iter = inc.begin(); iter != inc.end(); ++iter) {
			if ((*iter).dest() == v && (*iter).origin() == (*this)) {
				return true;
				break;
			}
		}

		return false;
    }

    /*
     * Return a directed edge connecting this vertex to the given vertex.
     * If the directed edge does not exist, throw an exception.
     *
     * v - the given vertex
     * Return the directed edge connecting this vertex to the given vertex.
     */
    Edge outgoingEdge(const Vertex& v) const {
		bool chk = false;
		EdgeList inc = v.incidentEdges();

		for (EdgeItor iter = inc.begin(); iter != inc.end(); ++iter) {
			if ( (*iter).opposite(*this) == v) {
				chk = true;
				return (*iter);
			}
		}
		if (!chk) {
			throw runtime_error("There is no directed edge");
		}

    }

    /*
     * Return the set of all directed edges connecting this vertex to any vertex.
     */
    EdgeList outgoingEdges() const {
		EdgeList tmp, inc;
		inc = this->incidentEdges();
		for (EdgeItor iter = inc.begin(); iter != inc.end(); ++iter) {
			if ( (*this) == (*iter).origin() ) {
				tmp.push_back(*iter);
			}
		}
		return tmp;
    }

    /*
     * Check whether this vertex is the same as the given vertex
     *
     * v - the given vertex
     * Return true if this vertex is the same as the given vertex
     */
    bool operator==(const Vertex& v) const {
		if ( this->v_obj->elt != v.v_obj->elt ) { return false; }
		else { return true; }
    }

    /*
     * Declare friend to AdjacencyListDirectedGraph so that
     * AdjacencyListDirectedGraph can access to the private
     * member variables of this class.
     */
    friend class AdjacencyListDirectedGraph<V,E>;
  };

  /*
   * Edge is a position class of an edge in AdjacencyListDirectedGraph.
   * Internally, an edge is a pointer to an entry in edge_collection.
   */
  class Edge {

    EdgeObject *e_obj;

  public:

    /*
     * The constructor of Edge. This subsumes the default constructor.
     *
     * v - a pointer to a EdgeObject
     */
    Edge(EdgeObject* e = NULL) : e_obj(e) {}

    /*
     * Return the element stored at this edge.
     */
    E& operator*() const {
		return (*e_obj).elt;
    }

    /*
     * Return the vertices of this directed edge.
     * The first element of the vertex list is the vertex of the origin.
     * The second element of the vertex list is the vertex of the destination.
     */
    VertexList endVertices() const {
		VertexList tmp;
		tmp.push_back((*this).origin());
		tmp.push_back((*this).dest());
		return tmp;
    }

    /*
     * Return the vertex of this edge that is different from the given vertex.
     * If the given vertex is origin, return destination.
     * If the given vertex is destination, return origin.
     * If the given vertex is neither origin nor destination, throw an exception.
     *
     * v - the given vertex
     * Return the other vertex of this edge
     */
    Vertex opposite(const Vertex& v) const {
		if ((*this).origin() == v) { return (*this).dest(); }
		else { return (*this).origin(); }
    }

    /*
     * Check whether a given edge is adjacent to this edge.
     * This means that whether the given edge and this edge
     * shared a vertex.
     *
     * edge - the given edge
     * Return true if the given edge is adjacent to this edge.
     */
    bool isAdjacentTo(const Edge& edge) const {

		if ((*this).origin() == edge.origin()) { return true; }
		else if((*this).origin() == edge.dest()) { return true; }
		else if ((*this).dest() == edge.origin()) { return true; }
		else if ((*this).dest() == edge.dest()) { return true; }
		else { return false; }

    }

    /*
     * Check whether a vertex is incident on this edge.
     * This means that whether the vertex is a vertex of this edge.
     *
     * v - the given vertex
     * Return true if the given vertex is incident to this edge.
     */
    bool isIncidentOn(const Vertex& v) const {
		bool chk = false;
		EdgeList inc = v.incidentEdges();
		
		for (EdgeItor iter = inc.begin(); iter != inc.end(); ++iter) {
			if ((*iter)==(*this)) {
				chk = true;
				return true;
			}
		}
		if (!chk) { return false; }

    }

    /*
     * Return the vertex at the origin of this edge.
     */
    Vertex origin() const {
		return (this->e_obj)->origin_vertex;
    }

    /*
     * Return the vertex at the destination of this edge.
     */
    Vertex dest() const {
		return (this->e_obj)->dest_vertex;
    }

    /*
     * Return true if this is a directed edge.
     * In this class, it should always return true.
     */
    bool isDirected() const {
		return true;
    }

    /*
     * Check whether this edge is the same as the given edge.
     *
     * edge - the given edge
     * Return true if this edge is the same as the given edge.
     */
    bool operator==(const Edge& edge) const {
		if (*(*this).origin() != *(edge.origin())) { return false; }
		if (*(*this).dest() != *(edge.dest())) { return false; }
		if (*(*this) != *edge) { return false; }

		return true;
    }

    /*
     * Declare friend to AdjacencyListDirectedGraph so that
     * AdjacencyListDirectedGraph can access to the private
     * member variables of this class.
     */
    friend class AdjacencyListDirectedGraph<V,E>;
  };


public:

  /*
   * Return the list of vertices in this graph.
   */
  VertexList vertices() {
	  VertexList vlist;
	  for (VertexObjectItor iter = vertex_collection.begin(); iter != vertex_collection.end(); ++iter) {
		  VertexObject* t = &(*iter);
		  vlist.push_back(Vertex(t));
	  }
	  return vlist;
  }

  /*
   * Return the list of edges in this graph.
   */
  EdgeList edges() {
	  EdgeList elist;
	  EdgeObjectItor iter = edge_collection.begin();
	  for (iter; iter != edge_collection.end(); ++iter) {
		  
		  elist.push_back( Edge(&(*iter)) );
	  }
	  return elist;
  }

  /*
   * Add a new vertex to this graph.
   *
   * x - the element to be stored in the new vertex.
   * Return the newly created vertex.
   */
  Vertex insertVertex(const V& x) {
	
	  vertex_collection.push_back(VertexObject(x));
	  VertexObjectItor iter = vertex_collection.end(); --iter;
	  vertex_collection.back().pos = iter;
	  EdgeList tlist;
	  inc_edges_collection.push_back(tlist);
	  IncidenceEdgesItor last = inc_edges_collection.end(); --last;
	  vertex_collection.back().inc_edges_pos = last;
	  VertexObject* t = &(vertex_collection.back());
	  return Vertex(t);
  }

  /*
   * Add a new edge to this graph. Throw an exception
   * if an edge has already existed between v and w.
   *
   * v - the vertex at the origin
   * w - the vertex at the destination
   * x - the element to be stored in the new edge.
   * Return the newly created edge.
   */
  Edge insertDirectedEdge(const Vertex& v, const Vertex& w, E x) {
	  
	  bool chk = true;
	  
	  if (v.isOutgoingTo(w)) { throw runtime_error("Edge already exist"); }

	  if(v==w) { throw runtime_error("Self-directed route is not allowed"); }
	  
	  if (chk) {
		  EdgeObject tmp(v, w, x);
		  
		  edge_collection.push_back(tmp);

		  EdgeObjectItor tpos = edge_collection.end(); --tpos;
		  edge_collection.back().pos = tpos;

		  EdgeObject* t = &(edge_collection.back());
		  IncidenceEdgesItor iter = v.v_obj->inc_edges_pos;
		  (*iter).push_back(Edge(t));
		  
		  edge_collection.back().origin_inc_edges_pos = find((*iter).begin(), (*iter).end() , Edge(t));

		  iter = w.v_obj->inc_edges_pos;
		  (*iter).push_back(Edge(t));
		  edge_collection.back().dest_inc_edges_pos = find((*iter).begin(), (*iter).end(), Edge(t));

		  
		  return Edge(t);
	  }
  }

  /*
   * Remove a vertex from this graph. All edges that contain
   * v as one of their vertices are also removed.
   *
   * v - a vertex
   */
  void eraseVertex(const Vertex& v) {
	  EdgeList inc = v.incidentEdges();
	  VertexObjectItor vitor = v.v_obj->pos;

	  IncidenceEdgesItor incitor = v.v_obj->inc_edges_pos;
	  //inc_edges_collection.erase(incitor);

	  for (EdgeItor iter = inc.begin(); iter != inc.end(); ++iter) {
		  eraseEdge(*iter);
	  }
	  
	  inc_edges_collection.erase(incitor);
	  vitor = vertex_collection.erase(vitor);

  }

  /*
   * Remove an edge from this graph.
   *
   * e - an edge
   */
  void eraseEdge(const Edge& e) {
	  EdgeItor oitor = e.e_obj->origin_inc_edges_pos;
	  EdgeItor ditor = e.e_obj->dest_inc_edges_pos;
	  EdgeItor tmp;
	  EdgeObjectItor eitor = e.e_obj->pos;

	  Vertex o = e.e_obj->origin_vertex;
	  Vertex d = e.e_obj->dest_vertex;

	  //VertexObjectItor vitor = v.v_obj->pos;
	  IncidenceEdgesItor incitor = o.v_obj->inc_edges_pos;
	  tmp = find((*incitor).begin(), (*incitor).end(), *oitor);
	  if (tmp != (*incitor).end()) {
		  oitor = (*incitor).erase(oitor);
	  }
	  
	  incitor = d.v_obj->inc_edges_pos;
	  tmp = find((*incitor).begin(), (*incitor).end(), *ditor);
	  if (tmp != (*incitor).end()) {
		  ditor = (*incitor).erase(ditor);
	  }

	  eitor = edge_collection.erase(eitor);

  }

};


#endif //ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H
