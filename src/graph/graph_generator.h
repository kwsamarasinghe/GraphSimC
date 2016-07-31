/*
 * GraphGenerator.h
 *
 *  Created on: Jun 2, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_GRAPH_GRAPH_GENERATOR_H_
#define SRC_GRAPH_GRAPH_GENERATOR_H_

#include <iostream>

#include <iterator>
#include <vector>
#include <math.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/log/trivial.hpp>

using namespace std;
using namespace boost;

/**
 * A random geometric graph generator
 */
template<typename Graph>
class random_geometric_generator: public iterator_facade<
		random_geometric_generator<Graph>,
		std::pair<typename graph_traits<Graph>::vertices_size_type,
				typename graph_traits<Graph>::vertices_size_type>,
		std::input_iterator_tag,
		const std::pair<typename graph_traits<Graph>::vertices_size_type,
				typename graph_traits<Graph>::vertices_size_type>&> {
	typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
	typedef typename graph_traits<Graph>::edges_size_type edges_size_type;

	typedef boost::geometry::model::point<int, 2, boost::geometry::cs::cartesian> P;

	typedef std::pair<vertices_size_type, vertices_size_type> edge;
	typedef std::vector<edge> edges;

	typedef typename edges::iterator edge_list_iterator;

public:

	random_geometric_generator() :
			n(0), e(0) {

	}

	random_geometric_generator(vertices_size_type n) :
			n(n), e(0) {

		std::vector<P>::iterator pi, pi_;

		//Generates a random set of points within a 100x100 area
		int k;
		for (k = 0; k < n; k++) {
			int x = rand() % 100;
			int y = rand() % 100;
			P p;
			p.set<0>(x);
			p.set<1>(y);
			pi = points.insert(pi, p);

		}

		std::vector<P>::iterator qi, qi_;

		pi = points.begin();
		pi_ = points.end();

		qi = points.begin();
		qi_ = points.end();

		edge_list_iterator eit;
		eit = edge_list.begin();

		//Generates the connectivity based on the distance between points
		int i = 0;
		int j = 0;
		for (; pi != pi_;) {

			P a = (*pi);
			int x1 = a.get<0>();
			int y1 = a.get<1>();

			for (; qi != qi_;) {

				if (i != j) {

					int x2 = (*qi).get<0>();
					int y2 = (*qi).get<1>();

					double distance = sqrt(
							pow((x1 - x2), 2) + pow((y1 - y2), 2));
					if (distance <= 20) {
						std::pair<vertices_size_type, vertices_size_type> ep(i,
								j);
						eit = edge_list.insert(eit, ep);
						e++;
					}
				}

				qi++;
				j++;
			}

			pi++;
			i++;
			j = i;

			qi = points.begin();
			qi=qi+i;
			qi_ = points.end();

		}

		edge_list_it = edge_list.begin();
		next();

		BOOST_LOG_TRIVIAL(info)<<"[RandomGeometricGenerator] Random Geometric Graph connectivity generated";
	}

	const std::pair<vertices_size_type, vertices_size_type>&
	dereference() const {
		return current;
	}

	void increment() {
		--e;
		next();
	}

	bool equal(const random_geometric_generator& other) const {
		return e == other.e;
	}

	vector<P> get_points(){
		return points;
	}

private:
	void next() {
		current = (*edge_list_it);
		edge_list_it++;
	}

	int n; //Number of nodes

	std::vector<P> points;
	edges edge_list;
	edge_list_iterator edge_list_it;
	edge current;
	edges_size_type e;

};

#endif
