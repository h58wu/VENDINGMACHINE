#ifndef __SODABANK__
#define __SODABANK__
#include <uC++.h>
#include <vector>

using namespace std;


_Monitor Bank {
	unsigned int numStudents;
	vector<unsigned int> account_balance;
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};


#endif
