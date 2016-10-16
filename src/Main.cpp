#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Instrucao.h"
#include "Pipeline.h"

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
    
    Pipeline p;

    if (file.is_open()){
        while (!file.eof()){
        	getline (file, line);
            Instrucao i(line);
            p.addInstrucao(i);
            /*std::cout << i.getLinhaCompleta() << std::endl;
            std::cout << "Função    : " << i.getNome() << std::endl
                      << "Destino   : " << i.getDestino() << std::endl
                      << "Destino 2 : " << i.getDestinoSecundario() << std::endl
                      << "Fonte 1   : " << i.getFonte1() << std::endl
                      << "Fonte 2   : " << i.getFonte2() << std::endl
                      << "Label     : " << i.getLabel() << std::endl
                      << "Valor     : " << i.getValor() << std::endl
                      << "Válida?   : " << i.isValida() << std::endl
                      << "É lábel?  : " << i.isLabel()  << std::endl << std::endl;
            */
        }
    } else {
        std::cout << ">>> Input file wasn't found. Try again.\n";
    }

    for (unsigned int i = 0; i < p.getNumeroDeInstrucoes(); ++i) {
      std::cout << p.getElemento(i).getNome() << "\n";
    }

    p.gerarPipeline();

    return 0;
}