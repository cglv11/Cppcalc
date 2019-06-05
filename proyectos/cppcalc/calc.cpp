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



int main(int argc, char* argv[]) {
   string line;

   calc = new Calculator();

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
     //  cout << "Program Aborted due to exception!" << endl;
     //return EXIT_FAILURE;
   }
  }

delete calc;

   return EXIT_SUCCESS;
}
   
