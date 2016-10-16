#include <vector>
#include <queue>
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

public:
	Pipeline ();

	Instrucao getElemento (unsigned int i);

	void addInstrucao(Instrucao instrucao);

	unsigned int getNumeroDeInstrucoes();

	void gerarPipeline();

	bool hasConflito(Instrucao instrucao);

	void print();	
};

#endif