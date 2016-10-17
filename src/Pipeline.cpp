#include <Pipeline.h>

Pipeline::Pipeline () : numeroDeInstrucoes(0) {
}

void Pipeline::addInstrucao(Instrucao instrucao) {
	if(instrucao.isValida()) {
		instrucoes.push_back(instrucao);
		numeroDeInstrucoes++;
	}
}

Instrucao Pipeline::getElemento (unsigned int i) {
	return this->instrucoes[i];
}

unsigned int Pipeline::getNumeroDeInstrucoes() {
	return this->numeroDeInstrucoes;
}

unsigned int Pipeline::getNumeroDeCiclos() {
	return this->numeroDeCiclos;
}

void Pipeline::gerarPipeline() {
	Instrucao null;
	numeroDeCiclos = 0;
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

		//Como foi pulado um label, ela também não pode ser comparada com um elemento atual.
		//Então, se uma label é o elemento anterior, é necessário pegar o elemento anterior à label.
		int n;
		if (instrucoes[i-1].isLabel()) {
			n = i-2;
		}
		else {
			n = i-1;
		}

		//Procura se há conflito e passa o retorno pra uma instrução auxiliar.
		Instrucao conflitante = hasConflito(instrucoes[i]);
		
		//Se o elemento a ser inserido tiver conflito com o atual, retornará o conflito (e o nome será diferente de "null").
		if (conflitante.getNome() != "null") {	
			//std::cout << "\n" << conflitante.getLinhaCompleta() << "\n";
			//std::cout << estagios[1].getLinhaCompleta() << "\n";
			//std::cout << estagios[0].getLinhaCompleta() << "\n";
			//std::cout << "Instrução com conflito e no tempo 0.\n";
			numeroDeCiclos++;
			//std::cout << "\n" << instrucoes[i-1].getLinhaCompleta() << "\n";
			//std::cout << estagios[1].getLinhaCompleta() << "\n\n";
			
			//Se o elemento conflitante estiver na fase "EX" do pipeline. O novo será inserido.
			//Por causa de peculiaridades do código, é conferido o elemento 1 do deque, pois o elemento inserido agora só aparecerá na próxima impressão.
			//E caso o elemento conflitante não esteja no índice 1 do deque, é conferido o elemento 0.
			//Pois pode ser que tenha acontecido de um lw estar no estagios[2] e o código tenha pulado um índice, sendo assim, o elemento conflitante ficando no estagios[0].
			//Também é conferido se o elemento conflitante não está nos elementos 4, 3, e 2 do deque, pois pode ser que haja instruções iguais repetidas. Ou seja, não é a hora de inserir uma instrução com conflito.
			//Também é conferido se o elemento conflitante não está mais no processo de pipeline.
			
			if (((instrucoes[n].getLinhaCompleta() == estagios[1].getLinhaCompleta() or 
				conflitante.getLinhaCompleta() == estagios[0].getLinhaCompleta()) 	 and 
				conflitante.getLinhaCompleta() != estagios[4].getLinhaCompleta() 	 and 
				conflitante.getLinhaCompleta() != estagios[3].getLinhaCompleta() 	 and 
				conflitante.getLinhaCompleta() != estagios[2].getLinhaCompleta()) 	 or 

				(conflitante.getLinhaCompleta() != estagios[4].getLinhaCompleta() 	 and
				conflitante.getLinhaCompleta() != estagios[3].getLinhaCompleta() 	 and
				conflitante.getLinhaCompleta() != estagios[2].getLinhaCompleta() 	 and 
				conflitante.getLinhaCompleta() != estagios[1].getLinhaCompleta()  	 and
				conflitante.getLinhaCompleta() != estagios[0].getLinhaCompleta())) {

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

			//Se ele não estiver no último estágio, é avançado um estágio do pipeline.
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