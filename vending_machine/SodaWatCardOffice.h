#ifndef __SODAWATCARDOFFICE__
#define __SODAWATCARDPFFICE__
#include <uC++.h>
#include <uFuture.h>
#include <vector>
#include "SodaWatCard.h"
#include <uSemaphore.h>

using namespace std;


extern MPRNG mprng;
#include "SodaPrinter.h"
_Monitor Bank;


class Args{
public:
    unsigned int id;
    unsigned int amount;
    int type;       //1 stands for create, 2 stands for transfer
    WATCard* ocard;
};



_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };
    _Task Courier { 
    public:
        Printer *prt;
        Job * j;
        WATCardOffice * cardoffice;
        unsigned int cid; 
    private:
        void main();
    public:
        Courier(Printer &prt, WATCardOffice &cardoffice,unsigned int cid){
            this->prt = &prt;
            this->cardoffice = &cardoffice;
            this->cid = cid;
        }

        ~Courier(){
            prt->print(Printer::Courier,cid,'F');
        };



    };                 // communicates with bank

    Printer *prt;
    Bank *bank;
    unsigned int numCouriers;
    uCondition bench;
    vector<Job> v_j;
    bool finishing;
    Courier **c_array;
    void main();
    uSemaphore resultAvailable;
    uSemaphore lock_job;
    vector<WATCard*> record_wat;
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
    ~WATCardOffice(){
        finishing = true;
        lock_job.V(numCouriers);

        for(int i = 0; i < numCouriers;i++){
            delete c_array[i];
        }
        delete []c_array;
        prt->print(Printer::WATCardOffice,'F');
        for(int i = 0; i < record_wat.size();i++){
            delete record_wat[i];
        }
    };
};





#endif
