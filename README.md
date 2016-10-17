# Pipeline Simulator

Simulador de Pipeline produzido como um projeto da disciplina Introdução à Organização e Arquitetura de Computadores (2016.2).

# Funcionamento

O funcionamento desse simulador se dá através da leitura de um arquivo com instruções em Assembly. As instruções são lidas, validadas e armazenadas em um vetor que contém instruções e labels. A partir do vetor é gerado o pipeline. A estratégia tomada para caso haja presença de jumpers foi a de sempre ir para a label.

# Compilação

Para compilar, entre na pasta do projeto pelo terminal e use o comando:

`make`

ou

`g++ -Wall -std=c++11 src/Main.cpp src/Instrucao.cpp src/Pipeline.cpp -o bin/pipeline-simulator -I  include/`

Para executar, basta usar o comando:

`./bin/pipeline-simulator <arquivo com as instruções>`

Um exemplo de execução é:

`./bin/pipeline-simulator data/Teste2.txt`

#Thanks

- Yuri Alessandro (makefile, projeto passado, relatório), github.com/YuriAlessandro;
- Yuri Reinaldo (projeto passado), github.com/Yuri-wrlk;
- Elton Viana (makefile), github.com/eltonvs.