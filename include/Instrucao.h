#include <string>
#include <iostream>
#include <vector>
#include <cctype>

#ifndef INSTRUCAO_H
#define INSTRUCAO_H

class Instrucao {
private:
	std::string linhaCompleta;
	std::string nome;
	std::string destino;
	std::string destinoSecundario;
	std::string fonte1;
	std::string fonte2;
	std::string label;
	std::string valor;
	bool linhaValida;
	bool labelOuNao;

	void separarEValidarString();

public:
	Instrucao ();

	Instrucao (std::string linhaCompleta);

	std::string getLinhaCompleta();

	std::string getNome();

	std::string getDestino();

	std::string getDestinoSecundario();

	std::string getFonte1();

	std::string getFonte2();

	std::string getLabel();

	std::string getValor();

	bool isValida();

	bool isLabel();
};

#endif