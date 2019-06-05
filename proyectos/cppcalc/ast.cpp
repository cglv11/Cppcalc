#include "ast.h"
#include <iostream>
#include "calculator.h"

// for debug information uncomment
//#define debug

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
   AST(),
   leftTree(left),
   rightTree(right)
{}

BinaryNode::~BinaryNode() {
#ifdef debug
   cout << "In BinaryNode destructor" << endl;
#endif

   try {
      delete leftTree;
   } catch (...) {}

   try {
      delete rightTree;
   } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
   return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
   return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
   AST(),
   subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
   cout << "In UnaryNode destructor" << endl;
#endif

   try {
      delete subTree;
   } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
   return subTree;
}

AddNode::AddNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int AddNode::evaluate() {
   return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

TimesNode::TimesNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int TimesNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

DivideNode::DivideNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int DivideNode::evaluate() {
   return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

ModuleNode::ModuleNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int ModuleNode::evaluate() {
   return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

NumNode::NumNode(int n) :
   AST(),
   val(n)
{}

int NumNode::evaluate() {
   return val;
}

IdNode::IdNode(std::string var) :
   AST(),
   var(var)
{}

int IdNode::evaluate() {
  if(calc->containVar(var))
    return calc->getVar(var);
  else
    calc->setVar(var, 0);
    return 0;
}


RecallNode::RecallNode() :
   AST()
{}

int RecallNode::evaluate() {
  return calc->recall();
}

InitVarNode::InitVarNode(std::string var, AST* sub) : UnaryNode(sub), var(var) {}

InitVarNode::~InitVarNode() {}

int InitVarNode::evaluate(){

  calc->setVar(var, getSubTree()->evaluate());
  return calc->getVar(var);
}

StoreNode::StoreNode(AST *sub) : UnaryNode(sub) { }

StoreNode::~StoreNode() {}

int StoreNode::evaluate() {
  calc->store(getSubTree()->evaluate()); 
  return calc->recall();  //en esta func almacenamos el valor, como calc es un apuntador a un objeto lo que hace es tomar la funcion del objeto apuntado.
}

ClearNode::ClearNode() :
   AST()
{}

ClearNode::~ClearNode() {}

int ClearNode::evaluate() {
  return calc->clear();
}

PlusNode::PlusNode(AST *sub) : UnaryNode(sub) { }

PlusNode::~PlusNode() {}

int PlusNode::evaluate() {
  calc->plus(getSubTree()->evaluate());
  return calc->recall();  
}

MinusNode::MinusNode(AST *sub) : UnaryNode(sub) { }

MinusNode::~MinusNode() {}

int MinusNode::evaluate() {
  calc->minus(getSubTree()->evaluate());
  return calc->recall();
}

