sim:
	g++ -Wall -std=c++11 src/Main.cpp src/Instrucao.cpp src/Pipeline.cpp -o bin/Teste -I  include/
test1:
	./bin/Teste data/Teste1.txt
test2:
	./bin/Teste data/Teste2.txt
test3:
	./bin/Teste data/Teste3.txt
clean:
	rm bin/*
run:
	./bin/Teste data/entrada9.txt