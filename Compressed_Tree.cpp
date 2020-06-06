#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream> //Work with files
#include<ctime>
#include<algorithm>

using namespace std;

//Precisamos de uma fun��o pra serializar e pra desserializar
//Fun��o que adiciona todas as palavras do arquivo texto
//Fun��o que recebe a pesquisa do usuario e limpa a pesquisa
//Sugest�o de palavra
//Devolve o arquivo
//Ordena as p�ginas

const int ALPHABET_SIZE = 36;

struct Node{
	vector<int> documents;
	Node *children[ALPHABET_SIZE]; // Alfabeto mais algarismos, 26 + 10 = 36

	Node () {for(int i = 0 ; i < ALPHABET_SIZE ; i++ ){
    	children[i] = nullptr;
    	}
	}
};

class Trie{

public:
	Node *pRoot = new Node;
	Trie() {}

	//Auxiliar function to find corresponding index
	int index(char c){
	    if ('a' <= c && c <= 'z'){
			int index = c - 'a' + 10;
			}
    	else if ('0' <= c && c <= '9'){
			int index = c - '0';
		}
	}

	void insert(string word, int docId){
		Node *p = pRoot;
		Node *pChar;
		for (int i = 0; i < word.length() ; i++){
		    int ind = index(word[i]);
    		if(p -> children[ind] == nullptr){
    		    pChar = new Node();
    		    p -> children[ind] = pChar;
    		}
    	    p = p -> children[ind];
		}

		auto it = equal_range((p->documents).begin(), (p->documents).end(), docId);
		if (it.first == it.second){(p->documents).insert(it.first, docId);}

	}

	void pesquisa(){
	    vector<int> v  = {};
	    Node *p = pRoot;
        string palavra;
        string aux;
        int auxx = 1;
        cout << "O que procuras (digite s para pesquisar): ";
        cin >> palavra;
        for(int i = 0; i<palavra.length(); i++){
                int ind = index(palavra[i]);
                p = p->children[ind];
        }
        for(int f = 0; f<(p->documents).size();f++) {
            auto it = equal_range(v.begin(), v.end(), (p->documents)[f]);
            if (it.first == it.second){v.insert(it.first, (p->documents)[f]);}
        }
        for(int j = 0; j<v.size(); j++) {
            cout << v[j] << " " << endl;
            if(j == v.size()-1) {cout << endl << endl <<  "encerrando pesquisa :)" << endl << endl;}

            if(j == auxx*20){cout << "tecle s para a proxima pagina: "; cin >> aux; if(aux != "s")
                {cout << endl << endl << "encerrando pesquisa :)" << endl;break;}
                else{auxx += 1;}
            }
        }

	}

	void leitura(string texto) {
        clock_t t0 = clock();
        bool f;             // verifica se faz parte de um id
        int i = 0;          // conta as palavras
        int id;
        string word ;       // a palavra de cada iteraçao
        char c ;            // a letra em cada iteração
        char c2;            // a letra da iteração anterior
        ifstream arquivo;   // arquivo a ser lido

        arquivo.open(texto);
        if(arquivo.is_open()){

            while(arquivo.get(c)) {

                if (c == ' ' or c == '\n'){ // reconhecendo término de uma palavra
                    if(c == ' ' && c2 == '\n') { f = true;
                    }
                    if (f && word[0] == 'i' && word[1] == 'd' && word[2] == '=' && isdigit(word[3]) ){
                        id = stoi(word.substr(3));
                        word = "";
                        f = false;
                        i ++;
                    }
                    else if(word == ""){
                    }
                    else {
                        insert(word, id); // chamando a função de insertar
                        word = ""; // reinicio como vazia a variável word
                        i ++;
                        f = false;
                    }
                }
                else {
                    word = word+c; // acrescento �  palavra o char atual
                }
                c2 = c;
            }
        }
        arquivo.close();

        clock_t tf = ((float)(clock()-t0))/CLOCKS_PER_SEC; // calculando tempo em segundos
        cout << "segundos: "  << tf << endl << "palavras: " << i << endl;
    }


	//Checa se � um caractere v�lido (est� no alfabeto utilizado)
	bool is_wordchar(char c){
	    return (('a' <= c && c <= 'z') or ('0' <= c && c <= '9'));
	}


	//Fun��o para checar se uma string � v�lida antes de adicion�-la � �rvore
	bool is_word(string word){
		return true;
	}

	void search(string word){

	}

	void serializa(string name){
		ofstream file;
		file.open(name);
		Node * pNode = pRoot;
		exec_serializa(pNode, file);
	}

	void exec_serializa(Node * pCur, ofstream & file){
		if ( !(pCur->documents).empty() ){
					file << "{";
					for(std::vector<int>::iterator it = pCur->documents.begin() ; it != pCur->documents.end(); ++it){
						file << *it << " ";
					}
					file << "}";
				}
		for(int i = 0 ; i < ALPHABET_SIZE ; i++ ){
			if (pCur -> children[i] != nullptr){
				file << i << " ";
				exec_serializa(pCur-> children[i], file);
			}
		}
		file << "]";
	}

	void diserializa(string name){
        ifstream file; //file do tipo input
        string line; //string para pegar a primeira linha da file
        file.open(name);
        getline(file, line); //peguei a primeira linha
        Node ** pNode = &pRoot; //ponteiro duplo pois é a mesma ideia do insert da linkedlist
        stringstream split; //stringstream para receber a linha da file
        split << line; //passei line para o split
        string cur_name;
        while(split >> cur_name){
	       	if(exec_diserializa(pNode, cur_name, split)) break;
		}
    }

    bool exec_diserializa(Node ** pNode, string cur, stringstream  & split){
        if(cur == "]") return 1; //se for um parenteses, eu devo subir, então retorno verdadeiro

    	Node *p = pRoot;
    	Node *pChar;
    	if(p -> children[stoi(cur)] == nullptr){
    	    pChar = new Node();
    	    p -> children[stoi(cur)] = pChar;
    	}
    	p = p -> children[stoi(cur)];


        //Node * pNew = new Node(cur_name); //se não for um parenteses, eu crio um novo nó com essa string

        (*pNode)->children[stoi(cur)] = p; //digo que é filho do pNode da atual recursão
        pNode = &(*pNode)->children[stoi(cur)]; //caminho para esse filho

        string isvector;string id;
        split >> isvector; //recebe o pr�ximo valor que vai ser "{" ou " "

        //(*pNode)->end = stoi(end);

        if(isvector == "{"){ //se for "{"
        	split >> id; //recebo os ids

        	//(*pNode)->documents.pushback( stoi(id) ); //e salvo
		}

        while(split >> cur){ //continuo recebendo strings da split
            //vou descendo, até retorna um verdadeiro
            if(exec_diserializa(pNode, cur, split)) break;
        }
        return 0;
    }


};

int main() {

	Trie Trie;
	int docId1 = 8;
	int docId2 = 9;
	Trie.insert("ab4", docId1);
	Trie.insert("abc",docId2);
	Trie.insert("abc",docId1);


	Trie.serializa("serializa");
	Trie.diserializa("serializa");


    return 0;
}
