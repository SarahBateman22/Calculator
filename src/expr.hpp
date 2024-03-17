/**
 *\file expr.hpp
 *\brief Expression header class
 *
 * Contains header signatures for expr.cpp file
 */

#ifndef expr_hpp
#define expr_hpp

#include <stdio.h>
#include <string>
#include <sstream>

#endif /* expr_hpp */

typedef enum {
    prec_none = 0,      // = 0
  prec_add = 1,       // = 1
  prec_mult = 2       // = 2
} precedence_t;


class Expr {
public:
    // =0 means each subclass must override
    virtual bool equals(const Expr* other) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(const std::string var, Expr* replacement) = 0;
    virtual void print(std::ostream&) = 0;
    std::string to_string() {
        std::stringstream st("");
        this->print(st);
        return st.str();
    }
    void pretty_print(std::ostream&);
    virtual void pretty_print_at(std::ostream &o, precedence_t mode, bool let_parent, std::streampos strmpos);
    std::string to_pretty_string();
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(const Expr* other);
    int interp();
    bool has_variable();
    Expr* subst(const std::string var, Expr* replacement);
    void print(std::ostream&);
};

class Add : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(const Expr* other);
    int interp();
    bool has_variable();
    Expr* subst(const std::string var, Expr* replacement);
    void print(std::ostream&);
    void pretty_print_at(std::ostream &o, precedence_t mode, bool let_parent, std::streampos strmpos);
};

class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(const Expr* other);
    int interp();
    bool has_variable();
    Expr* subst(const std::string var, Expr* replacement);
    void print(std::ostream&);
    void pretty_print_at(std::ostream &o, precedence_t mode, bool let_parent, std::streampos strmpos);
};

class Var : public Expr {
public:
    std::string name;
    Var(const std::string& name);
    bool equals(const Expr* other) override;
    int interp() override;
    bool has_variable() override;
    Expr* subst(const std::string var, Expr* replacement) override;
    void print(std::ostream&) override;
};

class Let : public Expr {
public:
    std::string name;
    Expr *nameVal;
    Expr *bodyExpr;
    Let(const std::string name, Expr *nameVal, Expr *bodyExpr);
    bool equals(const Expr* other) override;
    int interp() override;
    bool has_variable() override;
    bool has_variable_excluding(const Expr* expr, const std::string& excludeVar);
    Expr* subst(const std::string var, Expr* replacement) override;
    void print(std::ostream &o) override;
    void pretty_print_at(std::ostream &ostream, precedence_t prec, bool let_parent, std::streampos strmpos);
};
