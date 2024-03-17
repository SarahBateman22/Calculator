/**
 *\mainpage MSDscript
 *\author Sarah Bateman
 *\Date 02/06/2024*
 *\brief main page
 * main page 
 */

#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include <algorithm>

#include "cmdLine.hpp"
#include "expr.hpp"
#include "catch.h"
#include "parse.hpp"

int main(int argc, const char **argv) {
    run_mode_t mode = use_arguments(argc, argv);

    switch (mode) {
        case do_test: {
            //if tests fail it will return 1, if they all pass it will break out and return 0
            if(Catch::Session().run(1, argv) != 0){
                std::cerr << "Tests failed.\n";
                exit(1);
            }
        }
            break;
        case do_interp: {
            Expr *expr = parse(std::cin);
            std::cout << expr->interp() << std::endl;
            break;
        }
        case do_print: {
            Expr *expr = parse(std::cin);
            expr->print(std::cout);
            std::cout << std::endl;
            break;
        }
        case do_pretty_print: {
            Expr *expr = parse(std::cin);
            std::cout << expr->to_pretty_string() << std::endl;
            break;
        }
        case do_nothing: {
        default:
            std::cerr << "No valid mode selected. Use --help for options." << std::endl;
            return 1;
        }
    }
    return 0;
}

