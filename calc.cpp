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
string getText(string, string);
bool compi(int, char**);
void compiler();
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
       
       if(compi(argc, argv)){
	 //compilerw(archivo);
       }
       
       if (chain.size()>=5 and chain.substr(chain.size()-5, chain.size())==".calc"){
	 archivo.open(argv[i], ios::in);

	 if (compi(argc, argv) and !error){
	    
	   cout << "hola";
	 }
	 else{  if(!error)
	      noCompiler(archivo);
	   }
	 archivo.close();
       }
     }
   }
    
   else {
     for(int i=1; i<argc; i++){
       if(compi(argc, argv)){
         compiler();
       }
     }
     while(true){
       try {
	 cout << "> ";
	 getline(cin, line);
	 if(!cin) break; 
	 int result = calc->eval(line);
	 cout << "= " << result << endl;
       }
       catch(Exception ex) {}
     }
   }

   delete calc;
   
}

bool compi(int argc, char* argv[]) {
  bool c;
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

void compiler(){
  
  string countLine;
  ofstream filePrint;
  string temp;
  string line;
  string line2;

  while(true){
    try {
      cout << "> ";
      getline(cin, line);
      if(!cin) break;
      line2 = line;

        string printer = temp + 
	"\n# Write result \n" +
        "operator1 := M[sp+0] \n"+
        "sp  := sp - one \n"+
        "writeInt(operator1)";

      countLine = countLine + calc->compile(line) + printer;
    }
    catch(Exception e){ cout << "error aca";}
  }

  filePrint.open("a.ewe", ios::out);
  if(filePrint.fail()){
    cout << "error";
  }
  filePrint << getText(countLine, line2);
  filePrint.close();

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

string getText(string lineOut, string line) {
  string temp = "";
  string input = temp +
    "#Expresion: " + line +
    "\nstart: " +
    "\n# Instrucciones antes del recorrido del AST \n" +
    "sp   := 1000 \n"+
    "one  := 1 \n"+
    "zero := 0 \n"+
    "memory := zero \n"+
    "#Comienza el recorrido del arbol";
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




