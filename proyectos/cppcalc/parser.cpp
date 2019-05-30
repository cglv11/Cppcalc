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

   if (t->getType() != eof) { //Si token es diferente a eof throw error 
     /* Error standar */ cerr << "Syntax Error: Expected EOF, found token at column "
			      << t->getCol() << endl;
      throw ParseError; 
   }

   return result;
}

AST* Parser::expr() {
   return restExpr(term());
}

AST* Parser::restExpr(AST* e) {
  Token* t = scan->getToken();  //obtiene el token

  if (t->getType() == add) { // [((+ term) RestExpr) | - term RestExpr | e ] addNode 
      return restExpr(new AddNode(e,term()));
   }

   if (t->getType() == sub)
      return restExpr(new SubNode(e,term()));
   
   scan->putBackToken();

   return e;
}

AST* Parser::term() {
  return restTerm(storable()); //restTerm llama a storable
}

AST* Parser::restTerm(AST* e) {
    Token* t = scan->getToken();  //obtiene el token

   AST* result = nullptr;

   switch(t->getType()) {
   case times:
     result = restTerm(new TimesNode(e, storable()));
     break;

   case divide:
     result = restTerm(new DivideNode(e, storable()));
     break;

   case module:
     result = restTerm(new ModuleNode(e, storable()));
     break;

     
   default:
     scan->putBackToken();
     result = e;
     break;
   }

   return result;
}

AST* Parser::storable() {
  AST* result = factor(); //AST (Arbol abstracto sintatico)

    Token *t = scan->getToken();

  if (t->getType() == keyword){
    if(t->getLex() == "S") { //"S" es una palabra reservada (keyword)
      return new StoreNode(result);
    }
    else {
      cerr << "Expected S found: " //se esperaba palabra reservada S pero ingresaron otra.
	   << t->getLex() << endl;
      throw ParseError; 
    }
  }
  else {
    scan->putBackToken();
  }
  return result;
}

AST* Parser::factor() {

     Token* t = scan->getToken();

   if (t->getType() == number) {
      istringstream in(t->getLex());
      int val;
      in >> val;
      return new NumNode(val);
   }

   if (t->getType() == keyword){
    if(t->getLex() == "R") { //"R" es una palabra reservada (keyword)
      return new RecallNode();
    }
    else {
      cerr << "Expected R found: " //se esperaba palabra reservada R pero ingresaron otra
           << t->getLex() << endl;
      throw ParseError;
    }
  }

    if (t->getType() == keyword){
      if(t->getLex() == "C") {
      return new ClearNode();
    }
      else {
	cerr << "Expected C found: " 
           << t->getLex() << endl;
	throw ParseError;
      }
  }


   if (t->getType() == lparen) { //left parentesis
     AST *result = expr();
     t = scan->getToken();
     if (t->getType() != rparen) {
       cerr << "Expected )" //Esperaba un parentesis derecho
	    << endl;
       throw ParseError;
     }
     return result;
   }

   cerr << "Expected number, R, ("
	<< endl;
   throw ParseError; 
}

//Analizador sintactico. 

