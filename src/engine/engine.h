/*
 * simulationengine.h
 *
 *  Created on: Jul 11, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_ENGINE_SIMULATIONENGINE_H_
#define SRC_ENGINE_SIMULATIONENGINE_H_

#include <unordered_map>

#include "../graph/network_graph.h"
#include "../node/random_walk_process.h"
#include "packet_forwarder.h"

#include <vector>
#include <boost/graph/distributed/adjacency_list.hpp>
#include <boost/log/trivial.hpp>

#include <omp.h>

using namespace std;
using namespace boost;

template<class NODE, class EDGE, class PACKET>
class simulation_engine {

	typedef network_graph<NODE, EDGE> graph;
	typedef packet_forwarder<NODE,EDGE,PACKET> forwarder;
	typedef node_process<NODE, EDGE, PACKET> process;
	typedef std::unordered_map<int, process> process_map;

public:
	simulation_engine(int network_size);
	virtual ~simulation_engine();

	void start();
	void handle_packet(PACKET packet);

private:
	graph _graph;			//Underlying graph
	forwarder _forwarder;	//Packet forwarder
	process_map _process_map;	//Process map
};

template<class NODE, class EDGE, class PACKET>
simulation_engine<NODE, EDGE, PACKET>::simulation_engine(int network_size) :
		_graph(network_size),_forwarder(this) {
}

template<class NODE, class EDGE, class PACKET>
simulation_engine<NODE, EDGE, PACKET>::~simulation_engine() {}

/*
 * Initializes the node processes and starts the packet forwarder
 */
template<class NODE, class EDGE, class PACKET>
void simulation_engine<NODE, EDGE, PACKET>::start() {

	//Starts the packet forwarder
	BOOST_LOG_TRIVIAL(info)<<"[Engine] Starting packet processor";

	omp_set_nested(1);
	#pragma omp parallel num_threads(2)
	{
		int thread_id = omp_get_thread_num();
		if (thread_id != 0) {
			BOOST_LOG_TRIVIAL(info)<<"[Engine] Packet processor started";
			_forwarder.start();
		} else {
			BOOST_LOG_TRIVIAL(info)<<"[Engine] Initializing the node processes";
			//Starts the node processes
			vector<NODE> vertices=_graph.get_vertices();
			#pragma omp parallel num_threads(2)
			{
				int thread_ids=omp_get_thread_num();
				if(thread_ids!=0) {
					BOOST_LOG_TRIVIAL(info)<<"[Engine] Node processes non master";
					#pragma omp parallel for ordered schedule(dynamic)
						for(int i=0;i<vertices.size();i++) {
							process* node_process_=new random_walk_process<NODE,EDGE,PACKET>(vertices.at(i),&_forwarder);
							node_process_->start();
						}
				}else{
					BOOST_LOG_TRIVIAL(info)<<"[Engine] Node processes started";
				}
			}
		}
	}

}


template<class NODE,class EDGE,class PACKET>
void simulation_engine<NODE,EDGE,PACKET>::handle_packet(PACKET packet){

	int source_=packet._addr_source;
	int destination_=packet._addr_destination;

	//Gets the destination node from the graph

}

#endif /* SRC_ENGINE_SIMULATIONENGINE_H_ */
