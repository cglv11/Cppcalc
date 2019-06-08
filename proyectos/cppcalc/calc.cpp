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
void compiler(ifstream&);
void noCompiler(ifstream&);

int main(int argc, char* argv[]) {
   string line;
   std::string chain;
   ifstream archivo;

   calc = new Calculator();

   scannerCommand(argc, argv);

   if (noInteractive(argc, argv)){
     bool error = false;

     for(int i=1; i<argc; i++){
       error = false;
       chain = argv[i];
       
       if (chain.size()>=5 and chain.substr(chain.size()-5, chain.size())==".calc"){
	 archivo.open(argv[i], ios::in);
	 if(archivo.fail()){
	   cout << "Error at the moment of reading file: " << argv[i] << endl;
	   error = true;
	 }

	 if (compi(argc, argv) and !error){
	   compiler(archivo);
	 }
	 else {
	     if(!error)
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
	if(!cin) break;
	
        int result = calc->eval(line);

        cout << "= " << result << endl;
      
     }
     catch(Exception ex) {
     }
    }
   }
delete calc;
}

bool compi(int argc, char* argv[]) {
  for(int i=1; i<argc; i++){
    if(strncmp(argv[i], "-c", 2)==0) {
      return true; 
    }
  }
  return false;
}

void scannerCommand(int argc, char* argv[]){

  bool v = false;
  string var;
  string val;
  int value;

  for(int i=1; i<argc; i++){ //strncmp() compare chain, stdlib.h-string.h
    if(strncmp(argv[i], "-v", 2)==0){  // 2 is the max number of char to compare 
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

void compiler(ifstream &archivo){
  
  string line;
  string countLine;
  ofstream filePrint;
  string temp;
  
  while(!archivo.eof()){
    try {
      getline(archivo, line);

        string printer = temp + "\n# Write result \n" +
	"operator1 := M[sp+1] \n"+
	"sp  := sp - one \n";
	"writeInt(operator1) \n"+
    
      countLine = calc->compile(line) + printer;
        filePrint.open("a.ewe", ios::out);
	if(filePrint.fail()){
	  cout << "error";
	}
	filePrint << getText(countLine);
	filePrint.close();

    }
    catch(Exception e){
    }
  }
}

void noCompiler(ifstream &archivo) {
  string line;
  while(!archivo.eof()){
    try { 
      getline(archivo, line);
      int result = calc->eval(line);
		
      cout << "= " << result << endl;
    }
    catch(Exception e) {} 	    	      
    }   
}

string getText(string lineOut) {
  string temp = "";
  string input = temp + "\n# Instrucciones antes del recorrido del AST \n" +
    "sp   := 1000 \n"+
    "one  := 1 \n"+
    "zero := 0 \n";
    "memory := zero"
string endFile = temp + "\n# end: halt \n" +
    "equ memory         M[0] \n"+
    "equ one            M[1] \n"+
    "equ zero           M[2] \n"+
    "equ operator1      M[3] \n"+
    "equ operator2      M[4] \n"+
    "equ sp             M[5] \n"+
    "equ stack          M[1000] \n"+
  
  calc->getValue();

 return input + lineOut + endFile;
}




