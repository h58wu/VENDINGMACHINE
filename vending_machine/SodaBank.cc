#include "SodaBank.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;                    // direct access to std
#include <cstdlib>


Bank::Bank( unsigned int numStudents ){
	this->numStudents = numStudents;
	account_balance.resize(numStudents,0);
}


void Bank::deposit( unsigned int id, unsigned int amount ){
	account_balance[id] += amount;
}
void Bank::withdraw( unsigned int id, unsigned int amount ){
	while(account_balance[id] < amount){
		_Accept(deposit); // wait for deposit becasue not enough balance
	}
	account_balance[id] -= amount;
}