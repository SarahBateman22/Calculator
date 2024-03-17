/**
 *\file cmdLine.hpp
 *\brief Command line header class
 *
 * Contains header signatures for cmdLine.cpp file
 */


#ifndef cmdLine_hpp
#define cmdLine_hpp

#include <stdio.h>

#endif /* cmdLine_hpp */

enum run_mode_t {
    do_nothing,
    do_test,
    do_interp,
    do_print,
    do_pretty_print
};

run_mode_t use_arguments(int argc, const char **argv);

