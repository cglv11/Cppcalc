#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>


Calculator::Calculator():
   memory(0)
{}

int Calculator::eval(string expr) {

   Parser* parser = new Parser(new istringstream(expr));
   
   AST* tree = parser->parse();
   
   int result = tree->evaluate();
   
   delete tree;
   
   delete parser;
   
   return result;
}

void Calculator::store(int val) {
   memory = val;
}

int Calculator::recall() {
   return memory;
}

int Calculator::clear() {
  memory = 0;
  return memory;
}

void Calculator::plus(int val) {
   memory += val;
}

void Calculator::minus(int val) {
   memory -= val;
}

void Calculator::setVar(string var, int val) {
  maps[var] = val;
}

bool Calculator::containVar(string var) {
  return maps.count(var);
}

int Calculator::getVar(string var) {
  return maps[var];
}

string Calculator::compile(string expr) {

   Parser* parser = new Parser(new istringstream(expr));

   AST* tree = parser->parse();

   string result = tree->compile();

   delete tree;

   delete parser;

   return result;
}

string Calculator::getValue() {
  string values;
  int count = 7;
  for(map<string, int>::iterator it = maps.begin(); it != maps.end(); ++it){
    values = values + "equ " + it->first + " M[" + to_string(count)+ "] \n";
    count++;
  }

  return values;
}

