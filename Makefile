sim:
	g++ -Wall -std=c++11 src/Main.cpp src/Instrucao.cpp -o bin/Teste -I  include/
test:
	./bin/Teste data/Teste.txt
clean:
	rm bin/*
run:
	./bin/Teste data/entrada9.txt