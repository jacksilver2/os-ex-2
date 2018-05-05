#include <vector>
#include <queue>
#include <iostream>
#include <cassert>
#include "ID_handler.h"

using namespace std;

/**
 * ctor
 */
ID_handler::ID_handler()
{
	_idCounter = INITIAL_ID;
};

/**
 * dtor
 */
ID_handler::~ID_handler() = default;

/**
 * Returns next smallest possible id.
 * increments id_counter if ids_pq is empty
 * @returns next counter value if ids_pq is empty,
 * otherwise the smallest number in ids_pq.
 */
int ID_handler::get_id()
{
	int ret;
	if (ID_handler::ids_pq.empty())
	{
		ret = ++ID_handler::_idCounter;
	}
	else
	{
		ret = ID_handler::ids_pq.top();
		ID_handler::ids_pq.pop();
	}
	cout << "provided id " << ret << endl;
	ID_handler::recycled_ids[ret] = false;
	return ret;
}

/**
 * recycles tid
 * @param tid
 * @return 0
 */
/**
 *
 * @param tid the id to be recycled
 * @return pushes tid to queue
 */
int ID_handler::recycle_id(int tid)
{
	//make sure an non-provided id is not being recycled
	//make sure id is not recycled twice
	//make sure 0 is not being recycled
	assert(tid <= _idCounter);
	assert(!recycled_ids[tid]);
	assert(tid != 0);
	recycled_ids[tid] = true;
	cout << "recycled " << tid << endl;
	ID_handler::ids_pq.push(tid);

	return 0;
}

/**
 * prints the available ids that are in the ids_pq
 */
void ID_handler::print_ids_pq()
{
	queue<int> tmp;
	cout << "\tPrinting queue:" << endl;
	cout << "\tFront of queue >" << endl;
	while (!ids_pq.empty())
	{
		cout << "\t" << ids_pq.top() << endl;
		tmp.push(ids_pq.top());
		ids_pq.pop();
	}
	cout << "\t< Back of queue" << endl;
	int p;
	while (!tmp.empty())
	{
		p = tmp.front();
		ids_pq.push(p);
		tmp.pop();
	}
}

int ID_handler::get_counter()
{
	return _idCounter;
}
