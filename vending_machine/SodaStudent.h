#ifndef __SODASTUDENT__
#define __SODASTUDENT__
#include <uC++.h>
#include <vector>
#include <uFuture.h>
#include "SodaWatCard.h"

_Monitor Printer;
_Task NameServer;
_Task WATCardOffice;
_Task VendingMachine;



_Task Student {
	Printer *prt;
	NameServer *nameServer;
	WATCardOffice *cardOffice;
	unsigned int maxPurchases;
	unsigned int id;
  WATCard::FWATCard watcard;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
    ~Student(){
    };
};


#endif