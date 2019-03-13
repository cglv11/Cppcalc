CXXFLAGS=-g

cppcalc: calc.o scanner.o token.o ast.o parser.o calculator.o
	$(CXX) -o $@ $^ #$ y arroba toma todos los objetivos osea .o 

calc.o: calc.cpp scanner.h token.h

calculator.o: calculator.cpp calculator.h parser.h ast.h

scanner.o: scanner.cpp scanner.h token.h

token.o: token.cpp token.h

[15~ast.o: ast.cpp ast.h

parser.o: parser.cpp parser.h

clean:
	rm -f *.o
	rm -f cppcalc

