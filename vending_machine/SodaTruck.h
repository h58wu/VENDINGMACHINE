#ifndef __Q6TRUCK__
#define __Q6TRUCK__


_Monitor Printer;
_Task NameServer;
_Task VendingMachine;



_Task Truck {
	Printer * prt;
    NameServer * nameServer;
    BottlingPlant * plant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    void main();
    VendingMachine ** vend;
    int stockVend( int id, unsigned int cargo[]);
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
};

#endif