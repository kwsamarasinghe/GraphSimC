/*
 * packet_queue.h
 *
 *  Created on: Jun 30, 2016
 *  Author: Kasun Samarasinghe
 */

#ifndef SRC_ENGINE_PACKET_QUEUE_H_
#define SRC_ENGINE_PACKET_QUEUE_H_

#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

/**
 * Thread safe queue implementation to hold the packets from the vertices
 */
template<class PACKET>
class packet_queue {

public:
	//Thread safe push to the queue
	void push(PACKET packet) {
		std::lock_guard <std::mutex> lock(_mutex);
		_queue.push(packet);
		_condition.notify_one();
	}

	//Thread safe pop from the queue
	void wait_and_pop(PACKET* packet) {
		//Wait if the queue is empty
		std::unique_lock<std::mutex> lock(_mutex);
		_condition.wait(lock, [this]{return !_queue.empty();});

		//Pops from the queue
		packet = &(_queue.front());
		_queue.pop();
	}

private:
	std::queue<PACKET> _queue;
	std::mutex _mutex;
	std::condition_variable _condition;
};

#endif /* SRC_ENGINE_PACKET_QUEUE_H_ */
