#include <vector>
#include <queue>
#include <cstring>
#include "Instrucao.h"

#ifndef PIPELINE_H
#define PIPELINE_H

class Pipeline {
private:
	std::deque<Instrucao> filaDestinos;
	std::deque<Instrucao> estagios;
	std::vector<Instrucao> instrucoes;
	unsigned int numeroDeInstrucoes;
	unsigned int numeroDeCiclos;

	Instrucao hasConflito(Instrucao instrucao);
	void print();	

public:
	Pipeline ();
	void addInstrucao(Instrucao instrucao);
	unsigned int getNumeroDeInstrucoes();
	unsigned int getNumeroDeCiclos();
	void gerarPipeline();
};

#endif