#include <uC++.h>
#include <iostream>
#include <fstream>
#include <limits>					// numeric_limits
using namespace std;
#include <sstream>					// direct access to std
#include <cstdlib>
#include "SodaBank.h"
#include "MPRNG.h"
#include "SodaNameServer.h"
#include "SodaParent.h"
#include "SodaStudent.h"
#include "SodaWatCard.h"
#include "SodaWatCardOffice.h"
#include "SodaBottlingPlant.h"
#include "SodaPrinter.h"
#include "SodaVendingMachine.h"


struct ConfigParms {
    unsigned int sodaCost;                 // MSRP per bottle
    unsigned int numStudents;              // number of students to create
    unsigned int maxPurchases;             // maximum number of bottles a student purchases
    unsigned int numVendingMachines;       // number of vending machines
    unsigned int maxStockPerFlavour;       // maximum number of bottles of each flavour stocked
    unsigned int maxShippedPerFlavour;     // number of bottles of each flavour in a shipment
    unsigned int timeBetweenShipments;     // length of time between shipment pickup
    unsigned int parentalDelay;            // length of time between cash deposits
    unsigned int numCouriers;              // number of couriers in the pool
}cp;


static bool comments( ifstream &in, string &name ) {
    for ( ;; ) {
	in >> name;
      if ( in.fail() ) return true;
      if ( name.substr(0,1) != "#" ) break;
	in.ignore( numeric_limits<int>::max(), '\n' ); // ignore remainder of line
    } // for
    return false;
} // comments

// Process the configuration file to set the parameters of the simulation.
void processConfigFile( const char *configFile, ConfigParms &cparms ) {
    const unsigned int Parmnum = 9;
    struct {
        const char *name;
        bool used;
        unsigned int *value;
    } static parms[Parmnum] = {
        { "SodaCost", false, &cparms.sodaCost },
        { "NumStudents", false, &cparms.numStudents },
        { "MaxPurchases", false, &cparms.maxPurchases },
        { "NumVendingMachines", false, &cparms.numVendingMachines },
        { "MaxStockPerFlavour", false, &cparms.maxStockPerFlavour },
        { "MaxShippedPerFlavour", false, &cparms.maxShippedPerFlavour },
        { "TimeBetweenShipments", false, &cparms.timeBetweenShipments },
        { "ParentalDelay", false, &cparms.parentalDelay },
        { "NumCouriers", false, &cparms.numCouriers },
    };
    string name;
    unsigned int value, cnt, posn;
    unsigned int numOfParm = 0;

    try {
        ifstream in( configFile );			// open the configuration file for input

	for ( cnt = 0 ; cnt < Parmnum; cnt += 1 ) {	// parameter names can appear in any order
	  if ( comments( in, name ) ) break;		// eof ?
	    for ( posn = 0; posn < Parmnum && name != parms[posn].name; posn += 1 ); // linear search
	  if ( posn == Parmnum ) break;			// configuration not found ?
	  if ( parms[posn].used ) break;		// duplicate configuration ?
	    in >> value;
	  if ( in.fail() ) break;
	    in.ignore( numeric_limits<int>::max(), '\n' ); // ignore remainder of line
	    numOfParm += 1;
	    parms[posn].used = true;
	    *parms[posn].value = value;
	} // for

	if ( numOfParm != Parmnum ) {
	    cerr << "Error: file \"" << configFile << "\" is corrupt." << endl;
	    exit( EXIT_FAILURE );
	} // if
	if ( ! comments( in, name ) ) {			// ! eof ?
	    cerr << "Error: file \"" << configFile << "\" has extraneous data." << endl;
	    exit( EXIT_FAILURE );
	} // if
    } catch( uFile::Failure ) {
        cerr << "Error: could not open input file \"" << configFile << "\"" << endl;
        exit( EXIT_FAILURE );    
    } // try
} // processConfigFile

// Local Variables: //
// compile-command: "make" //
// End: //

MPRNG mprng;



bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

enum { sizeDeflt = 20, codeDeflt = 5 };			// global defaults

void usage( char *argv[] ) {
    cerr << "Usage: ./soda soda.config seed"<<endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage



void uMain::main(){
	int seed = getpid();	// default value
    istream *infile; 				// default value
    char * s = "soda.config";

    switch ( argc ) {
      case 4:
      	usage(argv);	
      case 3:
        if ( ! convert( seed, argv[2] ) || seed < 0 ) {	// invalid integer ?
	    	usage( argv );
		} // if
        // FALL THROUGH
      case 2:
		s = argv[1];
        // FALL THROUGH
      case 1:						// all defaults
        break;
      default:						// wrong number of options
	usage( argv );
    } // switch
    
    processConfigFile(s,cp);

    mprng.seed(seed);

	unsigned int sodaCost           =    cp.sodaCost  ;
	unsigned int numStudents         =    cp.numStudents    ;
	unsigned int maxPurchases         =   cp.maxPurchases   ;
	unsigned int numVendingMachines    =  cp.numVendingMachines  ;
	unsigned int maxStockPerFlavour    =  cp.maxStockPerFlavour    ;
	unsigned int maxShippedPerFlavour   = cp.maxShippedPerFlavour;
	unsigned int timeBetweenShipments  =  cp.timeBetweenShipments;   
	unsigned int parentalDelay         =  cp.parentalDelay  ;  
	unsigned int numCouriers           =  cp.numCouriers;


	Printer *p = new Printer(numStudents,numVendingMachines,numCouriers);
	Bank *b = new Bank(numStudents);
	Parent * parent = new Parent(*p,*b,numStudents,parentalDelay);
	NameServer * name = new NameServer(*p,numVendingMachines,numStudents);
	WATCardOffice * w = new WATCardOffice(*p,*b,numCouriers);
	Student * s_array[numStudents];
    for(int i = 0; i < numStudents;i++){
    	s_array[i] = new Student(*p,*name,*w,i,maxPurchases);
    }

	VendingMachine   *v_array[numVendingMachines];
    for(int i = 0; i < numVendingMachines;i++){
    	v_array[i] = new VendingMachine(*p,*name,i,sodaCost,maxStockPerFlavour);
    }
	BottlingPlant * bp = new BottlingPlant(*p,*name,numVendingMachines,maxShippedPerFlavour,maxStockPerFlavour,timeBetweenShipments);

	
	for(int i = 0; i < numStudents;i++){
    	delete s_array[i];
    }

	delete bp;

	for(int i = 0; i < numVendingMachines;i++){
    	delete v_array[i];
    }

	
	delete w;
	delete name;
	delete parent;
	delete b;
	delete p;
}


