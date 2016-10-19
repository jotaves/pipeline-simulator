#include <Pipeline.h>

Instrucao Pipeline::hasConflito(Instrucao instrucao) {
	for (int k = filaDestinos.size()-1; k > -1; k--){
			//Comparando destino (se não for null)
			if(filaDestinos.at(k).getDestino() != "null"){
				if (instrucao.getFonte1() != "null") {
					if (instrucao.getFonte1() == filaDestinos.at(k).getDestino()){
							return filaDestinos.at(k);
					}
				}
				
				if (instrucao.getFonte2() != "null") {
					if (instrucao.getFonte2() == filaDestinos.at(k).getDestino())
						return filaDestinos.at(k);
				}
			}
			//Comparando destino secundário (se não for null)
			if(filaDestinos.at(k).getDestinoSecundario() != "null") {
				if (instrucao.getFonte1() != "null") {
					if (instrucao.getFonte1() == filaDestinos.at(k).getDestinoSecundario()) {
						return filaDestinos.at(k);
					}
				}

				if (instrucao.getFonte2() != "null") {
					if (instrucao.getFonte2() == filaDestinos.at(k).getDestinoSecundario()) {
						return filaDestinos.at(k);
					}
				}
			}
		}
	Instrucao null;
	return null;
}

void Pipeline::print() {
		std::cout << "\n-----------------------------------------------------\n";
		std::cout << "\nCiclo " << numeroDeCiclos << "\n";
		std::cout << "BI:	" << estagios.at(4).getLinhaCompleta() << "\n";
		std::cout << "DI:	" << estagios.at(3).getLinhaCompleta() << "\n";
		std::cout << "EX:	" << estagios.at(2).getLinhaCompleta() << "\n";
		std::cout << "MEM:	" << estagios.at(1).getLinhaCompleta() << "\n";
		std::cout << "WB:	" << estagios.at(0).getLinhaCompleta() << "\n";
}

Pipeline::Pipeline () : numeroDeInstrucoes(0), numeroDeCiclos(0) {
}

void Pipeline::addInstrucao(Instrucao instrucao) {
	if(instrucao.isValida()) {
		instrucoes.push_back(instrucao);
		if (!instrucao.isLabel()) numeroDeInstrucoes++;
	}
}

unsigned int Pipeline::getNumeroDeInstrucoes() {
	return this->numeroDeInstrucoes;
}

unsigned int Pipeline::getNumeroDeCiclos() {
	return this->numeroDeCiclos;
}

void Pipeline::gerarPipeline() {
	Instrucao null;
	estagios.assign(5, null);
	bool wasJump = false;
	unsigned int nextAfterJump;

	for (unsigned int i = 0; i < instrucoes.size(); ) {

		//Conflito caso lw esteja no MEM e algo seja inserido no IF, usando 1 memória.
		if(estagios[2].getNome() == "lw") {
			// não insere elementos
			estagios.push_back(null);
			estagios.pop_front();
			numeroDeCiclos++;
			print();
			continue;
		}

		//std::cout << "\ni = " << i << "\n";
		//std::cout << instrucoes[i].isLabel() << "\n";
		//Se a "instrução" for uma label, pula.
		if (instrucoes[i].isLabel()) {
			i++;
			continue;
		}

		if (instrucoes[i].getNome() == "beq" or 
			instrucoes[i].getNome() == "bne" or
			instrucoes[i].getNome() == "j") {

			unsigned int j = i;
			nextAfterJump = i;

			while (nextAfterJump < instrucoes.size() and instrucoes[j].getLabel().compare (instrucoes[nextAfterJump].getNome()) != 0) {
				//std::cout << instrucoes[nextAfterJump].getNome() << "\n";
				//std::cout << instrucoes[j].getLabel().compare (instrucoes[nextAfterJump].getNome()) << "\n";
				nextAfterJump++;
				//std::cout << instrucoes[nextAfterJump].getNome();
			}

			if (nextAfterJump == instrucoes.size()) {
				std::cout << "\nHá um jumper no código cujo label não foi encontrada!\n";
				break;
			}
			wasJump = true;
			//std::cout << k+1 << "\n";
			//std::cout << instrucoes[k].getLinhaCompleta() << "\n";
			//std::cout << instrucoes[j].getLabel().compare (instrucoes[k].getNome()) << "\n";
		}

		//std::cout << "\nj = " << j << "\n";
		//Primeira instrução.
		if (i == 0) {
			//std::cout << "Primeira instrução!\n";
			
			estagios.push_back(instrucoes[i]);
			filaDestinos.push_back(instrucoes[i++]);
			
			if (filaDestinos.size() > 4) {
				filaDestinos.pop_front();
			}			
			estagios.pop_front();
			numeroDeCiclos++;
			print();
			if (wasJump) {
				i = nextAfterJump;
				wasJump = false;
			}
			continue;
		}

		//hasConflito() procura se há conflito e passa o retorno pra uma Instrução auxiliar.
		Instrucao conflitante = hasConflito(instrucoes[i]);
		
		//Se o elemento a ser inserido tiver conflito com o atual, hasConflito() retornará uma Instrução. Caso não haja conflito, a função retorna
		// uma Instrução "null" (ou seja, se houver conflito, o nome da instrução retornada terá o nome diferente de "null").
		
		if (conflitante.getNome() != "null") {	
			//std::cout << "\n" << conflitante.getLinhaCompleta() << "\n";
			//std::cout << estagios[1].getLinhaCompleta() << "\n";
			//std::cout << estagios[0].getLinhaCompleta() << "\n";
			//std::cout << "Instrução com conflito e no tempo 0.\n";
			numeroDeCiclos++;
			//std::cout << "\n" << instrucoes[i-1].getLinhaCompleta() << "\n";
			//std::cout << estagios[1].getLinhaCompleta() << "\n\n";
			
			/*
				Se o elemento conflitante não estiver nos estágios 4, 3 e 2 do código, é inserido um novo elemento. Caso haja conflito, é avançado uma fase do pipeline.
				Por peculiaridades do código, não estar nos estágios 4, 3 e 2 significa:
					- Pode estar no 1: que é quando o elemento será inserido. Quando for inserido, o elemento conflitante estará na posição 0. Logo, o Pipeline
				imprimirá corretamente.
					- Pode estar no 0: isso pode ser possível devido à função lw, que pula um estágio sempre que há um lw no estágio 2.
					- Apesar de estar na lista de conflitos, o elemento não está mais dentro do processamento do pipeline. Ou seja, não está no vetor "estagios".
			*/
			if (conflitante.getLinhaCompleta() != estagios[4].getLinhaCompleta() 	 and
				conflitante.getLinhaCompleta() != estagios[3].getLinhaCompleta() 	 and
				conflitante.getLinhaCompleta() != estagios[2].getLinhaCompleta()) {

				estagios.push_back(instrucoes[i]);
				filaDestinos.push_back(instrucoes[i++]);
				if (filaDestinos.size() > 4) {
					filaDestinos.pop_front();
				}							
				estagios.pop_front();
				print();
				if (wasJump) {
					i = nextAfterJump;
					wasJump = false;
				}
				continue;
			}

			//Avançando um estágio do pipeline.
			estagios.push_back(null);
			estagios.pop_front();
			print();
			continue;
		}

		//Instrução sem conflito
		//O elemento é inserido imediatamente ao pipeline.

		estagios.push_back(instrucoes[i]);
		filaDestinos.push_back(instrucoes[i++]); //if fila > 4
		
		// Fila de destinos é atualizada.
		if (filaDestinos.size() > 4) {
			filaDestinos.pop_front();
		}		
		estagios.pop_front();
		numeroDeCiclos++;
		print();
		if (wasJump) {
			i = nextAfterJump;
			wasJump = false;
		}
		continue;
	}

	//Finalizando os ciclos restantes.
	for (unsigned int i; ; i++) {
		estagios.push_back(null);
		estagios.pop_front();
		//std::cout << estagios.size() << std::endl;
		
		//Só para quando todas as linhas forem vazias.
		if (estagios[4].getLinhaCompleta() == "null" and 
			estagios[3].getLinhaCompleta() == "null" and 
			estagios[2].getLinhaCompleta() == "null" and 
			estagios[1].getLinhaCompleta() == "null" and 
			estagios[0].getLinhaCompleta() == "null") {
			break;
		}

		numeroDeCiclos++;
		print();
	}
}