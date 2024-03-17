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

#to make documentation files
doc: msdscript
	cd Documentation && doxygen

# the prerequisite of the run target is the buildFile (executable file) 
run: msdscript
	./msdscript
	
# random gen test with path
test_msdscript: test_msdscript.o exec.o expr.o
		$(CXX) expr.o exec.o test_msdscript.o -o test_msdscript

test: msdscript
	./msdscript --test

build: msdscript

msdscript: main.o cmdLine.o expr.o tests.o parse.o
	$(CXX) main.o cmdLine.o expr.o tests.o parse.o -o msdscript

clean: 
	rm -f *.o *.out *.gch msdscript test_msdscript

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
	
exec.o: exec.cpp exec.h
	$(CXX) $(CXXFLAGS) exec.cpp exec.h
		
test_msdscript.o: test_msdscript.cpp
	$(CXX) $(CXXFLAGS) test_msdscript.cpp

parse.o: parse.cpp parse.hpp
	$(CXX) $(CXXFLAGS) parse.cpp
