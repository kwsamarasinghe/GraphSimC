/*
 * node_process.h
 *
 *  Created on: Jun 28, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_SIMULATION_VERTEX_PROCESS_H_
#define SRC_SIMULATION_VERTEX_PROCESS_H_

#include "../engine/packet_forwarder.h"
#include "../graph/graph_utils.h"


template<class NODE,class EDGE, class PACKET>
class packet_forwarder;
/**
 * Node process class which has to be implemented by every node
 * in order to add the functionality in the vertex
 */
template<class NODE, class EDGE, class PACKET>
class node_process{

	typedef packet_forwarder<NODE,EDGE,PACKET> forwarder;

public:
	node_process(){};
	node_process(NODE node,forwarder *forwarder){
		this->_node=node;
		this->_forwarder=forwarder;
	};
	virtual ~node_process(){};

	//This method must be implemented by the corresponding node processes
	virtual void start(){};

	//Packet handler which handles packets
	virtual void handle_packet(PACKET packet){};

protected:
	NODE _node;
	forwarder *_forwarder;

};


#endif /* SRC_SIMULATION_VERTEX_PROCESS_H_ */
