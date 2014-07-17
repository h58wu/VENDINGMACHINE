#include "MPRNG.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;                    // direct access to std
#include <cstdlib>
#include "SodaWatCardOffice.h"
#include "SodaPrinter.h"
#include "SodaWatCard.h"
#include "SodaBank.h"





void WATCardOffice::Courier::main(){
	prt->print(Printer::Courier,cid, 'S');
	while(true){
                if(cardoffice->finishing){
                    break;
                }
                else{
                    while(cardoffice->v_j.empty()){
                    	cardoffice->lock_job.P();
                    	if(cardoffice->finishing){
                    		break;
                		}
                    }
             		if(cardoffice->finishing){
                    	break;
                	}
                    int type = cardoffice->v_j[0].args.type;
                    unsigned int id_trans = cardoffice->v_j[0].args.id;
                    unsigned int amount_trans = cardoffice->v_j[0].args.amount;
                    prt->print(Printer::Courier,cid,'t',id_trans,amount_trans);
                    cardoffice->bank->withdraw(id_trans,amount_trans);
                    prt->print(Printer::Courier,cid,'T',id_trans,amount_trans);

                    if(type == 1){
                        WATCard * card = new WATCard();
                        cardoffice->record_wat.push_back(card);
                        if(mprng(5) == 2){
                            cardoffice->v_j[0].result.exception(new Lost);
                            cardoffice->resultAvailable.V();
                        }
                        else{
                            card->deposit(amount_trans);
                            cardoffice->v_j[0].result.delivery(card);
                            cardoffice->resultAvailable.V();
                        }

                    }
                    else{
                        if(mprng(5) == 2){
                        	
                            cardoffice->v_j[0].result.exception(new Lost);
                            cardoffice->resultAvailable.V();
                        }
                        else{
                            cardoffice->v_j[0].args.ocard->deposit(amount_trans);
                            cardoffice->v_j[0].result.delivery(cardoffice->v_j[0].args.ocard);
                            cardoffice->resultAvailable.V();
                        }

                    }
                    cardoffice->v_j.erase(cardoffice->v_j.begin());
                }
            }
}







WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ){
	this->prt = &prt;
	this->bank = &bank;
	this->numCouriers = numCouriers;
	c_array = new Courier*[numCouriers];
    for(int i = 0; i < numCouriers;i++){
    	c_array[i] = new Courier(prt,*this,i);
    }
    finishing = false;
    resultAvailable.P();
    lock_job.P();
}


WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){
	Args a;
	a.id = sid;
	a.amount = amount;
	a.type = 1;

	Job j(a);
	v_j.push_back(j);
	lock_job.V();
	prt->print(Printer::WATCardOffice,'C',sid,amount);
	resultAvailable.P();
	prt->print(Printer::WATCardOffice,'W');
	return j.result;

}
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
	Args a;
	a.id = sid;
	a.amount = amount;
	a.type = 2;
	a.ocard = card;

	Job j(a);
	v_j.push_back(j);
	lock_job.V();
	prt->print(Printer::WATCardOffice,'T',sid,amount);
	resultAvailable.P();
	prt->print(Printer::WATCardOffice,'W');
	return j.result;
}



void WATCardOffice::main(){
	prt->print(Printer::WATCardOffice,'S');
	while(true){
		_Accept(transfer,create){

		}or _Accept(~WATCardOffice){
			break;
		}
	}
}



WATCardOffice::Job * WATCardOffice::requestWork(){
	WATCardOffice::Job *j;
	while(v_j.empty()){
		bench.wait();
	}
	return j;
}