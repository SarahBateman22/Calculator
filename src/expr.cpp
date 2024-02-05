//
//  expr.cpp
//  WorkingProject
//
//  Created by Sarah Bateman on 1/19/24.
//

#include "expr.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <stdlib.h>

void Expr::pretty_print_at(std::ostream &o, precedence_t mode){
    print(o);
}

void Expr::pretty_print(std::ostream &o){
    pretty_print_at(o, prec_none);
}

std::string Expr::to_pretty_string(){
    std::stringstream o("");
    this->pretty_print(o);
    return o.str();
}

//NUM ------------------------------------------------------------------------
//constructor
Num::Num(int val) {
    this->val = val;
}

//implementing equals override for equals
bool Num::equals(const Expr* other) {
    //check that other is not null
       if (other != nullptr) {
           const Num* otherNum = dynamic_cast<const Num*>(other);
           
           //check that otherNum isn't null
           if (otherNum != nullptr) {
               //return if the values are the same or not
               return this->val == otherNum->val;
           }
       }
       
       return false;
   }

//implementing equals override for interp
int Num::interp() {
    return this->val;
}

//implementing override for has_variable
bool Num::has_variable() {
    return false;
}

//implementing override for subst
Expr* Num::subst(const std::string var, Expr* replacement){
    return this;
}

//implementing override for print
void Num::print(std::ostream& stream){
    stream << this->val;
}

//ADD ------------------------------------------------------------------------
//constructor
Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(const Expr* other) {
    if (other != nullptr){
        const Add* otherAdd = dynamic_cast<const Add*>(other);
        
        if(otherAdd != nullptr){
            return this->lhs->equals(otherAdd->lhs) && this->rhs->equals(otherAdd->rhs);
        }
    }
    return false;
}

int Add::interp() {
    return this->lhs->interp() + this->rhs->interp();
}

bool Add::has_variable() {
    return this->lhs->has_variable() || this->rhs->has_variable();
}

Expr* Add::subst(const std::string var, Expr* replacement){
    return new Add(lhs->subst(var, replacement), rhs->subst(var, replacement));
}

void Add::print(std::ostream& stream){
    stream << "(";
        this->lhs->print(stream);
        stream << "+";
        this->rhs->print(stream);
        stream << ")";
}

void Add::pretty_print(std::ostream &o) {
    pretty_print_at(o, prec_add);
}

void Add::pretty_print_at(std::ostream &o, precedence_t mode) {
    if (mode >= prec_add) {
        o << "(";
    }
    lhs->pretty_print_at(o, prec_add);
    o << " + ";
    rhs->pretty_print_at(o, prec_add);
    if (mode >= prec_add) {
        o << ")";
    }
}


//MULT -------------------------------------------------------------------
//constructor
Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(const Expr* other) {
    if (other != nullptr){
        const Mult* otherMult = dynamic_cast<const Mult*>(other);
        
        if(otherMult != nullptr){
            return this->lhs->equals(otherMult->lhs) && this->rhs->equals(otherMult->rhs);
        }
    }
    return false;
}

int Mult::interp() {
    return this->lhs->interp() * this->rhs->interp();
}

bool Mult::has_variable() {
    return this->lhs->has_variable() || this->rhs->has_variable();
}

Expr* Mult::subst(const std::string var, Expr* replacement){
    return new Mult(lhs->subst(var, replacement), rhs->subst(var, replacement));
}

void Mult::print(std::ostream& stream){
    stream << "(";
        this->lhs->print(stream);
        stream << "*";
        this->rhs->print(stream);
        stream << ")";
}

void Mult::pretty_print(std::ostream &o) {
    pretty_print_at(o, prec_mult);
}

void Mult::pretty_print_at(std::ostream &o, precedence_t mode) {
    if (mode >= prec_mult) {
        o << "(";
    }
    lhs->pretty_print_at(o, prec_mult);
    o << " * ";
    rhs->pretty_print_at(o, prec_mult);
    if (mode >= prec_mult) {
        o << ")";
    }
}

//VAR -------------------------------------------------------------------------
//constructor
Var::Var(const std::string& name) {
    this->name = name;
}

bool Var::equals(const Expr* other) {
    if (other != nullptr){
        const Var* otherVar = static_cast<const Var*>(other);
        
        if(otherVar != nullptr){
            return this->name == otherVar->name;
        }
    }
    return false;
}

int Var::interp() {
    throw std::runtime_error("no value for variable");
}

bool Var::has_variable() {
    return true;
}

Expr* Var::subst(const std::string var, Expr* replacement) {
    if (this->name == var) {
        return replacement;
    }
    else {
        return this;
    }
}

void Var::print(std::ostream& stream){
    stream << this->name;
}
