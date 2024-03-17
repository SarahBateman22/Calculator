/**
 *\file cmdLine.cpp
 *\brief Command line class
 *
 * Command line class handles arguments passed in when executable is ran. 
 */

//#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include "cmdLine.hpp"
#include <iostream>
#include <string>
#include <algorithm>

run_mode_t use_arguments(int argc, const char **argv){
    //initialize the run mode as nothing
    run_mode_t mode = do_nothing;
    
    //need to look at all the arguments in order
    for(int i = 1; i < argc; i++){
        std::string argPassed = argv[i];
        
        //if an argument is --help then it will print the available flag options
        if(argPassed == "--help"){
            std::cout << "Available flags:\n--test: run tests\n--help: this help text\n--interp: find the value of a statement\n--print: print out the statement\n";
            exit(0);
        }
        
        else if(argPassed == "--test"){
            mode = do_test;
        }
        
        else if (argPassed == "--interp") {
            mode = do_interp;
        }
        else if (argPassed == "--print") {
            mode = do_print;
        }
        else if (argPassed == "--pretty-print") {
            mode = do_pretty_print;
        }
        
        //handling if the argument is not a known flag
        else{
            std::cerr << "'" << argPassed << "' is an unknown argument. Please run again and enter '--help' for available tags.";
            exit(1);
        }
    }
    return mode;
}
