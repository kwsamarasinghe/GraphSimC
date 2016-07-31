/*
 * RandomGeometricGraph.h
 *
 *  Created on: May 25, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_GRAPH_RANDOM_GEOMETRIC_GRAPH_H_
#define SRC_GRAPH_RANDOM_GEOMETRIC_GRAPH_H_

#include <iterator>

#include <boost/graph/detail/adjacency_list.hpp>


using namespace boost;


class random_geometric_graph  {

public:

	random_geometric_graph(int width, int height, int R, int N) {
		this->width = width;
		this->height = height;
		this->R = R;
		this->N = N;

		//Generates the graph
		generate_graph();

	}
	;

	void setRadius(int R) {
		this->R = R;
	}

	int radius() {
		return this->R;
	}

	int totalNodes() {
		return N;
	}

private:

	struct VertexProperty {
		int x;
		int y;
	};

	int width;	//Width of the area
	int height;	//Height of the area
	int R;		//Radius of radio communication
	int N;		//Total number of nodes

	/**
	 * Generates a random geometric graph
	 */
	void generate_graph() {
		int i;

		//Generates a random point on the plane and add vertices
		for (i = 0; i < N; i++) {

			int x = rand() % width;
			int y = rand() % height;

			VertexProperty vertex_property;
			vertex_property.x = x;
			vertex_property.y = y;

			//boost::add_vertex(vertex_property,this);
		}

		//Establish the edges

	}
	;



};

#endif /* SRC_GRAPH_RANDOM_GEOMETRIC_GRAPH_H_ */
