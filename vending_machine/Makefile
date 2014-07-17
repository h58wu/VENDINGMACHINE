CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = SodaBank.o SodaNameServer.o SodaParent.o SodaMain.o SodaStudent.o SodaWatCard.o SodaWatCardOffice.o SodaBottlingPlant.o SodaPrinter.o SodaTruck.o SodaVendingMachine.o
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = soda

.PHONY : clean

all : ${EXEC}					# build all elsecutables


${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@




${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} ImplType
