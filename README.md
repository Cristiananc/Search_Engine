# Search_Engine

O trabalho que se encontra neste repositório foi feitos pelos estudantes: Cristiana, Hanna e Marcos para a disciplina de Estrutura de dados e algoritmos da EMAp ministrada pelo professor Jorge Poco.

No arquivo Search.cpp encontra-se a implementação da estrutura de dados Trie utilizada para construir a árvore de palavras com o corpus do Wikipedia em inglês, baixado em http://www.cs.upc.edu/~nlp/wikicorpus/. Estão nesse repositório implementados os algoritmos de pesquisa e outras funções auxiliares.

# Como executar a search engine?

Faça o download do corpus processado no seguinte link: https://github.com/Marcos358/3periodo. As pastas "for_tree" e "originais_ordenados" devem estar na mesma pasta dos arquivos Search.cpp, executeSearch.cpp e demais arquivos deste repositório.

Além dos pacotes padrão do c++, você precisa ter os seguintes pacotes: dirent.h e set.

Para rodar a search engine no terminal, pode se utilizar o compilador g++ (ou outro programa de sua preferência):
g++ executeSearch.cpp
./a.out

Para rodar a interface web da search engine usando um servidor local é preciso que você tenha instalada em seu computador o pacote boost (https://www.boost.org/). 

Feito isso, para executar basta abrir o terminal na pasta "web-server" e digitar: g++ main.cpp -I /usr/include -lboost_system -lboost_thread -lpthread.

Para visualizar a página acesse http://localhost:8080/index.html.


