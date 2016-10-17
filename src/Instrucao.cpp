#include "Instrucao.h"

void Instrucao::separarEValidarString() {
	std::vector<std::string> v;
	std::string tokenizado = "";

	bool isVazia = true;

	// Pegando elementos da string.
	for (unsigned int i = 0; i < linhaCompleta.size(); ++i)
	{
		if (linhaCompleta[i] == ' ' or linhaCompleta[i] == ',') {
			continue;
		}
		else {
			isVazia = false;
			while (linhaCompleta[i] != ' ' and linhaCompleta[i] != ',' and i < linhaCompleta.size()) {
				tokenizado += linhaCompleta[i++];
			}
			v.push_back(tokenizado);
			tokenizado = "";
		}
	}

	// Vendo se é uma linha vazia.
	if (isVazia) return;

	// ADD | SUB | AND | OR | SLT
	if (v[0] == "add" or v[0] == "sub" or v[0] == "and" or v[0] == "or" or v[0] == "slt") {
		if (v.size() < 4) {
			this->linhaValida = false;
			std::cout << "Instrução \"" << linhaCompleta << "\" incorreta. Ela não será considerada na simulação.\n";
		} else {
			this->nome = v[0];
			this->destino = v[1];
			this->fonte1 = v[2];
			this->fonte2 = v[3];
			this->linhaValida = true;
		}
	}

	// DIV | MUL
	else if (v[0] == "div" or v[0] == "mult" or v[0] == "mul") {
		if (v.size() < 3) {
			this->linhaValida = false;
			std::cout << "Instrução \"" << linhaCompleta << "\" incorreta. Ela não será considerada na simulação.\n";
		} else {
			this->nome = v[0];
			this->destino = "hi";
			this->destinoSecundario = "lo";
			this->fonte1 = v[1];
			this->fonte2 = v[2];
			this->linhaValida = true;			
		}
	}

	// ADDI | ORI | SLL | SLR | SUBI
	else if (v[0] == "addi" or v[0] == "ori" or v[0] == "sll" or v[0] == "slr" or v[0] == "subi") {
		if (v.size() < 3) {
			this->linhaValida = false;
			std::cout << "Instrução \"" << linhaCompleta << "\" incorreta. Ela não será considerada na simulação.\n";
		} else {
			this->nome = v[0];
			this->destino = v[1];
			this->fonte1 = v[2];
			this->valor = v[3];
			this->linhaValida = true;
		}
	}

	// LW | SW
	else if (v[0] == "lw" or v[0] == "sw") {
		if (v.size() < 3) {
			this->linhaValida = false;
			std::cout << "Instrução \"" << linhaCompleta << "\" incorreta. Ela não será considerada na simulação.\n";
		} else {
			std::string aux1 = "";
			std::string aux2 = "";
			unsigned int j = 0;

				// Pegando valor anterior ao registrador.
				while (v[2][j] != '(' and j < v[2].size()) {
					aux1 += v[2][j++];
				}

				// Pulando parênteses.
				j++;
				
				// Pegando registrador.
				while (v[2][j] != ')' and j < v[2].size()) {
					aux2 += v[2][j++];
				}

			if (v[0] == "lw") {
				this->nome = v[0];
				this->destino = v[1];
				this->valor = aux1;
				this->fonte1 = aux2;
			} else { // "sw"
				this->nome = v[0];
				this->fonte1 = v[1];
				this->valor = aux1;
				this->destino = aux2;
			}
			this->linhaValida = true;
		}
	}

	// BEQ | BNE
	else if (v[0] == "beq" or v[0] == "bne") {
		if (v.size() < 3) {
			this->linhaValida = false;
			std::cout << "Instrução \"" << linhaCompleta << "\" incorreta. Ela não será considerada na simulação.\n";
		} else {
			this->nome = v[0];
			this->fonte1 = v[1];
			this->fonte2 = v[2];
			this->label = v[3];
			this->linhaValida = true;
		}
	}

	// J
	else if (v[0] == "j") {
		if (v.size() < 2) {
			this->linhaValida = false;
			std::cout << "Instrução \"" << linhaCompleta << "\" incorreta. Ela não será considerada na simulação.\n";
		} else {
			this->nome = v[0];
			this->label = v[1];
			this->linhaValida = true;
		}
	}

	// SYSCALL
	else if (v[0] == "syscall") {
		if (v.size() < 1) {
			this->linhaValida = false;
			std::cout << "Instrução \"" << linhaCompleta << "\" incorreta. Ela não será considerada na simulação.\n";
		} else {
			this->nome = v[0];
			this->destino = "$v0";
			this->fonte1 = "$v0";
			this->fonte2 = "$a0";
			this->linhaValida = true;
		}
	}

	// MFHI | MFLO
	else if (v[0] == "mfhi" or v[0] == "mflo") {
		if (v.size() < 2) {
			this->linhaValida = false;
			std::cout << "Instrução \"" << linhaCompleta << "\" incorreta. Ela não será considerada na simulação.\n";
		} else {
			this->nome = v[0];
			this->destino = v[1];
			if (v[0] == "mfhi")
				this->fonte1 = "hi";
			else this->fonte1 = "lo";
			this->linhaValida = true;
		}
	}

	else {
			// LABEL (verificando)
			bool labelAux = false;

			for (unsigned int k = linhaCompleta.size()-1; k >= 0; k--) {
				if (linhaCompleta[k] == ' ') continue;
				else if (linhaCompleta[k] != ':') {
					break;
				}
				else {
					std::string aux = "";
					for(unsigned int l = 0; l < linhaCompleta.size()-1; l++) {
						if (linhaCompleta[l] == ' ' or linhaCompleta[l] == ':') continue;
						aux += linhaCompleta[l];
					}
					this->nome = aux;
					this->linhaValida = true;
					this->labelOuNao = true;
					labelAux = true;
				}
			}

			// NÃO IDENTIFICADO
			if (!labelAux) {
				std::cout << "Instrução " << linhaCompleta << " não foi identificada. Ela não será considerada na simulação.\n";
			}
	}
}

Instrucao::Instrucao () : linhaCompleta("null"), nome("null"), destino("null"), destinoSecundario("null"), fonte1("null"), fonte2("null"), label("null"), valor("null"), linhaValida(false), labelOuNao(false) {

}

Instrucao::Instrucao (std::string linhaCompleta) : nome("null"), destino("null"), destinoSecundario("null"), fonte1("null"), fonte2("null"), label("null"), valor("null"), linhaValida(false), labelOuNao(false) {
	this->linhaCompleta = linhaCompleta;
	separarEValidarString();
}

std::string Instrucao::getLinhaCompleta() {
	return this->linhaCompleta;
}

std::string Instrucao::getNome() {
	return this->nome;
}

std::string Instrucao::getDestino() {
	return this->destino;
}

std::string Instrucao::getDestinoSecundario() {
	return this->destinoSecundario;
}

std::string Instrucao::getFonte1() {
	return this->fonte1;
}

std::string Instrucao::getFonte2() {
	return this->fonte2;
}

std::string Instrucao::getLabel() {
	return this->label;
}

std::string Instrucao::getValor() {
	return this->valor;
}

bool Instrucao::isValida() {
	return this->linhaValida;
}

bool Instrucao::isLabel() {
	return this->labelOuNao;
}