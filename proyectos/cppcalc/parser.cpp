#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>

Parser::Parser(istream* in) {
   scan = new Scanner(in);
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::parse() {
   return prog();
}

AST* Parser::prog() {
   AST* result = expr();
   Token* t = scan->getToken();

   if (t->getType() != eof) {
      cout << "Syntax Error: Expected EOF, found token at column " << t->getCol() << endl;
      throw ParseError;
   }

   return result;
}

AST* Parser::expr() {
   return restExpr(term());
}

AST* Parser::restExpr(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == add) {
      return restExpr(new AddNode(e,term()));
   }

   if (t->getType() == sub)
      return restExpr(new SubNode(e,term()));

   scan->putBackToken();

   return e;
}

AST* Parser::term() {
   //write your term() code here. This code is just temporary
   //so you can try the calculator out before finishing it.
   Token* t = scan->getToken();

   if (t->getType() == number) {
      istringstream in(t->getLex());
      int val;
      in >> val;
      return new NumNode(val);
   }

   cout << "Term not implemented" << endl;

   throw ParseError; 
}

AST* Parser::restTerm(AST* e) {
   cout << "restTerm not implemented" << endl;

   throw ParseError; 
}

AST* Parser::storable() {
   cout << "storable not implemented" << endl;

   throw ParseError; 
}

AST* Parser::factor() {
   cout << "factor not implemented" << endl;

   throw ParseError; 
}
   
