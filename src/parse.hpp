//
//  parse.hpp
//  WorkingProject
//
//  Created by Sarah Bateman on 2/16/24.
//

#ifndef parse_hpp
#define parse_hpp

#include <stdio.h>

#endif /* parse_hpp */

Expr *parse_multicand(std::istream &in);

Expr *parse_num(std::istream &inn);

Expr *parse_expr(std::istream &in);

Expr *parse_addend(std::istream &in);

void consume(std::istream &in, int expected);

void skip_whitespace(std::istream &in);

Expr *parse(std::istream &in);

Expr* parse_str(const std::string& s);

Expr *parse_variable(std::istream &in);

std::string parse_var_name(std::istream &in);

Expr* parse_let(std::istream &in);
