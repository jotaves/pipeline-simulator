#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Instrucao.h"

int main(int argc, char * argv[]) {
	/* Leitura de entrada */
	std::string entrada;

	if (argc == 2){
        std::stringstream (argv[1]) >> entrada;
    } else {
        std::cout << ">>> Error. Try calling $ ./bin/sim [input filename]\n";
        return 0;
    }

    std::ifstream file;
    std::string line;

    file.open (entrada);
    
    if (file.is_open()){
        while (!file.eof()){
        	getline (file, line);
            Instrucao i (line);
            std::cout << i.getNome() << " " << i.getDestino() << " " << i.getFonte1() << " " << i.getFonte2() << std::endl;
        }
    } else {
        std::cout << ">>> Input file wasn't found. Try again.\n";
    }

    return 0;
}