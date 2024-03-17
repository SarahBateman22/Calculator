/**
 *\file tests.cpp
 *\brief Test class
 *
 * Test class contains test cases separated by class (ie Num, Add, Mult, etc) and function being tested (Equals, Interp, Subst, etc)
 */
#include <stdio.h>
#include "expr.hpp"
#include "catch.h"
#include "parse.hpp"
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
    
    SECTION("To_String (print)"){
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
    
    SECTION("To_String (print)"){
        CHECK( (new Add(new Num(1), new Num(1))) -> to_string() == "(1+1)");
        CHECK( (new Add(new Num(0), new Num(10))) -> to_string() == "(0+10)");
        CHECK( (new Add(new Num(-2), new Num(-4))) -> to_string() == "(-2+-4)");
        CHECK( (new Add(new Var("x"), new Num(1))) -> to_string() == "(x+1)");
        CHECK( (new Add(new Num(1), new Var("12"))) -> to_string() == "(1+12)");
    }
    
    SECTION("Pretty_Print"){
        CHECK ( (new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
        CHECK ( (new Add(new Num(10), new Add(new Num(4), new Num(2))))->to_pretty_string() ==  "10 + 4 + 2" );
        CHECK ( (new Add(new Num(1), new Num(1)))->to_pretty_string() ==  "1 + 1" );
        CHECK( (new Add(new Add(new Num(-4), new Num(3)), new Add(new Num(2), new Num(-1))) )->to_pretty_string() == "(-4 + 3) + 2 + -1" );
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
    
    SECTION("To_String (print)"){
        CHECK( (new Mult(new Num(1), new Num(1))) -> to_string() == "(1*1)");
        CHECK( (new Mult(new Num(0), new Num(10))) -> to_string() == "(0*10)");
        CHECK( (new Mult(new Num(-2), new Num(-4))) -> to_string() == "(-2*-4)");
        CHECK( (new Mult(new Var("y"), new Num(1))) -> to_string() == "(y*1)");
        CHECK( (new Mult(new Num(1), new Var("7"))) -> to_string() == "(1*7)");
    }
    
    SECTION("Pretty_Print"){
        CHECK ( (new Mult(new Mult(new Num(8), new Num(1)), new Var("y")))->to_pretty_string() ==  "(8 * 1) * y" );
        CHECK ( (new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
        CHECK ( (new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );
        CHECK ( (new Mult(new Num(2), new Num(2)))->to_pretty_string() ==  "2 * 2" );
        CHECK( (new Mult(new Mult(new Num(1), new Num(-2)), new Mult(new Num(-3), new Num(4))) )->to_pretty_string() == "(1 * -2) * -3 * 4" );
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
    
    SECTION("To_String (print)"){
        CHECK( (new Var("sarah")) -> to_string() == "sarah");
        CHECK( (new Var("!")) -> to_string() == "!");
        CHECK( (new Mult(new Var("*"), new Var("7"))) -> to_string() == "(**7)");
        CHECK( (new Add(new Var("longword"), new Var("s"))) -> to_string() == "(longword+s)");
        CHECK( (new Var("-&")) -> to_string() == "-&");
    }
}

TEST_CASE("Let Class"){
    
    SECTION("Equals"){
        CHECK((new Let("x", new Num(1), new Add(new Num(2), new Num(3))))->equals(new Let("x", new Num(1), new Add(new Num(2), new Num(3)))) == true);
        CHECK((new Let("var", new Num(0), new Mult(new Num(-10000), new Num(5))))->equals(new Let("var", new Num(0), new Mult(new Num(-10000), new Num(5)))) == true);
        //difference is in var name
        CHECK((new Let("x", new Num(0), new Mult(new Num(1), new Num(-8))))->equals(new Let("y", new Num(0), new Add(new Num(1), new Num(-8)))) == false);
        //difference is in first nameVal field
        CHECK((new Let("x", new Num(0), new Mult(new Num(1), new Num(-8))))->equals(new Let("x", new Num(1), new Add(new Num(1), new Num(-8)))) == false);
        //difference is in Add/Mult in bodyExpr
        CHECK((new Let("x", new Num(0), new Mult(new Num(1), new Num(-8))))->equals(new Let("x", new Num(0), new Add(new Num(1), new Num(-8)))) == false);
        
    }
    
    SECTION("Interp"){
        CHECK( (new Let("var", new Num(0), new Add(new Var("var"), new Num(1))))->interp() == 1);
        CHECK( (new Let("z", new Num(-10), new Mult(new Var("z"), new Num(5))))->interp() == -50);
        CHECK( (new Let("!", new Num(0), new Mult(new Var("!"), new Num(0))))->interp() == 0);
        CHECK( (new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->interp() == 10);
        CHECK( (new Let("x", new Num(10), new Add(new Let("y", new Num(-15), new Add(new Var("y"), new Num(2))), new Var("x"))))->interp() == -3);
    }
    
    SECTION("Has_Variable"){
        CHECK( (new Let("var", new Num(0), new Add(new Var("var"), new Num(1))))->has_variable() == true);
        CHECK( (new Let("x", new Num(3), new Add(new Var("x"), new Var("here"))))->has_variable() == true);
        CHECK( (new Let("one", new Num(0), new Add(new Var("two"), new Num(0))))->has_variable() == true);
        CHECK( (new Let("&", new Var("*"), new Add(new Var("&"), new Num(-1))))->has_variable() == true);
        CHECK( (new Let("^", new Num(-8), new Add(new Var("^"), new Num(5))))->has_variable() == true);
    }
    
    SECTION("Subst"){
        CHECK((new Let("x", new Var("x"), new Add(new Var("x"), new Num(3))))
            ->subst("x", new Num(1))->equals(new Let("x", new Num(1),
            new Add(new Var("x"), new Num(3)))) == true);
        CHECK((new Let("x", new Num(1), new Var("x")))->subst
            ("x", new Num(2)) ->equals(new Let("x", new Num(1), new Var("x"))) == true);
        CHECK((new Let("x", new Num(1), new Add(new Var("x"), new Var("y"))))->subst("y", new Num(2))->equals(new Let("x", new Num(1), new Add(new Var("x"), new Num(2)))) == true);
        CHECK((new Let("x", new Num(1), new Let("y", new Var("x"), new Var("y"))))
            ->subst("x", new Num(2))
            ->equals(new Let("x", new Num(2), new Let("y", new Num(2), new Var("y")))) == false);
        CHECK((new Let("x", new Var("z"), new Add(new Var("x"), new Var("z"))))
            ->subst("z", new Num(3))
            ->equals(new Let("x", new Num(3), new Add(new Var("x"), new Num(3)))) == true);
    }
    
    SECTION("To_String (print)"){
        CHECK((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
        CHECK((new Let("a", new Num(10), new Let("b", new Num(5), new Add(new Var("a"), new Var("b")))))->to_string() == "(_let a=10 _in (_let b=5 _in (a+b)))");
        CHECK((new Let("n", new Num(2), new Mult(new Var("n"), new Num(3))))->to_string() == "(_let n=2 _in (n*3))");
        CHECK((new Let("x", new Num(1), new Add(new Var("x"), new Let("y", new Num(2), new Mult(new Var("y"), new Num(3))))))->to_string() == "(_let x=1 _in (x+(_let y=2 _in (y*3))))");
        CHECK((new Let("x", new Num(4), new Let("y", new Num(5), new Add(new Let("z", new Num(6), new Mult(new Var("z"), new Var("y"))), new Var("x")))))->to_string() == "(_let x=4 _in (_let y=5 _in ((_let z=6 _in (z*y))+x)))");
    }
    
    SECTION("Pretty Print"){
        Let* innerLet = new Let("y", new Num(3), new Add(new Var("y"), new Num(2)));
        Let* outerLet = new Let("x", new Num(5), new Add(innerLet, new Var("x")));
        std::string expected = "_let x = 5\n _in (_let y = 3\n      _in y + 2) + x";
        CHECK( outerLet->to_pretty_string()==expected );
        CHECK ( (new Mult(new Mult(new Num (2), new Let("x", new Num(5), new Add(new Var("x") , new Num(1)) )), new Num(3)))->to_pretty_string() == "(2 * _let x = 5\n"
                "      _in x + 1) * 3");
        CHECK((new Mult(new Num(5), new Add(new Let("x", new Num(5), new Var("x")), new Num(1))))->to_pretty_string() == "5 * ((_let x = 5\n"
                "      _in x) + 1)");
             
        CHECK ( (new Add(new Let("x", new Num(2), new Add(new Var("x"), new Num(9))), new Num(4)))->to_pretty_string() == "(_let x = 2\n"
                " _in x + 9) + 4");
               
        CHECK((new Mult(new Let("x", new Num(5), new Add(new Var("x"), new Num(8))), new Num(3)))->to_pretty_string() == "(_let x = 5\n"
                " _in x + 8) * 3");
            
        CHECK( (new Let("x",new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2 ))), new Var("x"))))->to_pretty_string() == "_let x = 5\n _in (_let y = 3\n      _in y + 2) + x");
    }
}

TEST_CASE("parse") {
  CHECK_THROWS_WITH( parse_str("()"), "Invalid input" );

  CHECK( parse_str("(1)")->equals(new Num(1)) );
  CHECK( parse_str("(((1)))")->equals(new Num(1)) );

  CHECK_THROWS_WITH( parse_str("(1"), "Missing close parentheses" );

  CHECK( parse_str("1")->equals(new Num(1)) );
  CHECK( parse_str("10")->equals(new Num(10)) );
  CHECK( parse_str("-3")->equals(new Num(-3)) );
  CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
  CHECK_THROWS_WITH( parse_str("-"), "Invalid input" );

  CHECK_THROWS_WITH( parse_str(" -   5  "), "Invalid input" );

  CHECK( parse_str("x")->equals(new Var("x")) );
  CHECK( parse_str("xyz")->equals(new Var("xyz")) );
  CHECK( parse_str("xYz")->equals(new Var("xYz")) );
  CHECK_THROWS_WITH( parse_str("x_z"), "Invalid input" );

  CHECK( parse_str("x + y")->equals(new Add(new Var("x"), new Var("y"))) );

  CHECK( parse_str("x * y")->equals(new Mult(new Var("x"), new Var("y"))) );

  CHECK( parse_str("z * x + y")
        ->equals(new Add(new Mult(new Var("z"), new Var("x")),
                         new Var("y"))) );
  
  CHECK( parse_str("z * (x + y)")
        ->equals(new Mult(new Var("z"),
                          new Add(new Var("x"), new Var("y"))) ));
    
    CHECK( parse_str("_let x = 5 _in x + 3")
              ->equals(new Let("x", new Num(5), new Add(new Var("x"), new Num(3)))) );
    
    CHECK( parse_str("_let x = 2 _in _let y = x + 3 _in y * x") ->equals(new Let("x", new Num(2),
        new Let("y", new Add(new Var("x"), new Num(3)), new Mult(new Var("y"), new Var("x"))))) );
}


