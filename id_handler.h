#ifndef EX2_ID_HANDLER_H
#define EX2_ID_HANDLER_H

#define INITIAL_ID 0

#include <vector>
#include <queue>
using namespace std;

class id_handler
{
public:

	int id_counter;
	std::priority_queue<int, std::vector<int>, std::greater<int> > ids_pq;

	id_handler();

	virtual ~id_handler();

	int get_id();

	int recycle_id(int tid);

};


#endif //EX2_ID_HANDLER_H
