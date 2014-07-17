#ifndef __SODABOTTLINGPLANT__
#define __SODABOTTLINGPLANT__


_Monitor Printer;
_Task NameServer;
_Task Truck;




_Task BottlingPlant {
	  Printer * prt;
    NameServer * nameServer;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int numVendingMachines;
    unsigned int timeBetweenShipments;
    Truck * truck;
    bool closing;
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
    ~BottlingPlant();
};

#endif