# Makefile - builds hw1 project
#
# to build enter 'make build'
# to run enter 'make run'
# to clear .o and executable files enter 'make clean'
#
# targets:
# build - builds all files
# clean - deletes all .o files

CXX = c++
CXXFLAGS = --std=c++11 -c

# the prerequisite of the run target is the buildFile (executable file) 
run: msdscript
	./msdscript

test: msdscript
	./msdscript --test

build: msdscript

msdscript: main.o cmdLine.o expr.o tests.o
	$(CXX) main.o cmdLine.o expr.o tests.o -o msdscript

clean: 
	rm -f *.o *.out *.gch msdscript

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

cmdLine.o: cmdLine.cpp cmdLine.hpp
	$(CXX) $(CXXFLAGS) cmdLine.cpp cmdLine.hpp 

expr.o:	expr.cpp expr.hpp
	$(CXX) $(CXXFLAGS) expr.cpp expr.hpp

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) tests.cpp

catch.o: catch.h
	$(CXX) $(CXXFLAGS) catch.h
