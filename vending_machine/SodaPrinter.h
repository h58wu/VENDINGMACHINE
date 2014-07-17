#ifndef __A6PRINTER__
#define __A6PRINTER__

#include <vector>
using namespace std;

_Monitor Printer {
	int total;
	int numStudents;
	int numCouriers;
	int numVendingMachines;
	
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
    ~Printer();
	private:
		struct info {
		int id;
		Kind kind;
		char state;
		int value1;
		int value2; 
		};
		vector<info> v;
		bool checkKind(Kind kind);
		bool checkKind(Kind kind, int id );
		void printHelper(info i) ;
};

#endif