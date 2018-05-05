//
// Created by idob on 5/4/2018.
//

#ifndef T2_THREADLIST_H
#define T2_THREADLIST_H

class ThreadList;

/**
 * a node representing a thread
 */
struct ThreadNode
{
	int id;
	ThreadNode *next;
	ThreadNode *prev;
};


/**
 * a linked list of nodes representing threads
 */
class ThreadList
{
public:
	/**
	 * creates an empty list
	 */
	ThreadList();

	/**
	 * adds node to end of list
	 */
	void push(ThreadNode *node);

	/**
	 * removes node at the top of the list
	 * @return pointer to removed node
	 */
	ThreadNode* pop();

	/**
	 * removes given node from list (and set it's next, prev, list accordingly)
	 * assumes given node is in the list
	 */
	void remove(ThreadNode* node);

	/**
	 * concatenate nodes of given list to end of self and leave it empty
	 */
	void concat(ThreadList &other);

	/**
	 * prints contents
	 */
	void print();
private:
	ThreadNode *_head;
	ThreadNode *_tail;
};

#endif //T2_THREADLIST_H