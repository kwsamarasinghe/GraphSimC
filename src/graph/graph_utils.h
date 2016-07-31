/*
 *  graph_utils.h
 *
 *  Created on: Jun 7, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_GRAPH_GRAPH_UTILS_H_
#define SRC_GRAPH_GRAPH_UTILS_H_

#include <math.h>


class node{

private:
	//A unique ID
	int id;
	//Coordinates
	int x;
	int y;

public:
	node() :
			x(0), y(0),id(0) {
	};

	int get_x() {
		return x;
	}

	int get_y() {
		return y;
	}

	int get_id(){
		return id;
	}

	void set_x(int x) {
		this->x = x;
	}

	void set_y(int y) {
		this->y = y;
	}

	void set_id(int id){
		this->id=id;
	}

	double distanceTo(node u) {
		return sqrt(((x - u.x) ^ 2 + (y - u.y) ^ 2));
	}

	template<typename Archiver>
	void serialize(Archiver& ar, const unsigned int /*version*/) {
		ar & x & y;
	}

};



class comm_link {

private:
	node _first;
	node _second;
	int _weight;

public:
	template<typename Archiver>
	void serialize(Archiver& ar, const unsigned int /*version*/) {
		ar & _weight;
	}

	node* get_first(){
		return &_first;
	}

	node* get_secont(){
		return &_second;
	}
};

#endif /* SRC_GRAPH_GRAPH_UTILS_H_ */
