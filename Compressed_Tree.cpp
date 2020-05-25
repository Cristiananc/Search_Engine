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
		//end of word
		//(p -> documents).push_back(docId);
		auto it = equal_range((p->documents).begin(), (p->documents).end(), docId);
		if (it.first == it.second){(p->documents).insert(it.first, docId);}
		//bool b = binary_search((p->documents).begin(), (p->documents).end(), docId);
		//if(!b){auto it = lower_bound((p->documents).begin(), (p->documents).end(), docId);
		//(p->documents).insert(it, docId);
		//}
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
                    word = word+c; // acrescento à palavra o char atual
                }
                c2 = c;
            }
        }
        arquivo.close();
        //cout << ((((((pRoot)->children[23])->children[28])->children[29])->children[23])->documents)[2l] << endl;

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

	void serializacao(string name){
		ofstream file;
		file.open(name);
		Node * pNode = pRoot;
		exec_serializacao(pNode, file);
	}

	void exec_serializacao(Node * pCur, ofstream & file){
		for(int i = 0 ; i < ALPHABET_SIZE ; i++ ){
			if (pCur -> children[i] != nullptr){
				file << i ;
				for(int j = 0 ; j < (pCur->documents).size(); j++ ){// nao ta escrevendo no file
					file << " " << (pCur -> documents)[j] << " ";
				}
				exec_serializacao(pCur-> children[i], file);
			}
		}
		file << "]";
	}

	void disserializacao(string name){
		ifstream file;
		string line;
        file.open(name);
        getline(file, line);
        Node ** pNode = &pRoot;
        stringstream split;
        split << line;
        exec_pRoot_disserializacao(pNode, split);
	}

	void exec_pRoot_disserializacao(Node ** pNode, stringstream & split){
        string cur_word;
        while(split >> cur_word){
            if(exec_disserializacao(pNode, cur_word, split)) break;
        }
    }

    bool exec_disserializacao(Node ** pNode, string cur_word, stringstream  & split){
        if(cur_word == "]") return 1;

        //Node * pNew = new Node(cur_word);
        //(*pNode)->children[cur_word] = pNew;
        //pNode = &(*pNode)->children[cur_word];

        while(split >> cur_word){
            if(exec_disserializacao(pNode, cur_word, split)) break;
        }
        return 0;
    }
};

int main() {

	Trie Trie;
	int docId1 = 8;
	int docId2 = 9;
	Trie.insert("abc4", docId1);
	Trie.insert("abd",docId2);

	Trie.serializacao("serializa��o");
	Trie.leitura("TEXTO_00.txt");
	Trie.pesquisa();
	//cout << (Trie.pRoot.children[10].children.[20].children[0].children[11].children[0].documents).size();

    return 0;
}
