/*
 * random_walk_process.cpp
 *
 *  Created on: Jul 15, 2016
 *  Author: Kasun Samarasinghe
 */

#include "../engine/engine.h"
#include "../engine/node_process.h"

#include <boost/log/trivial.hpp>

template<class NODE,class EDGE, class PACKET>
class packet_forwarder;

/**
 * A random walk process, which generates a packet to a random destination
 * and performs a random walk
 */
template<class NODE, class EDGE, class PACKET>
class random_walk_process: public node_process<NODE, EDGE, PACKET> {

	typedef packet_forwarder<NODE,EDGE,PACKET> forwarder;

public:
	random_walk_process() {
		this->_node(0);
	};

	random_walk_process(NODE node, forwarder *forwarder) {
		this->_node = node;
		this->_forwarder = forwarder;
	};

	~random_walk_process() {};

	//Starts the node process
	void start();

	//Handles an incoming packet
	void handle_packet(PACKET packet);

};

template<class NODE, class EDGE, class PACKET>
void random_walk_process<NODE, EDGE, PACKET>::start() {

	//Simple simulation process, where every node generates packet at random
	PACKET packet;
	packet._addr_source = this->_node.get_id();
	packet._addr_destination = rand() % 10;

	//Sends the packet
	this->_forwarder->send(packet);

	BOOST_LOG_TRIVIAL(info)<<"[RandomWalkProcess] Packet sent; source "<<packet._addr_source<<
			" destination "<<packet._addr_destination;
}

template<class NODE, class EDGE, class PACKET>
void random_walk_process<NODE, EDGE, PACKET>::handle_packet(PACKET packet) {

}
