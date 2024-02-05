//
//  cmdLine.cpp
//  MSDscript
//
//  Created by Sarah Bateman on 1/11/24.
//

#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include "cmdLine.hpp"
#include <iostream>
#include <string>
#include <algorithm>


void use_arguments(int argc, const char **argv){
    //bool to keep track of if we have run tests before or not
    bool canRunTests = true;
    
    //need to look at all the arguments in order
    for(int i = 1; i < argc; i++){
        //if an argument is --help then it will print the available flag options
        if(std::string(argv[i]) == "--help"){
            std::cout << "Available flags:\n--test: run tests\n--help: this help text\n";
            exit(0);
        }
        
        //if --test is passed
        if(std::string(argv[i]) == "--test"){
            //and has never been passed before
            if(canRunTests){
                //run the tests
                //if any failed then print fail statement and exit
                if(Catch::Session().run(1, argv) != 0){
                    std::cerr << "Tests failed.\n";
                    exit(1);
                }
                //flip bool to false for future test flags passed
                canRunTests = false;
            }
            //if test flag has already been passed then print to cerr
            else if(!canRunTests){
            std::cerr << "Tests have already been ran.\n";
            exit(1);
            }
        }
        
        //handling if the argument is not a known flag
        else{
            std::cerr << "'" << std::string(argv[i]) << "' is an unknown argument. Please run again and enter '--help' for available tags.";
            exit(1);
        }
    }
}
