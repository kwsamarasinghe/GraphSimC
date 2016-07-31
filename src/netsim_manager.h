/*
 * netsim.h
 *
 *  Created on: May 25, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef NETSIM_H_
#define NETSIM_H_

#include "graph/graph_utils.h"
#include "engine/engine.h"

#include <iterator>
#include <boost/log/trivial.hpp>

using namespace std;

template<class NODE, class EDGE, class PACKET>
class simulation_engine;

class netsim_manager {

	typedef simulation_engine<node,comm_link,packet> engine;

	public:
		netsim_manager():_engine(10){};
		~netsim_manager(){};

		void start(){
			BOOST_LOG_TRIVIAL(info)<<"[NetSimManager] Starting simulation engine";
			_engine.start();
			BOOST_LOG_TRIVIAL(info)<<"[NetSimManager] Simulation engine started";
		}
	private:
		engine _engine;

};

#endif /* NETSIM_H_ */
