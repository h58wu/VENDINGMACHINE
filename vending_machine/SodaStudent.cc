#include "SodaNameServer.h"
#include "MPRNG.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;                    // direct access to std
#include <cstdlib>
#include "SodaPrinter.h"
#include "SodaWatCardOffice.h"
#include "SodaWatCard.h"
#include "SodaVendingMachine.h"
#include "SodaStudent.h"


extern MPRNG mprng;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ){
	this->prt = &prt;
	this->nameServer = &nameServer;
	this->cardOffice = &cardOffice;
	this->id = id;
	this->maxPurchases = maxPurchases;
}



void Student::main(){
	int purchase = mprng(maxPurchases - 1) + 1;
	int flavor	= mprng(3);  // picks a random favouite flavor
	prt->print(Printer::Student,id, 'S',flavor,purchase);
	bool flag_create = true;
	bool lost_buy = false;
	for(;flag_create == true;){

		try{
			watcard = cardOffice->create(id,5);  // tries to create a watcard
		}catch( WATCardOffice::Lost ){
			watcard.reset();
			prt->print(Printer::Student,id,'L');
			continue;
		}
		flag_create = false;	

	}
	flag_create = true;
	int result;
	VendingMachine *machine = nameServer->getMachine(id);  // gets the next vending machine
	prt->print(Printer::Student, id, 'V',machine->getId());
	for(int i = 0; i < purchase; i++){ // loops until the student has purchased the number of drinks it want to purchase
		if(lost_buy){
			lost_buy=false;
		}
		else{
			yield(mprng(9) + 1);
		}

		for(;flag_create;){
			try{ // try's to buy a drink
				result = machine->buy((VendingMachine::Flavours)flavor, *watcard);
			}
			catch(WATCardOffice::Lost){
				watcard.reset();
				prt->print(Printer::Student,id,'L');
				watcard = cardOffice->create(id,5);
				continue;
			}
			flag_create =false;
		}
		flag_create = true;
		if(result == 0){
			prt->print(Printer::Student,id,'B',((WATCard *)watcard)->getBalance());
		}
		else if(result == 1){
			i--;
			machine = nameServer->getMachine(id);
			prt->print(Printer::Student,id,'V',machine->getId());
			continue;
		}
		else{
			flag_create = false;
			i--;
			try{ // not enough money must wait for parent to transfer
				watcard = cardOffice->transfer(id,5+machine->cost(),watcard);

			} catch( WATCardOffice::Lost ){
					lost_buy = true;
					prt->print(Printer::Student,id,'L');
					watcard.reset();
					flag_create = true;
			}
			for(;flag_create == true;){
				try{
					watcard = cardOffice->create(id,5);
				}catch( WATCardOffice::Lost ){
					watcard.reset();
					prt->print(Printer::Student,id,'L');
					continue;
				}
				flag_create = false;
			}
			flag_create = true;
		}
	}
	prt->print(Printer::Student,id,'F');
}