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

void Pipeline::gerarPipeline() {
	Instrucao null;
	numeroDeCiclos = 0;
	estagios.assign(5, null);

	for (unsigned int i = 0; i < instrucoes.size(); ) {
		//std::cout << "\ni = " << i << "\n";
		//std::cout << instrucoes[i].isLabel() << "\n";

		//Se a "instrução" for uma label, pula.
		if (instrucoes[i].isLabel()) {
			i++;
			continue;
		}

		//std::cout << "\nj = " << j << "\n";
		//Primeira instrução.
		if (i == 0) {
			//std::cout << "Primeira instrução!\n";
			filaDestinos.push_back(instrucoes[i]);
			
			if (filaDestinos.size() > 4) {
				filaDestinos.pop_front();
			}
			
			estagios.push_back(instrucoes[i++]);
			estagios.pop_front();
			numeroDeCiclos++;
			print();
			
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

		//Se o elemento a ser inserido tiver conflito com o atual.
		if (hasConflito(instrucoes[i])) {
			//std::cout << "Instrução com conflito e no tempo 0.\n";
			numeroDeCiclos++;
			//std::cout << "\n" << instrucoes[i-1].getLinhaCompleta() << "\n";
			//std::cout << estagios[1].getLinhaCompleta() << "\n\n";
			
			//Se o elemento anterior ao que será inserido estiver no último estágio do pipeline, é inserido o atual.
			if (instrucoes[n].getLinhaCompleta() == estagios[1].getLinhaCompleta()) {
				//std::cout << "Teste\n";
				filaDestinos.push_back(instrucoes[i]); //if fila > 4
				
				if (filaDestinos.size() > 4) {
					filaDestinos.pop_front();
				}

				estagios.push_back(instrucoes[i++]);
				estagios.pop_front();
				print();
				continue;
			}

			//Se ele não estiver no último estágio, é avançado um estágio do pipeline.
			estagios.push_back(null);
			estagios.pop_front();
			print();
			continue;
		}

		//Instrução sem conflito
		//std::cout << "Instrução sem conflito no tempo 0!\n";
		filaDestinos.push_back(instrucoes[i]); //if fila > 4
		
		// Fila de destinos é atualizada.
		if (filaDestinos.size() > 4) {
			filaDestinos.pop_front();
		}
		
		// O elemento é inserido imediatamente ao pipeline.
		estagios.push_back(instrucoes[i++]);
		estagios.pop_front();
		numeroDeCiclos++;
		print();
		continue;
	}

	//Finalizando os ciclos restantes.
	for (unsigned int i; ; i++) {
		estagios.push_back(null);
		estagios.pop_front();

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

bool Pipeline::hasConflito(Instrucao instrucao) {
	for (unsigned int k = 0; k < filaDestinos.size(); k++){
		if (instrucao.getFonte1() == filaDestinos.at(k).getDestino())
			return true;
		if (instrucao.getFonte2() == filaDestinos.at(k).getDestino())
			return true;
	}
	return false;
}

void Pipeline::print() {
		std::cout << "\nCiclo " << numeroDeCiclos << "\n";
		std::cout << estagios.at(4).getLinhaCompleta() << "\n";
		std::cout << estagios.at(3).getLinhaCompleta() << "\n";
		std::cout << estagios.at(2).getLinhaCompleta() << "\n";
		std::cout << estagios.at(1).getLinhaCompleta() << "\n";
		std::cout << estagios.at(0).getLinhaCompleta() << "\n";
}