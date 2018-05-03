
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <iostream>
#include "id_handler.h"
#include "utils.h"
#include "state.h"

void id_test();

using std::cout;
using std::endl;

void print_pq(priority_queue<int> pq)
{
	cout<<"Printing queue\n"<<endl;
	while (!pq.empty())
	{
		cout<<pq.top()<<endl;
		pq.pop();
	}
}

void id_test()
{
	cout << "Welcome to the id_handler tester" << endl;
	id_handler h;
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	h.recycle_id(1);
	h.recycle_id(3);
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	h.recycle_id(4);
	cout << "got id " << h.get_id() << endl;
	h.recycle_id(2);
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
	cout << "got id " << h.get_id() << endl;
}

int main()
{
	id_test();
	state s = READY;

}

