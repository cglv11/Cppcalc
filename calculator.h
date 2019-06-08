#pragma once
#include <map>
#include <string>
 
using namespace std;


class Calculator {
 public:
   Calculator();

   int eval(string expr);
   void store(int val);
   int recall();
   int clear();
   void plus(int val);
   void minus(int val);
   void setVar(string var, int val);
   int getVar(string var);
   bool containVar(string var);
   string compile(string expr);
   string getValue(); 

 private:
   int memory;
   map <string, int> maps;
};

extern Calculator* calc;  //variable global, para resolver el problema que tenemos una sola memoria. Con la variable externa, recall llama a calculator

