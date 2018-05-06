#ifndef EX2_IDHANDLER_H
#define EX2_IDHANDLER_H

#include <vector>
#include <queue>

class IdHandler
{
public:
	/**
	 * ctor of IdHandler
	 */
	IdHandler();

	/**
	 * dtor if IdHandler
	 */
	~IdHandler();

	/**
	 * Returns next smallest possible id.
	 * increments id_counter if ids_pq is empty
	 * @returns next counter value if ids_pq is empty,
	 * otherwise the smallest number in ids_pq.
	 */
	int getId();

	/**
	 * takes used id for future use
	 * @param id the id to be recycled
	 */
	void recycleId(int id);

	/**
	 * prints the available ids that are in the _idsPQ
	 */
	void printIdsPQ();

	/**
	 * @return max id value up until now
	 */
	int currMaxId();

private:
	int _idCounter;
	std::priority_queue<int, std::vector<int>, std::greater<int> > _idsPQ;
	bool recycled_ids[100] = {false}; //we might get rid of this eventually.
};


#endif //EX2_ID_HANDLER_H
