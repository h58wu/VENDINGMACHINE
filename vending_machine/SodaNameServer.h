#ifndef __SODANAMESERVER__
#define __SODANAMESERVER__
#include <uC++.h>
#include <vector>

using namespace std;

_Monitor Printer;
_Task VendingMachine;



_Task NameServer {
    Printer *prt;
	vector<int> vendNumPerStud;
	VendingMachine **VendList;
	unsigned int numStudents;
	unsigned int numVendingMachines;
    void main();
    unsigned int reged;
    uCondition bench;
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
    ~NameServer(){
        delete VendList;
    };
};


#endif