//
//  parse.cpp
//  WorkingProject
//
//  Created by Sarah Bateman on 2/16/24.
//

#include "expr.hpp"
#include "parse.hpp"
#include <iostream>

/**
 * \brief Parses an expression from an input stream.
 * \param in The input stream to parse.
 * \return A pointer to the parsed expression.
 * \throws std::runtime_error If the input contains invalid expressions or is not fully consumed.
 *
 * This function delegates to specific parsing functions based on the input's initial characters.
 * It ensures that the entire input stream is consumed and valid as per the parsing rules.
 */
Expr *parse(std::istream &in) {
    Expr* e;
    //parse expression and skip whitespace
    e = parse_expr(in);
    skip_whitespace(in);
    
    //if it's not the end of the file then throw an errpr
    if ( !in.eof() ) {
        throw std::runtime_error("Invalid input") ;
    }
    return e;
}

/**
 * \brief Consumes whitespace characters from the input stream.
 * \param in The input stream from which whitespace will be consumed.
 *
 * This function iterates over the input stream and consumes all leading whitespace characters
 * until a non-whitespace character is encountered.
 */
//from lecture 10 slides
void skip_whitespace(std::istream &in) {
    //forever loop
    while (1) {
        //check what the next value in the instream is
        int c = in.peek();
        //if it's not a space then break out of this method
        if (!isspace(c))
            break;
        //if it is a space then consume
        consume(in, c);
    }
}

/**
 * \brief Parses a numeric expression from an input stream.
 * \param in The input stream to parse.
 * \return A pointer to the Num expression representing the parsed number.
 * \throws std::runtime_error If the input does not start with a digit after an optional leading '-'.
 *
 * Handles both positive and negative integers. It checks for a leading '-'
 * to determine negativity and constructs a Num expression based on the parsed number.
 */
//from lecture 10 slides
Expr *parse_num(std::istream &in) {
    //initialize the return int as 0
    int n = 0;
    bool negative = false;
    //check if the first value is a -, if it is then flip the boolean to true and consume it
    if (in.peek() == '-') {
        negative = true;
        consume (in, '-');
        //if the next input is not a digit then throw an error
        if(!isdigit(in.peek())){
            throw std::runtime_error("Invalid input") ;
        }
    }
    //forever loop
    while (1) {
        //check the next input
        int c = in.peek();
        if (isdigit(c))
        {
            //consume it and set the return int to the number
            consume(in, c);
            n = n*10 + (c - '0');
        }
        else
            break;
    }
    //if it's negative then make it negative
    if (negative)
        n = n * -1;
    return new Num(n);
}

/**
 * \brief Parses an additive expression from an input stream.
 * \param in The input stream to parse.
 * \return A pointer to the parsed expression, which may be a Num, Var, Add, or other expression type.
 *
 * Attempts to parse an expression that may include addition. If a '+' is encountered,
 * it parses both sides of the addition and returns an Add expression.
 */
//from lecture 10 slides
Expr *parse_expr(std::istream &in) {
    Expr *e;
    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        Expr *rhs = parse_expr(in);
        return new Add(e, rhs);
    }
    else{
        return  e;
    }
}

/**
 * \brief Parses a multiplicative expression from an input stream.
 * \param in The input stream to parse.
 * \return A pointer to the parsed expression, potentially a Mult expression.
 *
 * Similar to parse_expr, but for multiplication. If a '*' is encountered, it parses both operands
 * and returns a Mult expression.
 */
//from lecture 10 slides (mostly)
Expr *parse_addend(std::istream &in) {
    Expr *e;
    e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        skip_whitespace(in) ;
        Expr *rhs = parse_addend(in);
        return new Mult(e, rhs);
    }
    else{
        return e ;
    }
}

/**
 * \brief Consumes the next character in the input stream if it matches the expected character.
 * \param in The input stream.
 * \param expected The character expected to be next in the stream.
 * \throws std::runtime_error If the next character in the stream does not match the expected character.
 *
 * A utility used to consume specific characters, such as operators or parentheses,
 * as part of the parsing process.
 */
void consume(std::istream &in, int expected) {
    //get (not peek) the next input which clears it from the stream
    int c = in.get();
    //if it's not what's expected then throw an exception
    if (c!=expected) {
        throw std::runtime_error("consume mismatch");
    }
}

/**
 * \brief Parses a multiplicand from an input stream.
 * \param in The input stream to parse.
 * \return A pointer to the parsed expression.
 * \throws std::runtime_error If the input is invalid for a multiplicand.
 *
 * A multiplicand can be a number, variable, let-expression, or a parenthesized expression.
 * Delegates to the appropriate parsing function based on the next character.
 */
Expr *parse_multicand(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();
    //if it's straight to a - or number then pass to parse_num
    if ((c == '-') || isdigit(c)){
        return parse_num(in);
    }
    
    //if it's a variable then send to parse_var
    else if (isalpha(c)) {
        return parse_variable(in);
    }
    
    //if it starts with an underscore it's a let statement
    else if (c == '_'){
        return parse_let(in);
    }

    else if (c == '(') {
        //consume parentheses
        consume(in, '(');
        //parse the internal expression
        Expr *e = parse_expr(in);
        skip_whitespace(in);
        //if the thing after the expression isn't a close parentheses throw an exception
        c = in.get();
        if (c != ')'){
            throw std::runtime_error("Missing close parentheses");
        }
        return e;
    }
    
    //if it's not any of the things above then throw an error
    else {
        consume(in, c);
        throw std::runtime_error("Invalid input");
    }
}

/**
 * \brief Parses a variable from an input stream.
 * \param in The input stream to parse.
 * \return A pointer to a Var expression representing the parsed variable.
 *
 * Constructs a variable name by consuming consecutive alphabetical characters.
 */
Expr *parse_variable(std::istream &in) {
    std::string var;
    //forever loop
    while (true) {
        int c = in.peek();
        //check that the char is valid
        if (isalpha(c)) {
            consume(in, c);
            //add the char it's on to the var string
            var += static_cast<char>(c);
        }
        else {
            break;
        }
    }
    //return the var
    return new Var(var);
}

/**
 * \brief Parses the name of a variable in a let statement from an input stream.
 * \param in The input stream to parse.
 * \return The name of the variable as a string.
 *
 * Similar to parse_variable, but specifically used within the context of parsing let-statements
 * to extract the variable name.
 */
std::string parse_var_name(std::istream &in){
    std::string name;
    //forever loop
    while (true) {
        int c = in.peek();
        //check that the char is valid
        if (isalpha(c)) {
            consume(in, c);
            //add the char it's on to the var string
            name += static_cast<char>(c);
        }
        else {
            break;
        }
    }
    return name;
}

/**
 * \brief Parses a let-expression from an input stream.
 * \param in The input stream to parse.
 * \return A pointer to a Let expression constructed from the parsed components.
 * \throws std::runtime_error If the input does not conform to the expected let-expression syntax.
 *
 * A let-expression binds a variable name to an expression and then uses that binding
 * within another expression. Parses the "_let" keyword, variable name,
 * binding expression, "_in" keyword, and body expression.
 */
Expr* parse_let(std::istream &in) {
    //need to consume "_let"
    std::string word = "_let";
    //check and consume each char
    for(char c : word){
        if (in.get() != c) {
            throw std::runtime_error("Not a let statement (_let)");
        }
    }
    skip_whitespace(in);
    
    //get the name of the variable
    std::string name = parse_var_name(in);
    skip_whitespace(in);
    
    //consume in the =
    consume(in, '=');
    skip_whitespace(in);
    
    //parse the rhs of the let statement
    Expr* nameVal = parse_expr(in);
    skip_whitespace(in);
    
    //consume _in
    std::string wordIn = "_in";
    //check and consume each char
    for(char c : wordIn){
        if (in.get() != c) {
            throw std::runtime_error("Not a let statement (_in)");
        }
    }
    skip_whitespace(in);
    
    //parse the body of the let statement
    Expr* bodyExpr = parse_expr(in);
    skip_whitespace(in);
    
    //return the parts together in a new let expression
    return new Let(name, nameVal, bodyExpr);
}

/**
 * \brief Parses an expression from a string.
 * \param s The string to parse.
 * \return A pointer to the parsed expression.
 *
 * Wraps the parse function to allow parsing from a string by converting it
 * to an std::istringstream and passing it to the parse function.
 */
Expr* parse_str(const std::string& s) {
    std::istringstream in(s);
    return parse(in);
}

