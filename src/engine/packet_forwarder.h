/*
 * packet_processor.h
 *
 *  Created on: Jun 29, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_ENGINE_PACKET_PROCESSOR_H_
#define SRC_ENGINE_PACKET_PROCESSOR_H_

#include <list>
#include <omp.h>

#include "engine.h"
#include "packet_queue.h"

using namespace std;


template<class NODE,class EDGE, class PACKET>
class simulation_engine;

struct packet;

/**
 * Message passing backbone which passes the packets to the destination
 */
template<class NODE, class EDGE ,class PACKET>
class packet_forwarder {

	typedef simulation_engine<NODE,EDGE,PACKET> engine;

public:

	packet_forwarder(engine* _engine_):_engine(_engine){}

	/**
	 * Start the event processor
	 */
	void start() {

		BOOST_LOG_TRIVIAL(info)
							<< "[PacketForwarder] Waiting to read a packet from the queue";
		while (true) {
			//Continuously reads from the packet queue
			PACKET packet;
			_packet_queue.wait_and_pop(&packet);

			//Forwards the packet to the destination
			int destination_ = packet._addr_destination;
			BOOST_LOG_TRIVIAL(info) << "[PacketForwarder] Reading a packet";
		}

		BOOST_LOG_TRIVIAL(info) << "[PacketForwarder] Packet forwarder started";
	}

	/**
	 * Interface for node processes to send a packet
	 */
	void send(PACKET packet) {
		BOOST_LOG_TRIVIAL(info) << "[PacketForwarder] Enqueue packet";
		BOOST_LOG_TRIVIAL(info) << "[PacketForwarder] Destination "<<packet._addr_destination;
		BOOST_LOG_TRIVIAL(info) << "[PacketForwarder] Source "<<packet._addr_source;
		_packet_queue.push(packet);
	}

private:
	packet_queue<packet> _packet_queue; //Packet queue which handles all the packets of the simulation
	engine* _engine;			//Pointer to the simulation engine
};

/*template<class NODE, class EDGE ,class PACKET>
packet_forwarder<NODE,EDGE,PACKET>::packet_forwarder(engine engine_){

}*/


struct packet {
	int _addr_destination;
	int _addr_source;
	int _ttl;
	string _message;
};

#endif /* SRC_ENGINE_PACKET_PROCESSOR_H_ */
