#ifndef parser_h
#define parser_h

#include "ast.h"
#include "scanner.h"

class Parser {
 public:
   Parser(istream* in);
   ~Parser();

   AST* parse();

 private:
   AST* prog();
   AST* ListExpr();
   AST* expr();
   AST* restExpr(AST* e);
   AST* term();
   AST* restTerm(AST* t);
   AST* storable();
   AST* MemOperation();
   AST* factor();

   Scanner* scan;
};


#endif   
