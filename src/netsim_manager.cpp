/*
 * simulator.cpp
 *
 *  Created on: May 25, 2016
 *  Author: Kasun Samarasinghe
 */

#include "netsim_manager.h"

#include <iostream>
#include <mpi/mpi.h>

#include <boost/log/trivial.hpp>

using namespace std;
using namespace boost;
using boost::graph::distributed::mpi_process_group;

class netsim_manager;


int main(int argc, char* argv[]) {

	boost::mpi::environment env(argc, argv);

	BOOST_LOG_TRIVIAL(info)<<"[NetSimManager] Initializing simulation";
	netsim_manager sim_manager;
	sim_manager.start();
	BOOST_LOG_TRIVIAL(info)<<"[NetSimManager] Initialized simulation";

	return 0;
}
