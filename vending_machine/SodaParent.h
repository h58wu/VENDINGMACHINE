#ifndef __SODAPARENT__
#define __SODAPARENT__
#include <uC++.h>

_Monitor Printer;
_Monitor Bank;



_Task Parent {
	unsigned int numStudents;
	unsigned int parentalDelay;
	Printer *prt;
	Bank 	*bank;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
    ~Parent(){};
};


#endif
