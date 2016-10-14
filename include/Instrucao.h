#include <string>
#include <iostream>
#include <vector>

#ifndef INSTRUCAO_H
#define INSTRUCAO_H

class Instrucao {
private:
	std::string nome;
	std::string destino;
	std::string fonte1;
	std::string fonte2;
	std::string linhaCompleta;
	//bool instrucaoValida;

	void separarString();

public:

	Instrucao (std::string linhaCompleta);

	std::string getNome();

	void setNome(std::string nome);

	std::string getDestino();

	void setDestino(std::string destino);

	std::string getFonte1();

	void setFonte1(std::string fonte1);

	std::string getFonte2();

	void setFonte2(std::string fonte2);
};

#endif