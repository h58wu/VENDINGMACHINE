#include <uC++.h>
#include "SodaNameServer.h"
#include "MPRNG.h"
#include "SodaBank.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;                    // direct access to std
#include <cstdlib>
#include "SodaPrinter.h"
#include "SodaVendingMachine.h"
#include "SodaBottlingPlant.h"
#include "SodaParent.h"
#include "SodaStudent.h"
#include "SodaTruck.h"
#include "SodaWatCard.h"


VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour ) {
	this->prt = &prt;
	this->nameServer = &nameServer;
	this->id = id;
	this->sodaCost = sodaCost;
	this->maxStockPerFlavour = maxStockPerFlavour;
	restocking = false;

	for(int i = 0; i < 4; i++) {
		stock[i] = 0;
	}

	this->prt->print( Printer::Vending, id, 'S', sodaCost);
	this->nameServer->VMregister(this);
}

VendingMachine::~VendingMachine () {
	prt->print( Printer::Vending, id, 'F');
}

_Nomutex unsigned int VendingMachine::cost() {
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
	return id;
}

void VendingMachine::restocked() {
	prt->print( Printer::Vending, id, 'R');
	restocking = false;
}

unsigned int *VendingMachine::inventory() {
	prt->print( Printer::Vending, id, 'r');
	restocking = true;
	return stock;
}

 VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ){
	if(restocking){
		_Accept (restocked);
	}
	if(stock[flavour] == 0) {
		return STOCK;
	}
	if(card.getBalance() < sodaCost) {
		return FUNDS;
	}
	card.withdraw(sodaCost);
	stock[flavour]--;
	prt->print( Printer::Vending, id, 'B', flavour, (int)stock[flavour]);
	return BUY;
}

void VendingMachine::main () {
	for (;;) {
		_Accept(~VendingMachine) {
			break;
		}
		or _Accept(buy){}
		or _Accept(inventory){}
		or _Accept(restocked){};
	}
}