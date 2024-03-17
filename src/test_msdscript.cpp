//
//  test_msdscript.cpp
//  WorkingProject
//
//  Created by Sarah Bateman on 2/23/24.
//

#include <stdio.h>
#include "exec.h"
#include <iostream>
using namespace std;

std::string random_expr_string(int depth = 0) {
    if (depth > 10) {
        if (rand() % 2) {
            return std::string(1, static_cast<char>('a' + (rand() % 26)));
        } else {
            return std::to_string(rand() % 100);
        }
    }

    int choice = rand() % 5;
    switch(choice) {
        case 0:
            return std::to_string(rand() % 100);
        case 1:
            return random_expr_string(depth + 1) + " + " + random_expr_string(depth + 1);
        case 2:
            return random_expr_string(depth + 1) + " * " + random_expr_string(depth + 1);
        case 3:
            return std::string(1, static_cast<char>('a' + (rand() % 26)));
        case 4: {
            std::string var = std::string(1, static_cast<char>('a' + (rand() % 26)));
            std::string value = random_expr_string(depth + 1);
            std::string body = random_expr_string(depth + 1);
            return "_let " + var + "=" + value + " _in " + body;
        }
        default:
            return std::to_string(rand() % 100);
    }
}

int main(int argc, const char **argv) {
    //seeding the random num generator with the current time
       srand(static_cast<unsigned int>(time(0)));

    if(argc == 2){
        const char * const interp1_argv[] = { argv[1], "--interp" };
        const char * const print1_argv[] = { argv[1], "--print" };
        const char * const pprint1_argv[] = { argv[1], "--pretty-print" };
        
        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();
            std::cout << "Trying " << in << "\n";
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult print1_result = exec_program(2, print1_argv, in);
            ExecResult pprint1_result = exec_program(2, pprint1_argv, in);
            
            ExecResult interp_again = exec_program(2, interp1_argv, print1_result.out);
            if(interp_again.out != interp1_result.out){
                cout << "Different results for printed";
            }
            
            
        }
        return 0;
    }


    else if (argc == 3){
        const char * const interp1_argv[] = { argv[1], "--interp" };
        const char * const print1_argv[] = { argv[1], "--print" };
        const char * const pprint1_argv[] = { argv[1], "--pretty-print" };
        
        const char * const interp2_argv[] = { argv[2], "--interp" };
        const char * const print2_argv[] = { argv[2], "--print" };
        const char * const pprint2_argv[] = { argv[2], "--pretty-print" };
        
        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();
            std::cout << "Trying " << in << "\n";
            
            //testing interp
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult interp2_result = exec_program(2, interp2_argv, in);
            if (interp1_result.out != interp2_result.out){
                cout << "msdscript interp: " << interp1_result.out;
                cout << "tester interp: " << interp2_result.out << "\n";
                throw std::runtime_error("different results - interp\n");
            }
            
            //testing print
            ExecResult print1_result = exec_program(2, print1_argv, in);
            ExecResult print2_result = exec_program(2, print2_argv, in);
            if (print1_result.out != print2_result.out){
                cout << "msdscript print: " << print1_result.out;
                cout << "tester print: " << print2_result.out;
                throw std::runtime_error("different results - print");
            }
            
            //testing pretty print
            ExecResult pprint1_result = exec_program(2, pprint1_argv, in);
            ExecResult pprint2_result = exec_program(2, pprint2_argv, in);
            if (pprint1_result.out != pprint2_result.out){
                cout << "msdscript pretty print: " << pprint1_result.out;
                cout << "tester pretty print: " << pprint2_result.out;
                throw std::runtime_error("different results - pretty print");
            }
        }
        return 0;
        
    }

    //catch if the input is invalid
    else{
        cerr << "Usage: test_msdscript <msdscript_path> or test_msdscript <msdscript_path_1> <msdscript_path_2>";
        return 1;
    }
    
}
