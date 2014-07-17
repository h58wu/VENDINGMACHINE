#include "SodaParent.h"
#include "MPRNG.h"
#include "SodaBank.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;                    // direct access to std
#include <cstdlib>
#include "SodaPrinter.h"

extern MPRNG mprng;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ){
	this->prt = &prt;
	this->bank = &bank;
	this->numStudents = numStudents;
	this->parentalDelay = parentalDelay;
}



void Parent::main(){
	prt->print(Printer::Parent,'S');
	while(true){
		_Accept(~Parent){
			break;
		}
		_Else{
			int id = mprng(numStudents-1);
			int deposit = mprng(2) + 1;
			yield(parentalDelay);
			bank->deposit(id,deposit);
			prt->print(Printer::Parent,'D',id,deposit);
		}
	}
	prt->print(Printer::Parent,'F');
}

