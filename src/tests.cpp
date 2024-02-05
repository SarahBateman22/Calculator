//
//  tests.cpp
//  WorkingProject
//
//  Created by Sarah Bateman on 1/21/24.
//

#include <stdio.h>
#include "expr.hpp"
#include "catch.h"
#include <iostream>


TEST_CASE("Num Class") {
    
    SECTION("Equals"){
        CHECK( (new Num(2))->equals(new Num(2)) == true);
        CHECK( (new Num(01))->equals(new Num(1)) == true);
        CHECK( (new Num(01))->equals(nullptr) == false);
        CHECK( (new Num(-5))->equals( new Num(-5)) == true);
        CHECK( (new Num(-5))->equals( new Num(5)) == false);
    }
    
    SECTION("Interp"){
        CHECK( (new Num(3))->interp()== 3 );
        CHECK( (new Num(0))->interp()== 0 );
        CHECK( (new Num(-500))->interp()== -500 );
        CHECK( (new Num(2))->interp()== 2 );
        CHECK( (new Num(1000000000))->interp()== 1000000000 );
    }
    
    SECTION("Has_Variable"){
        CHECK( (new Num(3))->has_variable()== false );
        CHECK( (new Num(0))->has_variable()== false );
        CHECK( (new Num(-500))->has_variable()== false );
        CHECK( (new Num(2))->has_variable()== false );
        CHECK( (new Num(1000000000))->has_variable()== false );
    }
    
    SECTION("Subst"){
        CHECK( (new Num(3))->subst("anyVar", new Num(5))->equals(new Num(3)));
        CHECK( (new Num(0))->subst("anyVar", new Num(6))->equals(new Num(0)));
        CHECK( (new Num(-500))->subst("anyVar", new Var("secondVar"))->equals(new Num(-500)));
        CHECK( (new Num(2))->subst("anyVar", new Mult( new Num(5), new Num (6)))->equals(new Num(2)));
        CHECK( (new Num(1000000000))->subst("anyVar", new Num(0))->equals(new Num(1000000000)));
    }
    
    SECTION("To_String"){
        CHECK( (new Num(10))->to_string() == "10" );
        CHECK( (new Num(0))->to_string() == "0" );
        CHECK( (new Num(1000000000))->to_string() == "1000000000" );
        CHECK( (new Num(-5))->to_string() == "-5" );
        CHECK( (new Num(02))->to_string() == "2" );
    }
}


TEST_CASE("Add Class") {
    
    SECTION("Equals"){
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))== true);
        CHECK( (new Add(new Num(1),new Num(3)))->equals(new Add(new Num(2),new Num(3)))== false);
        CHECK( (new Add(new Num(0),new Num(0)))->equals(new Add(new Num(0),new Num(0)))== true);
        CHECK( (new Add(new Num(-10),new Num(-5)))->equals(new Add(new Num(-10),new Num(-5)))== true);
        CHECK( (new Add(new Num(0),new Var("var")))->equals(new Add(new Num(0),new Num(0)))== false);
        
    }
    
    SECTION("Interp"){
        CHECK( (new Add(new Add(new Num(10), new Num(15)), new Add(new Num(20),new Num(20)))) ->interp()== 65);
        CHECK( (new Add(new Num(3), new Num(2))) ->interp()== 5 );
        CHECK( (new Add(new Num(-1),new Num(1)))->interp() == 0);
        CHECK( (new Add(new Num(-10),new Num(2)))->interp() == -8);
        CHECK( (new Add(new Num(0),new Num(0)))->interp() == 0);
    }
    
    SECTION("Has_Variable"){
        CHECK( (new Add(new Var("&"), new Num(1)))->has_variable() == true );
        CHECK( (new Add(new Var("one"), new Var("two")))->has_variable() == true );
        CHECK( (new Add(new Var("x"), new Var("y")))->has_variable() == true );
        CHECK( (new Add(new Num(0), new Num(1)))->has_variable() == false );
        CHECK( (new Add(new Num(-1), new Num(1)))->has_variable() == false );
    }
    
    SECTION("Subst"){
        CHECK( (new Add(new Num(2), new Num(1)))->subst("var", new Num(8))->equals(new Add(new Num(2), new Num(1))) );
        CHECK( (new Add(new Var("var"), new Num(1)))->subst("var", new Num(8))->equals(new Add(new Num(8), new Num(1))) );
        CHECK( (new Add(new Var("var"), new Var("var")))->subst("var", new Num(0))->equals(new Add(new Num(0), new Num(0))) );
        CHECK( (new Add(new Var("%"), new Num(10)))->subst("%", new Var(")"))->equals(new Add(new Var(")"), new Num(10))) );
        CHECK( (new Add(new Var("var"), new Num(1)))->subst("variable", new Num(8))->equals(new Add(new Var("var"), new Num(1))) );
    }
    
    SECTION("To_String"){
        CHECK( (new Add(new Num(1), new Num(1))) -> to_string() == "(1+1)");
        CHECK( (new Add(new Num(0), new Num(10))) -> to_string() == "(0+10)");
        CHECK( (new Add(new Num(-2), new Num(-4))) -> to_string() == "(-2+-4)");
        CHECK( (new Add(new Var("x"), new Num(1))) -> to_string() == "(x+1)");
        CHECK( (new Add(new Num(1), new Var("12"))) -> to_string() == "(1+12)");
    }
    
    SECTION("Pretty_Print"){
        CHECK ( (new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
        //failing below
        CHECK ( (new Add(new Num(10), new Add(new Num(4), new Num(2))))->to_pretty_string() ==  "10 + 4 + 2" );
        CHECK ( (new Add(new Num(1), new Num(1)))->to_pretty_string() ==  "1 + 1" );
        CHECK ( (new Add(new Add(new Num(-4), new Num(3)), new Add(new Num(2), new Num(-1))) )->to_pretty_string() ==  "(-4 + 3) + (2 + -1)" );
        CHECK ( (new Add(new Var("sarah"), new Var("b")))->to_pretty_string() ==  "sarah + b" );
    }
}

TEST_CASE("Mult Class") {
    
    SECTION("Equals"){
        CHECK( (new Add(new Num(3),new Num(-5)))->equals(new Mult(new Num(3),new Num(-5)))== false);
        CHECK( (new Mult(new Num(1),new Num(3)))->equals(new Mult(new Num(1),new Num(3)))== true);
        CHECK( (new Mult(new Num(1),new Num(3)))->equals(new Mult(new Num(2),new Num(3)))== false);
        CHECK( (new Mult(new Num(0),new Num(3)))->equals(new Mult(new Num(0),new Num(3)))== true);
        CHECK( (new Mult(new Num(100000000),new Num(3)))->equals(new Mult(new Num(100000000),new Num(3)))== true);
    }
    
    SECTION("Interp"){
        CHECK( (new Mult(new Num(3), new Num(2))) ->interp()== 6 );
        CHECK( (new Mult(new Num(1), new Num(0))) ->interp()== 0 );
        CHECK( (new Mult(new Num(10), new Num(200))) ->interp()== 2000 );
        CHECK( (new Mult(new Num(-1), new Num(2))) ->interp()== -2 );
        CHECK( (new Mult(new Num(-4), new Num(-5))) ->interp()== 20 );
    }
    
    SECTION("Has_Variable"){
        CHECK( (new Mult(new Num(2), new Var("Sarah")))->has_variable() == true );
        CHECK( (new Mult(new Num(2), new Num(1)))->has_variable() == false );
        CHECK( (new Mult(new Num(0), new Num(0)))->has_variable() == false );
        CHECK( (new Mult(new Num(2), new Var("#")))->has_variable() == true );
        CHECK( (new Mult(new Var("Sarah"), new Var("Bateman")))->has_variable() == true );
    }
    
    SECTION("Subst"){
        CHECK( (new Mult(new Num(2), new Num(1)))->subst("var", new Num(8))->equals(new Mult(new Num(2), new Num(1))) );
        CHECK( (new Mult(new Var("var"), new Num(1)))->subst("var", new Num(8))->equals(new Mult(new Num(8), new Num(1))) );
        CHECK( (new Mult(new Var("var"), new Var("var")))->subst("var", new Num(0))->equals(new Mult(new Num(0), new Num(0))) );
        CHECK( (new Mult(new Var("$"), new Num(10)))->subst("$", new Var("!"))->equals(new Mult(new Var("!"), new Num(10))) );
        CHECK( (new Mult(new Var("var"), new Num(1)))->subst("variable", new Num(8))->equals(new Mult(new Var("var"), new Num(1))) );
    }
    
    SECTION("To_String"){
        CHECK( (new Mult(new Num(1), new Num(1))) -> to_string() == "(1*1)");
        CHECK( (new Mult(new Num(0), new Num(10))) -> to_string() == "(0*10)");
        CHECK( (new Mult(new Num(-2), new Num(-4))) -> to_string() == "(-2*-4)");
        CHECK( (new Mult(new Var("y"), new Num(1))) -> to_string() == "(y*1)");
        CHECK( (new Mult(new Num(1), new Var("7"))) -> to_string() == "(1*7)");
    }
    
    SECTION("Pretty_Print"){
        CHECK ( (new Mult(new Mult(new Num(8), new Num(1)), new Var("y")))->to_pretty_string() ==  "(8 * 1) * y" );
        //failing below
        CHECK ( (new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
        CHECK ( (new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );
        CHECK ( (new Mult(new Num(2), new Num(2)))->to_pretty_string() ==  "2 * 2" );
        CHECK ( (new Mult(new Mult(new Num(1), new Num(-2)), new Mult(new Num(-3), new Num(4))) )->to_pretty_string() ==  "(1 * -2) * (-3 * 4)" );
    }
}

TEST_CASE("Var Class") {
    
    SECTION("Equals"){
        CHECK( (new Num(1))->equals(new Var("x")) == false);
        CHECK( (new Var("sarah"))->equals(new Var("sarah")) == true);
        CHECK( (new Var("sarah"))->equals(nullptr) == false);
        CHECK( (new Var("yes"))->equals(new Var("no")) == false);
        CHECK( (new Var("^"))->equals(new Var("^")) == true);
    }
    
    SECTION("Interp"){
        CHECK_THROWS_WITH( (new Var("x"))->interp(), "no value for variable" );
        CHECK_THROWS_WITH( (new Var("!"))->interp(), "no value for variable" );
        CHECK_THROWS_WITH( (new Var(""))->interp(), "no value for variable" );
        CHECK_THROWS_WITH( (new Var("1"))->interp(), "no value for variable" );
        CHECK_THROWS_WITH( (new Var("word"))->interp(), "no value for variable" );
    }
    
    SECTION("Has_Variable"){
        CHECK( (new Var("x"))->has_variable() == true);
        CHECK( (new Var("!"))->has_variable() == true);
        CHECK( (new Var(""))->has_variable() == true);
        CHECK( (new Var("1"))->has_variable() == true);
        CHECK( (new Var("word"))->has_variable() == true);
    }
    
    SECTION("Subst"){
        CHECK( (new Var("x")) ->subst("x", new Add(new Var("y"),new Num(7)))
               ->equals(new Add(new Var("y"),new Num(7))) );
        CHECK( (new Var("replaceMe")) ->subst("replaceMe", new Num(1))
               ->equals(new Num(1)) );
        CHECK( (new Var("replaceMe")) ->subst("replaceMe", new Num(-1))
               ->equals(new Num(-1)) );
        CHECK( (new Var("replaceMe")) ->subst("replaceMe", new Var("okay"))
               ->equals(new Var("okay")) );
        CHECK( (new Var("&")) ->subst("&", new Num(0))
               ->equals(new Num(0)) );
    }
    
    SECTION("To_String"){
        CHECK( (new Var("sarah")) -> to_string() == "sarah");
        CHECK( (new Var("!")) -> to_string() == "!");
        CHECK( (new Mult(new Var("*"), new Var("7"))) -> to_string() == "(**7)");
        CHECK( (new Add(new Var("longword"), new Var("s"))) -> to_string() == "(longword+s)");
        CHECK( (new Var("-&")) -> to_string() == "-&");
    }
}

TEST_CASE("New"){

}
