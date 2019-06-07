#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "calcex.h"
#include "calculator.h"


using namespace std;

Calculator* calc;

void scannerCommand(int, char**);
bool noInteractive(int, char**);
string getText(string);
bool compi(int, char**);
void compiler(ifstream&, string);
void noCompiler(ifstream&);

int main(int argc, char* argv[]) {
   string line;
   string chain;
   ifstream archivo;

   calc = new Calculator();

   scannerCommand(argc, argv);

   if (noInteractive(argc, argv)){
     bool fail = false;

     for(int i=1; i<argc; i++){
       fail = false;
       chain = argv[i];
       
       if (chain.size()>=5 and chain.substr(chain.size()-5, chain.size())==".calc"){
	 archivo.open(argv[i], ios::in);
	 if(archivo.fail()){
	   cout << "Error at the moment of reading file: " << argv[i] << endl;
	   fail = true;
	 }

	 if (compi(argc, argv) and !fail){
	   compiler(archivo, chain);
	 }
	 else {
	   if (!fail)
	     noCompiler(archivo);
	 }

	 archivo.close();
       }
     }
   }
     
   else {
    while(true){
     try {

      cout << "> ";

      getline(cin, line); 
      // line + '\n';

	if(!cin) break;
	
        int result = calc->eval(line);

        cout << "= " << result << endl;
      
     }
     catch(Exception ex) {
     }
    }
   }
delete calc;

   return EXIT_SUCCESS;
}

void scannerCommand(int argc, char* argv[]){

  bool v = false;
  string var;
  string val;
  int value;

  for(int i=1; i<argc; i++){ //strncmp() compare chain, stdlib.h-string.h
    if(strncmp(argv[i], "-v", 2)==0){  // 2 is the max number of char to compare 
      v = true;
      string chain = argv[i+1];
      int equal = chain.find_first_of('=');
      var = chain.substr(0, equal);
      val = chain.substr(equal+1);
      calc->setVar(var, stoi(val));
    }
  }
}


bool noInteractive(int argc, char** argv){
  string chain;
  for(int i=1; i<argc; i++){
    chain = argv[i];
    if(chain.size()>=5 and chain.substr(chain.size()-5, chain.size())==".calc"){
      return true;    
    }
  }
  return false;
}


bool compi(int argc, char** argv){
  for(int i=1; 1<argc; i++){
    if(strncmp(argv[i], "-c", 2) == 0) {
      return true;
      }
  }
  return false;
}


void compiler(ifstream &archivo, string chain){
  string line;
  string lineOut;
  string temp = "";

  while(!archivo.eof()){
    try {
      getline(archivo, line);

      string printer = temp + "\n# print value produced \n" +
	"operator1 := M[sp+1] \n"+
	"writeInt(operator1) \n"+
	"sp  := sp + one \n";

      lineOut += calc->compile(line) + printer;
    }
    catch(Exception e){}    
  }

  ofstream archivoOut;
  archivoOut.open(chain.substr(0, chain.size()-4)+".ewe", ios::out);

  archivoOut << getText(lineOut);
  archivoOut.close();
}

string getText(string lineOut) {
  string temp = "";
  string input = temp + "\n# Code didn't edit \n" +
    "sp   := 1000 \n"+
    "one  := 1 \n"+
    "zero := 0 \n";
string endFile = temp + "\n# Memory \n" +
    "equ zero         M[0] \n"+
    "equ one          M[1] \n"+
    "equ operator1    M[2] \n"+
    "equ operator2    M[3] \n"+
    "equ sp           M[4] \n"+
    "equ memory       M[5] \n"+
    "equ value        M[6] \n"+
  calc->getKeys();

 return input + lineOut + "\n halt: \n" + endFile;
}




