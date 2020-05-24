#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream> //Work with files
#include <iomanip>
#include <ctime>
#include <locale.h>

using namespace std;

//Precisamos de uma fun��o pra serializar e pra desserializar
//Fun��o que adiciona todas as palavras do arquivo texto
//Fun��o que recebe a pesquisa do usuario e limpa a pesquisa
//Sugest�o de palavra
//Devolve o arquivo
//Ordena as p�ginas

const int ALPHABET_SIZE = 36;

struct Node{
	vector <string> documents; // cada componente do vetor será também um vetor
	Node *children[ALPHABET_SIZE]; // Alfabeto mais algarismos, 26 + 10 = 36

	Node () {for(int i = 0 ; i < 36 ; i++ ){
    	children[i] = nullptr;
    	}
	}
};

class Trie{

public:
	Node *pRoot = new Node;
	Trie() {}

	// checa se alguma parte da palavra já foi inserida
	// retorna ponteiro da bifurcação
	// bool find(char* x,Node **&p){
	// 	p = &pRoot;
	// 	int i = 0;
	// 	while(*p or x[i]) {
    //         if ((*p)->data==x[i]){
    //         	p = &((*p)->children[(*p)->data == x[i+1]]);
	// 		}
	// 		i++;
    //     }
    //     return true ;
	// }

	//Auxiliar function to find corresponding index
	int index(char c){
	    if( c == '_') {int index = 35;}
	    if ('a' <= c && c <= 'z'){int index = c - 'a';}
	    else if('0' <= c && c <= '9'){int index = c-'0'+26;}
    		else{int index = c - 'a' + 'z';}
	}

	void insert(string word, string docId){ // a palavra é uma string e o id um vetor de chars
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
		(p -> documents).push_back(docId);
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

	void le(string texto) {
        clock_t t0;
        string title;       // titulo do texto atual
        bool t;             // verifica se faz parte de um titulo
        bool f;             // verifica se faz parte de um id
        int i = 0;          // conta as palavras
        string ids;         // lista de ids
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
                        ids = "";   //  apago id antigo
                        title = ""; //apago titulo antigo
                        t = true;
                        for(int i = 3; i< word.size();i++) {
                            ids = ids+word[i]; // registrando IDs
                        }
                        word = "";
                        f = false;
                        i ++;
                    }
                    else if(word == ""){ // me livrando dos espaços e endlines
                            if (c == '\n') {t = false;}
                    }
                    else {
                        if(t && c != '\n' && word != "title") {title = title+word+" ";} //reconhecendo palavras do titulo
                        else if(word == "") {t = false;} // reconhecendo termino do titulo
                        if(!t){     // titulos não precisam ser inseridos
                            insert(word, ids); // chamando a função de insertar
                        }
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

        clock_t ti = ((float)clock() - t0)/CLOCKS_PER_SEC; // calculando tempo em segundos
        cout << ti << endl << i;
    }

    void leitura() {

        string p;
        char arq[8];
        for(int i = 1; i <9; i++){
            p = itoa(10000*i, arq, 10); // o numero do texto
            p = ".ipynb_checkpoints/texto_"+p+".txt"; //  o nome do arquivo, por enquanto é só uma pasta de teste
            cout <<"  " << p << endl;
            le(p); // chama a função pra ler e registrar com a "insert"
    }

    }

};

int main() {
	//teste da dinânica de uma palavra alocada em um espaço de memória char


	Trie Trie;
	string docId = "2";
	string s = "ab";
	//Trie.insert(s, docId);
	Trie.leitura();

    return 0;
}
