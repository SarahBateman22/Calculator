/**
 *\file expr.cpp
 *\brief Expression class
 *
 * Expression class contains implementations of every function for every class available
 */

#include "expr.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <map>


void Expr::pretty_print_at(std::ostream &o, precedence_t mode, bool let_parent, std::streampos strmpos){
    print(o);
}

void Expr::pretty_print(std::ostream &o){
    pretty_print_at(o, prec_none, NULL, NULL);
}

std::string Expr::to_pretty_string(){
    std::stringstream o("");
    this->pretty_print(o);
    return o.str();
}

//NUM ------------------------------------------------------------------------
/**
 * \brief Constructor for the Num class.
 * \param val The integer value of the Num object.
 * Initializes a Num object with the given integer value.
 */
Num::Num(int val) {
    this->val = val;
}

/**
 * \brief Implementation of the equals function for Num.
 * \param other The other expression to compare to.
 * \return True if the expressions are equal, false otherwise.
 * Checks if the current Num object is equal to another expression.
 */
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

/**
 * \brief Implementation of the interp function for Num.
 * \return The integer value of the Num object.
 * Evaluates the numeric literal and returns its integer value.
 */
int Num::interp() {
    return this->val;
}

/**
 * \brief Implementation of the has_variable function for Num.
 *
 * \return Always returns false.
 * Checks if the Num object contains any variables (always returns false for Num).
 */
bool Num::has_variable() {
    return false;
}

/**
 * \brief Implementation of the subst function for Num.
 * \param var The variable to replace.
 * \param replacement The replacement expression.
 * \return The new expression with the variable substituted.
 * Substitutes a variable in the Num object with a replacement expression.
 */
Expr* Num::subst(const std::string var, Expr* replacement){
    return this;
}

/**
 * \brief Implementation of the print function for Num.
 * \param stream The output stream to print to.
 * Prints the integer value of the Num object to the specified output stream.
 */
void Num::print(std::ostream& stream){
    stream << this->val;
}

//ADD ------------------------------------------------------------------------
/**
 * \brief Constructor for the Add class.
 *
 * Initializes an Add object with the given left and right expressions.
 *
 * \param lhs The left expression.
 * \param rhs The right expression.
 */
Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief Implementation of the equals function for Add.
 *
 * Checks if the current Add object is equal to another expression.
 *
 * \param other The other expression to compare to.
 * \return True if the expressions are equal, false otherwise.
 */
bool Add::equals(const Expr* other) {
    if (other != nullptr){
        const Add* otherAdd = dynamic_cast<const Add*>(other);
        
        if(otherAdd != nullptr){
            return this->lhs->equals(otherAdd->lhs) && this->rhs->equals(otherAdd->rhs);
        }
    }
    return false;
}

/**
 * \brief Implementation of the interp function for Add.
 *
 * Evaluates the addition of the left and right expressions and returns the result.
 *
 * \return The result of evaluating the addition.
 */
int Add::interp() {
    return this->lhs->interp() + this->rhs->interp();
}

/**
 * \brief Implementation of the has_variable function for Add.
 *
 * Checks if the Add object or its sub-expressions contain any variables.
 *
 * \return True if the expressions contain variables, false otherwise.
 */
bool Add::has_variable() {
    return this->lhs->has_variable() || this->rhs->has_variable();
}

/**
 * \brief Implementation of the subst function for Add.
 *
 * Substitutes a variable in the Add object or its sub-expressions with a replacement expression.
 *
 * \param var The variable to replace.
 * \param replacement The replacement expression.
 * \return The new expression with the variable substituted.
 */
Expr* Add::subst(const std::string var, Expr* replacement){
    return new Add(lhs->subst(var, replacement), rhs->subst(var, replacement));
}

/**
 * \brief Implementation of the print function for Add.
 *
 * Prints the addition expression to the specified output stream.
 *
 * \param stream The output stream to print to.
 */
void Add::print(std::ostream& stream){
    stream << "(";
        this->lhs->print(stream);
        stream << "+";
        this->rhs->print(stream);
        stream << ")";
}

/**
 * \brief Implementation of the pretty_print_at function for Add.
 *
 * Pretty prints the addition expression with a specified precedence mode to the output stream.
 *
 * \param o The output stream to print to.
 * \param mode The precedence mode for pretty printing.
 */
void Add::pretty_print_at(std::ostream &o, precedence_t mode, bool let_parent, std::streampos strmpos) {
    if (mode >= prec_add) {
        o << "(";
    }
    lhs->pretty_print_at(o, prec_add, true, strmpos);
    o << " + ";
    rhs->pretty_print_at(o, prec_none, false, strmpos);
    if (mode >= prec_add) {
        o << ")";
    }
}


//MULT -------------------------------------------------------------------
/**
 * \brief Constructor for the Mult class.
 *
 * Initializes a Mult object with the given left and right expressions.
 *
 * \param lhs The left expression.
 * \param rhs The right expression.
 */
Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief Implementation of the equals function for Mult.
 *
 * Checks if the current Mult object is equal to another expression.
 *
 * \param other The other expression to compare to.
 * \return True if the expressions are equal, false otherwise.
 */
bool Mult::equals(const Expr* other) {
    if (other != nullptr){
        const Mult* otherMult = dynamic_cast<const Mult*>(other);
        
        if(otherMult != nullptr){
            return this->lhs->equals(otherMult->lhs) && this->rhs->equals(otherMult->rhs);
        }
    }
    return false;
}

/**
 * \brief Implementation of the interp function for Mult.
 *
 * Evaluates the multiplication of the left and right expressions and returns the result.
 *
 * \return The result of evaluating the multiplication.
 */
int Mult::interp() {
    return this->lhs->interp() * this->rhs->interp();
}

/**
 * \brief Implementation of the has_variable function for Mult.
 *
 * Checks if the Mult object or its sub-expressions contain any variables.
 *
 * \return True if the expressions contain variables, false otherwise.
 */
bool Mult::has_variable() {
    return this->lhs->has_variable() || this->rhs->has_variable();
}

/**
 * \brief Implementation of the subst function for Mult.
 *
 * Substitutes a variable in the Mult object or its sub-expressions with a replacement expression.
 *
 * \param var The variable to replace.
 * \param replacement The replacement expression.
 * \return The new expression with the variable substituted.
 */
Expr* Mult::subst(const std::string var, Expr* replacement){
    return new Mult(lhs->subst(var, replacement), rhs->subst(var, replacement));
}

/**
 * \brief Implementation of the print function for Mult.
 *
 * Prints the multiplication expression to the specified output stream.
 *
 * \param stream The output stream to print to.
 */
void Mult::print(std::ostream& stream){
    stream << "(";
        this->lhs->print(stream);
        stream << "*";
        this->rhs->print(stream);
        stream << ")";
}

/**
 * \brief Implementation of the pretty_print_at function for Mult.
 *
 * Pretty prints the multiplication expression with a specified precedence mode to the output stream.
 *
 * \param o The output stream to print to.
 * \param mode The precedence mode for pretty printing.
 */
void Mult::pretty_print_at(std::ostream &o, precedence_t mode, bool let_parent, std::streampos strmpos) {
    if (mode >= prec_mult) {
        o << "(";
    }
    lhs->pretty_print_at(o, prec_mult, true, strmpos);
    o << " * ";
    rhs->pretty_print_at(o, prec_add, false, strmpos);
    if (mode >= prec_mult) {
        o << ")";
    }
}

//VAR -------------------------------------------------------------------------
/**
 * \brief Constructor for the Var class.
 *
 * Initializes a Var object with the given variable name.
 *
 * \param name The name of the variable.
 */
Var::Var(const std::string& name) {
    this->name = name;
}

/**
 * \brief Implementation of the equals function for Var.
 *
 * Checks if the current Var object is equal to another expression.
 *
 * \param other The other expression to compare to.
 * \return True if the expressions are equal, false otherwise.
 */
bool Var::equals(const Expr* other) {
    if (other != nullptr){
        const Var* otherVar = static_cast<const Var*>(other);
        
        if(otherVar != nullptr){
            return this->name == otherVar->name;
        }
    }
    return false;
}

/**
 * \brief Implementation of the interp function for Var.
 *
 * Throws a runtime error since Var objects do not have a defined value.
 *
 * \return This function always throws a runtime error.
 */
int Var::interp() {
    throw std::runtime_error("no value for variable");
}

/**
 * \brief Implementation of the has_variable function for Var.
 *
 * Checks if the Var object represents a variable (always returns true for Var).
 *
 * \return Always returns true.
 */
bool Var::has_variable() {
    return true;
}

/**
 * \brief Implementation of the subst function for Var.
 *
 * Substitutes a variable in the Var object with a replacement expression.
 *
 * \param var The variable to replace.
 * \param replacement The replacement expression.
 * \return The new expression with the variable substituted.
 */
Expr* Var::subst(const std::string var, Expr* replacement) {
    if (this->name == var) {
        return replacement;
    }
    else {
        return this;
    }
}

/**
 * \brief Implementation of the print function for Var.
 *
 * Prints the variable name to the specified output stream.
 *
 * \param stream The output stream to print to.
 */
void Var::print(std::ostream& stream){
    stream << this->name;
}

//_let -------------------------------------------------------------------------
/**
 * \brief Constructor for the Let class.
 *
 * Initializes a Let object with a given variable name, the value to be assigned to the variable, and the body expression where the variable is in scope.
 *
 * \param name The name of the variable.
 *
 * \param nameVal The expression whose value is to be assigned to the variable.
 * \param bodyExpr The body expression where the variable is used.
 */
Let::Let(std::string name, Expr *nameVal, Expr *bodyExpr){
    this->name = name;
    this->nameVal = nameVal;
    this->bodyExpr = bodyExpr;
}

/**
 * \brief Checks if this Let object is equal to another expression.
 *
 * Determines equality by comparing the variable name, the assigned value expression, and the body expression of the two Let objects.
 *
 * \param other The other expression to compare with this Let object.
 * \return True if both Let objects are equal, false otherwise.
 */
bool Let::equals(const Expr* other){
    if (other != nullptr) {
        const Let* otherLet = dynamic_cast<const Let*>(other);
           
        if (otherLet != nullptr) {
            return this->name == otherLet->name &&
                this->nameVal->equals(otherLet->nameVal) &&
                this->bodyExpr->equals(otherLet->bodyExpr);
        }
    }
    return false;
}

/**
 * \brief Evaluates the Let expression.
 *
 * Evaluates the expression assigned to the variable and substitutes this value into the body expression before evaluating the body expression itself.
 *
 * \return The result of evaluating the body expression with the variable substituted.
 */
int Let::interp() {
    //get the value of the name variable
    int nameValue = nameVal->interp();
    
    //put the value into a Num object to use further
    Num tempNum(nameValue);

    //substitute the interp'd value into the body of the let expression
    Expr* subBody = bodyExpr->subst(name, &tempNum);
    
    //get the result by interp'ing the body with the value sub'd in
    return subBody->interp();
}

/**
 * @brief Checks if the current `Let` object contains a variable.
 *
 * This method evaluates whether the `Let` object contains a variable by checking
 * both the name value (`nameVal`) and the body expression (`bodyExpr`). It returns
 * true if either `nameVal` or `bodyExpr` contains a variable, and false otherwise.
 *
 * @return bool True if either the name value or the body expression contains a variable,
 *              false if neither contains a variable.
 */
bool Let::has_variable(){
    //return if the name value or the body expression has a variable
    return (nameVal->has_variable() || bodyExpr-> has_variable());
}

/**
 * @brief Substitutes a variable within the `Let` object with a replacement expression.
 *
 * This method performs a substitution within the `Let` object. If the `Let` object's name
 * matches the specified variable (`var`), the method returns a new `Let` object with the
 * original name, but substitutes the variable within the `nameVal` only, leaving `bodyExpr` unchanged.
 * If the `Let` object's name does not match the specified variable, it returns a new `Let` object
 * where the variable is substituted both in `nameVal` and `bodyExpr` with the provided replacement expression.
 *
 * @param var The name of the variable to be substituted.
 * @param replacement The expression to replace the variable with.
 * @return Expr* A new `Let` object with the variable substituted in the `nameVal` and/or `bodyExpr`.
 */

Expr* Let::subst(const std::string var, Expr* replacement){
    //check if the name is the same as the name of the replacement var
    if (name == var) {
        return new Let(name, nameVal->subst(var, replacement), bodyExpr);
    }
    else {
        //if not then replace with subst in the name value and body
        return new Let(name, nameVal->subst(var, replacement), bodyExpr->subst(var, replacement));
    }
}

/**
 * \brief Prints the Let expression to an output stream.
 *
 * Formats the Let expression as a string and writes it to the given output stream, including the variable name, assigned value expression, and body expression.
 *
 * \param o The output stream to write to.
 */
void Let::print(std::ostream &o){
    //open parentheses and _let to start the expression
    o << "(_let ";
    
    //print var name
    o << this->name;
    o << "=";
    
    //print the value expression
    nameVal->print(o);
    
    o << " _in ";
    
    //print the body expression
    bodyExpr->print(o);
    
    //end the expression with a close parentheses
    o << ")";
}

/**
 * \brief Pretty prints the let expression with indentation based on its depth in the expression tree.
 *
 * This function pretty prints a let expression, taking into account its depth in the overall
 * expression tree for proper indentation. It uses recursion to print nested let expressions
 * correctly. The function is designed to visually represent the structure of nested let expressions
 * in a more readable and formatted way, especially when dealing with complex expressions.
 *
 * \param o The output stream to which the pretty-printed expression is written.
 * \param mode The precedence level of the current expression, used to determine if parentheses are needed.
 * \param let_parent A boolean indicating if the current let expression is nested within another let expression.
 * \param strmpos The stream position of the parent expression or the initial call to pretty_print_at, used to calculate indentation depth.
 *
 * The function starts by calculating its depth based on the stream position passed to it, which helps
 * in determining the correct amount of indentation for visually nested structures. It then prints the
 * let binding with proper alignment and recursively pretty prints the body of the let expression with
 * the adjusted stream position for further nested expressions.
 */
void Let::pretty_print_at(std::ostream &o, precedence_t mode, bool let_parent, std::streampos strmpos)  {
    
    std::streampos startPosition = o.tellp();
        
    std::streampos depth = startPosition-strmpos;
        
    if (let_parent) {
        o << "(";
    }
        
    o << "_let " << name << " = ";
        
    nameVal->pretty_print_at(o, prec_none, false, depth);
        
    o << "\n";
        
    std::streampos rc = o.tellp();
        
    o << std::string(depth, ' ') << " _in ";
       
    bodyExpr->pretty_print_at(o, prec_none, false, rc);

    if (let_parent) {
        o << ")";
    }
}
