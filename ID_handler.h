#ifndef EX2_ID_HANDLER_H
#define EX2_ID_HANDLER_H

#define INITIAL_ID 0

#include <vector>
#include <queue>

using namespace std;

class ID_handler
{
public:

	ID_handler();

	virtual ~ID_handler();

	int get_id();

	int recycle_id(int tid);

	void print_ids_pq();

private:

	int id_counter;
	std::priority_queue<int, std::vector<int>, std::greater<int> > ids_pq;
	bool recycled_ids[100] = {false}; //we might get rid of this eventually.
};


#endif //EX2_ID_HANDLER_H
