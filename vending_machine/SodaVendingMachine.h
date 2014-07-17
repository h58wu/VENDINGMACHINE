#ifndef __Q6VENDINGMACHINE__
#define __Q6VENDINGMACHINE__


_Monitor Printer;
_Task NameServer;
class WATCard;



//CHANGE ID TO PRIVATE AFTER!!!!!
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//********************************

_Task VendingMachine {
    Printer * prt;
    NameServer * nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    void main();
    unsigned int stock[4];
    bool restocking;
    
  public:
    enum Flavours { COLA, GRAPE, ORANGE, DIET, MAX_FLAVOUR_VALUE};                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
    ~VendingMachine();
};

#endif