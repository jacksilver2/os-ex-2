
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <iostream>
#include "id_handler.h"
#include "utils.h"

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

int main()
{
	cout << "Welcome to the EX2 tester" << endl;
	cout << SOMECONST << endl;
	id_handler h;
	cout << "new id " << h.get_id() << endl;
	cout << "new id " << h.get_id() << endl;
	cout << "new id " << h.get_id() << endl;
	cout << "new id " << h.get_id() << endl;
	h.recycle_id(1);
	h.recycle_id(3);
	cout << "new id " << h.get_id() << endl;
	cout << "new id " << h.get_id() << endl;
	cout << "new id " << h.get_id() << endl;
	cout << "new id " << h.get_id() << endl;

}

