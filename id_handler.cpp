#include <vector>
#include <queue>
#include <iostream>
#include <cassert>
#include "id_handler.h"

using namespace std;

id_handler::id_handler()
{
	id_counter = INITIAL_ID;
};

id_handler::~id_handler() = default;

int id_handler::get_id()
{
	if (id_handler::ids_pq.empty())
	{
		return ++id_handler::id_counter;
	}
	else
	{
		int ret = id_handler::ids_pq.top();
		id_handler::ids_pq.pop();
		return ret;
	}
}

/**
 * recycles tid
 * @param tid
 * @return 0
 */
int id_handler::recycle_id(int tid)
{
	assert(tid>0);
	cout << "recycled " << tid << endl;
	id_handler::ids_pq.push(tid);
	//is there a problem if tid is recycled without
	//wnybody having got it?
	return 0;
}
