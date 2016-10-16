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

for (unsigned int i = 0; i < instrucoes.size();) {
	//std::cout << "\ni = " << i << "\n";
		for(unsigned int j = 0; j < 5; j++) {
			//std::cout << "\nj = " << j << "\n";
			if (i == 0 and j == 0) {
				//std::cout << "Primeira instrução!\n";
				//numeroDeCiclos++;
				filaDestinos.push_back(instrucoes[i]);
				if (filaDestinos.size() > 4) filaDestinos.pop_front();
				estagios.push_back(instrucoes[i++]);
				estagios.pop_front();
				numeroDeCiclos++;
				print();
				if (!(i < instrucoes.size())) break;
				continue;
			} 

			if (hasConflito(instrucoes[i])) {
				if (j == 0) {
					//std::cout << "Instrução com conflito e no tempo 0.\n";
					numeroDeCiclos++;
					//std::cout << "\n" << instrucoes[i-1].getLinhaCompleta() << "\n";
					//std::cout << estagios[1].getLinhaCompleta() << "\n\n";
					if (instrucoes[i-1].getLinhaCompleta() == estagios[1].getLinhaCompleta()) {
					//	std::cout << "Teste\n";
						filaDestinos.push_back(instrucoes[i]); //if fila > 4
						if (filaDestinos.size() > 4) filaDestinos.pop_front();
						estagios.push_back(instrucoes[i++]);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;
					}
						estagios.push_back(null);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;
				}
				if (j == 1) {
					//std::cout << "Instrução com conflito e no tempo 1.\n";
					numeroDeCiclos++;
					//std::cout << "\n" << instrucoes[i-1].getLinhaCompleta() << "\n";
					//std::cout << estagios[1].getLinhaCompleta() << "\n\n";
					if (instrucoes[i-1].getLinhaCompleta() == estagios[1].getLinhaCompleta()) {
						//std::cout << "Teste\n";
						filaDestinos.push_back(instrucoes[i]); //if fila > 4
						if (filaDestinos.size() > 4) filaDestinos.pop_front();
						estagios.push_back(instrucoes[i++]);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;
					}
						estagios.push_back(null);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;
				}
				if (j == 2) {
					//std::cout << "Instrução com conflito e no tempo 2.\n";
					numeroDeCiclos++;
					//std::cout << "\n" << instrucoes[i-1].getLinhaCompleta() << "\n";
					//std::cout << estagios[1].getLinhaCompleta() << "\n\n";
					if (instrucoes[i-1].getLinhaCompleta() == estagios[1].getLinhaCompleta()) {
						//std::cout << "Teste\n";
						filaDestinos.push_back(instrucoes[i]); //if fila > 4
						if (filaDestinos.size() > 4) filaDestinos.pop_front();
						estagios.push_back(instrucoes[i++]);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;						
					}
						estagios.push_back(null);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;			
				}
				if (j == 3) {
					//std::cout << "Instrução com conflito e no tempo 3.\n";
					numeroDeCiclos++;
					//std::cout << "\n" << instrucoes[i-1].getLinhaCompleta() << "\n";
					//std::cout << estagios[1].getLinhaCompleta() << "\n\n";
					if (instrucoes[i-1].getLinhaCompleta() == estagios[1].getLinhaCompleta()) {
						//std::cout << "Teste\n";
						filaDestinos.push_back(instrucoes[i]); //if fila > 4
						if (filaDestinos.size() > 4) filaDestinos.pop_front();
						estagios.push_back(instrucoes[i++]);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;						
					}
						estagios.push_back(null);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;
				}

				if (j == 4) {
					//std::cout << "Instrução com conflito e no tempo 4.\n";
					numeroDeCiclos++;
					//std::cout << "\n" << instrucoes[i-1].getLinhaCompleta() << "\n";
					//std::cout << estagios[1].getLinhaCompleta() << "\n\n";
					if (instrucoes[i-1].getLinhaCompleta() == estagios[1].getLinhaCompleta()) {
						//std::cout << "Teste\n";
						filaDestinos.push_back(instrucoes[i]); //if fila > 4
						if (filaDestinos.size() > 4) filaDestinos.pop_front();
						estagios.push_back(instrucoes[i++]);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;						
					}
						estagios.push_back(null);
						estagios.pop_front();
						print();
						if (!(i < instrucoes.size())) break;
						continue;
				}
			} 

			if (j == 0) {
				//std::cout << "Instrução sem conflito no tempo 0!\n";
				filaDestinos.push_back(instrucoes[i]); //if fila > 4
				if (filaDestinos.size() > 4) filaDestinos.pop_front();
				estagios.push_back(instrucoes[i++]);
				estagios.pop_front();
				numeroDeCiclos++;
				print();
				if (!(i < instrucoes.size())) break;
				continue;
			}
			if (j == 1) {
				//std::cout << "Instrução sem conflito no tempo 0!\n";
				filaDestinos.push_back(instrucoes[i]); //if fila > 4
				if (filaDestinos.size() > 4) filaDestinos.pop_front();
				estagios.push_back(instrucoes[i++]);
				estagios.pop_front();
				numeroDeCiclos++;
				print();
				if (!(i < instrucoes.size())) break;
				continue;
			}
			if (j == 2) {
				//std::cout << "Instrução sem conflito no tempo 0!\n";
				filaDestinos.push_back(instrucoes[i]); //if fila > 4
				if (filaDestinos.size() > 4) filaDestinos.pop_front();
				estagios.push_back(instrucoes[i++]);
				estagios.pop_front();
				numeroDeCiclos++;
				print();
				if (!(i < instrucoes.size())) break;
				continue;
			}
			if (j == 3) {
				//std::cout << "Instrução sem conflito no tempo 0!\n";
				filaDestinos.push_back(instrucoes[i]); //if fila > 4
				if (filaDestinos.size() > 4) filaDestinos.pop_front();
				estagios.push_back(instrucoes[i++]);
				estagios.pop_front();
				numeroDeCiclos++;
				print();
				if (!(i < instrucoes.size())) break;
				continue;
			}
			if (j == 4) {
				//std::cout << "Instrução sem conflito no tempo 0!\n";
				filaDestinos.push_back(instrucoes[i]); //if fila > 4
				if (filaDestinos.size() > 4) filaDestinos.pop_front();
				estagios.push_back(instrucoes[i++]);
				estagios.pop_front();
				numeroDeCiclos++;
				print();
				if (!(i < instrucoes.size())) break;
				continue;
			}
		}
	}
	// Finalizando os ciclos.
		for (unsigned int i; ; i++) {
			estagios.push_back(null);
			estagios.pop_front();
			if (estagios[4].getLinhaCompleta() == "null" 
				and estagios[3].getLinhaCompleta() == "null"
				and estagios[2].getLinhaCompleta() == "null"
				and estagios[1].getLinhaCompleta() == "null"
				and estagios[0].getLinhaCompleta() == "null")
					break;
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