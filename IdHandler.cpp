#include <vector>
#include <queue>
#include <iostream>
#include <cassert>
#include "IdHandler.h"

/**
 * ctor
 */
IdHandler::IdHandler()
{
	_idCounter = 0;
};

/**
 * dtor
 */
IdHandler::~IdHandler() = default;

/**
 * Returns next smallest possible id.
 * increments _idCounter if idsPq is empty
 * @returns next counter value if idsPQ is empty,
 * otherwise the smallest number in idsPQ.
 */
int IdHandler::getId()
{
	int ret;
	if (_idsPQ.empty())
	{
		ret = ++_idCounter;
	}
	else
	{
		ret = _idsPQ.top();
		_idsPQ.pop();
	}
	std::cout << "provided id " << ret << std::endl;
	IdHandler::recycled_ids[ret] = false;
	return ret;
}

/**
 * takes used id for future use
 * @param id the id to be recycled
 */
void IdHandler::recycleId(int id)
{
	//make sure an non-provided id is not being recycled
	//make sure id is not recycled twice
	//make sure 0 is not being recycled
	assert(id <= _idCounter);
	assert(!recycled_ids[id]);
	assert(id != 0);
	recycled_ids[id] = true;
	std::cout << "recycled " << id << std::endl;
	_idsPQ.push(id);
}

/**
 * prints the available ids that are in the _idsPQ
 */
void IdHandler::printIdsPQ()
{
	std::queue<int> tmp;
	std::cout << "\tPrinting queue:" << std::endl;
	std::cout << "\tFront of queue >" << std::endl;
	while (!_idsPQ.empty())
	{
		std::cout << "\t" << _idsPQ.top() << std::endl;
		tmp.push(_idsPQ.top());
		_idsPQ.pop();
	}
	std::cout << "\t< Back of queue" << std::endl;
	int p;
	while (!tmp.empty())
	{
		p = tmp.front();
		_idsPQ.push(p);
		tmp.pop();
	}
}

/**
 * @return max id value up until now
 */
int IdHandler::currMaxId()
{
	return _idCounter;
}
