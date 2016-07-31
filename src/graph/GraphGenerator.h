/*
 * GraphGenerator.h
 *
 *  Created on: Jun 2, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_GRAPH_GRAPHGENERATOR_H_
#define SRC_GRAPH_GRAPHGENERATOR_H_


template <typename Vertex, typename Edge>
class Graph_Generator {
public:
	Graph_Generator();
	virtual ~Graph_Generator();

	void generate();

	std::iterator edge_iterator;	//This must be of type edge
	std::iterator vertex_iterator;	//This iterator must be of time Vertex


private:
	std::vector<Vertex> vertices;	//For the time being start to store the vertices in a vector
	std::vector<Edge> edges;		//Same here
};


#endif /* SRC_GRAPH_GRAPHGENERATOR_H_ */
