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

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ) {
	this->prt = &prt;
	this->nameServer = &nameServer;
	this->numVendingMachines = numVendingMachines;
	this->maxShippedPerFlavour = maxShippedPerFlavour;
	this->maxStockPerFlavour = maxStockPerFlavour;
	this->timeBetweenShipments = timeBetweenShipments; 
	closing = false;
	this->prt->print(Printer::BottlingPlant, 'S');
	truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (closing) {
		return true;
	}
	int sum = 0;
	for (int i = 0; i < 4; i++) { // adds drinks to the trucks cargo
		cargo[i] = mprng(maxShippedPerFlavour);
		sum += cargo[i];
	}
	this->prt->print(Printer::BottlingPlant, 'G', sum);
	yield(timeBetweenShipments);
	return false;
}

void BottlingPlant::main() {
	for(;;) {
		_Accept(~BottlingPlant) {
			break;
		}
		or _Accept(getShipment);
	}
}

BottlingPlant::~BottlingPlant(){
	closing = true;
	_Accept(getShipment) { // must wait for truck to delete it
		delete truck;
	}
	this->prt->print(Printer::BottlingPlant, 'F');
}