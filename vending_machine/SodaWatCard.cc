#include "MPRNG.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;                    // direct access to std
#include <cstdlib>
#include "SodaWatCard.h"

WATCard::WATCard(){
	balance = 0;
}

void WATCard::deposit( unsigned int amount ){
	balance += amount;
}
void WATCard::withdraw( unsigned int amount ){
	balance -= amount;
}
unsigned int WATCard::getBalance(){
	return balance;
}

