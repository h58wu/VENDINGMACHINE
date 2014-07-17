#ifndef __MPRNG__
#define __MPRNG__

#include <uC++.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;					// direct access to std
#include <cstdlib>


_Monitor MPRNG {
  public:
    MPRNG( unsigned int seed = 1009 ) { srand( seed ); }    // set seed
    void seed( unsigned int seed ) { srand( seed ); }       // set seed
    unsigned int operator()() { return rand(); }            // [0,UINT_MAX]
    unsigned int operator()( unsigned int u ) { return operator()() % (u + 1); } // [0,u]
    unsigned int operator()( unsigned int l, unsigned int u ) { return operator()( u - l ) + l; } // [l,u]
};
#endif // MPRNG