#ifndef __SODAWATCARD__
#define __SODAWATCARD__
#include <uC++.h>
#include <uFuture.h>

class WATCard {
    WATCard( const WATCard & );            // prevent copying
    WATCard &operator=( const WATCard & );
    unsigned int balance;
  public:
    WATCard();
    typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

#endif