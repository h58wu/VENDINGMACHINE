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

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ){
	this->prt = &prt;
	this->numStudents = numStudents;
	this->numVendingMachines = numVendingMachines;
	VendList = new VendingMachine * [numVendingMachines];
	vendNumPerStud.resize(numStudents,0);
	reged = 0;
}



void NameServer::VMregister(VendingMachine * vendingmachine){
	if(reged < numVendingMachines){
		VendList[reged] = vendingmachine;
		prt->print(Printer::NameServer,'R',reged);
		reged++;
	}
	while ( ! bench.empty() ) bench.signal(); 

}



VendingMachine* NameServer::getMachine(unsigned int id){
	while(reged != numVendingMachines){
		bench.wait();
	}
	int cur = vendNumPerStud[id];
	if(cur == (numVendingMachines - 1)){
		vendNumPerStud[id] = 0;
	}
	else
		vendNumPerStud[id]++;
	
	prt->print(Printer::NameServer,'N',id,cur);	
	while ( ! bench.empty() ) bench.signal(); 
	return VendList[cur];
}


VendingMachine** NameServer::getMachineList(){
	while(reged != numVendingMachines){
		bench.wait();
	}
	while ( ! bench.empty() ) bench.signal(); 
	return this->VendList;
}


void NameServer::main(){
	prt->print(Printer::NameServer,'S');
	while(true){
		_Accept(VMregister,getMachine,getMachineList){

		}or _Accept(~NameServer){
			break;
		}
	}
	prt->print(Printer::NameServer,'F');
}	