#include "Instrucao.h"

void Instrucao::separarString() {
	std::vector<std::string> v;
	std::string tokenizado = "";

	for (unsigned int i = 0; i < linhaCompleta.size(); ++i)
	{
		if (linhaCompleta[i] == ' ' or linhaCompleta[i] == ',')
			continue;
		else {
			while (linhaCompleta[i] != ' ' and linhaCompleta[i] != ',' and i < linhaCompleta.size()) {
				tokenizado += linhaCompleta[i++];
			}
			v.push_back(tokenizado);
			tokenizado = "";
		}
	}

	if(v[0] == "add" or v[0] == "sub" or v[0] == "and" or v[0] == "or" or v[0] == "slt") {
		if (v.size() < 4) {
			std::cout << "Instrução " << v[0] << " incompleta.";
		} else {
			this->nome = v[0];
			this->destino = v[1];
			this->fonte1 = v[2];
			this->fonte2 = v[3];
		}
	}

	// TODO: colocar outras funções.
}

Instrucao::Instrucao (std::string linhaCompleta) {
	this->linhaCompleta = linhaCompleta;
	separarString();
}

std::string Instrucao::getNome() {
	return this->nome;
}

void Instrucao::setNome(std::string nome) {
	this->nome = nome;
}

std::string Instrucao::getDestino() {
	return this->destino;
}

void Instrucao::setDestino(std::string destino) {
	this->destino = destino;
}

std::string Instrucao::getFonte1() {
	return this->fonte1;
}

void Instrucao::setFonte1(std::string fonte1) {
	this->fonte1 = fonte1;
}

std::string Instrucao::getFonte2() {
	return this->fonte2;
}

void Instrucao::setFonte2(std::string fonte2) {
	this->fonte2 = fonte2;
}