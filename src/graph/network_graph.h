/*
 * networkgraph.h
 *
 *  Created on: May 25, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_GRAPH_NETWORKGRAPH_H_
#define SRC_GRAPH_NETWORKGRAPH_H_

#include <iterator>
#include <vector>

#include "boost/mpi.hpp"
#include "boost/graph/use_mpi.hpp"
#include "boost/graph/distributed/adjacency_list.hpp"
#include "boost/graph/distributed/mpi_process_group.hpp"
#include "boost/log/trivial.hpp"

#include "graph_generator.h"

using namespace std;
using namespace boost;
using boost::graph::distributed::mpi_process_group;

/**
 * Underlying graph on which the simulations are performed
 */
template<class NODE, class EDGE>
class network_graph {

	typedef adjacency_list<vecS,
			distributedS<boost::graph::distributed::mpi_process_group, vecS>,
			undirectedS, NODE, EDGE> G;
	typedef random_geometric_generator<G> rgg;
	typedef boost::geometry::model::point<int, 2, boost::geometry::cs::cartesian> P;

public:

	network_graph(int N) :
			N(N), _rgg_first(N), _graph(_rgg_first, _rgg_last, N) {

		//Sets the coordinates of nodes
		vector<P> points = _rgg_first.get_points();
		vector<P>::iterator pit;
		pit = points.begin();

		typedef typename boost::graph_traits<G>::vertex_iterator vertex_iterator;
		pair<vertex_iterator, vertex_iterator> p;
		p = boost::vertices(_graph);

		vertex_iterator it = p.first;
		int i=0;
		for (; it != p.second; ++it) {

			int x = ((P) (*pit)).get<0>();
			int y = ((P) (*pit)).get<1>();
			pit++;

			//Sets the coordinates
			NODE* node = &(_graph)[*it];
			node->set_x(x);
			node->set_y(y);

			//Sets an ID
			node->set_id(i++);
		}

		BOOST_LOG_TRIVIAL(info) << "[NetworkGraph] Initialized network graph";
	}

	virtual ~network_graph() {};

	/**
	 * Returns the vertices
	 */
	std::vector<NODE> get_vertices() {
		typedef typename boost::graph_traits<G>::vertex_iterator vertex_iterator;
		pair<vertex_iterator, vertex_iterator> p;
		p = boost::vertices(_graph);

		vertex_iterator it = p.first;
		vector<NODE> nodes;
		typedef typename vector<NODE>::iterator insert_iterator;
		insert_iterator iit = nodes.begin();

		for (; it != p.second; ++it) {
			NODE v = (_graph)[*it];
			iit = nodes.insert(iit, v);
		}

		return nodes;
	}

private:

	//Graph generators
	rgg _rgg_first, _rgg_last;

	//Underlying graph
	G _graph;

	//Vertex property
	struct VertexProperty {
		int x;
		int y;
	};

	//Number of nodes
	int N;
};

#endif /* SRC_GRAPH_NETWORKGRAPH_H_ */
