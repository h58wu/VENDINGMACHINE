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

extern MPRNG mprng;


Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) {
	this->prt = &prt;
	this->nameServer = &nameServer;
	this->plant = &plant;
	this->numVendingMachines = numVendingMachines;
	this->maxStockPerFlavour = maxStockPerFlavour;
	this->prt->print(Printer::Truck, 'S');
	vend = this->nameServer->getMachineList();
}

Truck::~Truck(){
	this->prt->print(Printer::Truck, 'F');
}

void Truck::main(){
	unsigned int cargo[VendingMachine::MAX_FLAVOUR_VALUE];
	for(;;) {
		_Accept(~Truck) { // waits for destructor
			break;
		}
		_Else{
			yield(mprng(9) + 1);
			if (plant->getShipment(cargo)){ // checks if the plant is closed and also gets the shippment
				break;
			}
			int sum = 0;
			for (int i = 0; i < 4; i++) { // sums the total cargo in the truck
				sum += cargo[i];
			}
			prt->print(Printer::Truck, 'P', sum);
			for(int i = 0; i < numVendingMachines; i++){ // loops through all the vending machines
				sum = 0;
				
				for (int j = 0; j < 4; j++) {
					sum += cargo[j];
				}
				prt->print(Printer::Truck, 'd', i, sum);
				int temp = stockVend(i, cargo);  // stock the current vending machine and returns the left over cargo
				if (temp > 0) { // checks if there is no more cargo
					prt->print(Printer::Truck, 'U', i,temp);
					prt->print(Printer::Truck, 'D', i, 0);
					break;
				}
				sum = 0;
				
				for (int j = 0; j < 4; j++) {
					sum += cargo[j];
				}
				prt->print(Printer::Truck, 'D', i, sum);
			}
		}
	}
}

int Truck::stockVend(int id, unsigned int cargo[]) {
	int notFilled = 0;
	unsigned int * inv = vend[id]->inventory();
	for (int i = 0; i <  4; i++) {
		if (inv[i] + cargo[i] <= maxStockPerFlavour) {
			inv[i] += cargo[i];
			cargo[i] = 0;
		}
		else {
			int temp = maxStockPerFlavour - inv[i];
			inv[i] = maxStockPerFlavour;
			cargo[i] -= temp;
		}
		notFilled += maxStockPerFlavour - inv[i];
		
	}
	vend[id]->restocked();
	return notFilled;
}

