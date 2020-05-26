#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream> //Work with files
#include<ctime>
#include<algorithm>
#include<dirent.h>

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
            (p->documents).push_back(docId);
	}

	void pesquisa(){

	    vector<int> v  = {};
	    Node *p = pRoot;
        string palavra;
        string aux;
        int auxx = 1;
        cout << "O que procuras : ";
        cin >> palavra;
        clock_t t0 = clock();

        for(int i = 0; i<palavra.length(); i++){
                int ind = index(palavra[i]);
                p = p->children[ind];
        }

        clock_t tf = clock();

        cout << "tempo de busca: " << ((float)tf- (float)t0)/CLOCKS_PER_SEC << "s" << endl;

        for(int j = 0; j<(p->documents).size(); j++) {
                if (j == 0) { cout << " resultados encontrados: "<<(p->documents).size() << endl ;}
            cout << (p->documents)[j] << " " << endl;
            if(j == (p->documents).size()-1) {cout << endl << endl <<  "encerrando pesquisa :)" << endl << endl;}

            if(j == auxx*20){cout << "tecle s para a proxima pagina: "; cin >> aux; if(aux != "s")
                {cout << endl << endl << "encerrando pesquisa :)" << endl;break;}
                else{auxx += 1;}
            }
        }

	}

	int leitura(string texto, int tf, int ch) {
        bool f;            // verifica se faz parte de um id
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
        ch += i;
        cout << "texto "  << tf << "  " << "palavras: " << ch << endl;
        return ch;
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

    clock_t t0 = clock();
    int ch = 0;
    int c = 0;
	Trie Trie;

    DIR *  dir;
    struct dirent *entry;
    dir  = opendir("../../../Desktop/sem_repet1");
    while((entry = readdir(dir)) != NULL && c<=45){
            string s = entry->d_name;
            ch = Trie.leitura("../../../Desktop/sem_repet1/"+s, c, ch);
            c = c+1;
    }
    dir  = opendir("../../../Desktop/sem_repet2");
    while((entry = readdir(dir)) != NULL ){
            string s = entry->d_name;
            ch = Trie.leitura("../../../Desktop/sem_repet2/"+s, c, ch);
            c = c+1;
    }
    dir  = opendir("../../../Desktop/sem_repet3");
    while((entry = readdir(dir)) != NULL){
            string s = entry->d_name;
            ch = Trie.leitura("../../../Desktop/sem_repet3/"+s, c, ch);
            c = c+1;
    }

    closedir(dir);
    clock_t tf = clock();
    cout <<"tempo de processamento: " << ((float)tf - (float)(t0))/CLOCKS_PER_SEC << endl;
	Trie.pesquisa();

    return 0;
}


/*for(int i = 0; i<palavra.length(); i++){
                if ( i == palavra.length()-1){
                    if( b && p != pRoot) { v = (p->documents); cout << (p->documents)[0] << " aqui "; b = false;}
                    else if(palavra != "" && p != pRoot){
                        int t1 = v[0];
                        int t2 = (p->documents)[0];
                        const int t3 = v[v.size()-1];
                        const int t4 = (p->documents)[(p->documents).size()-1];
                        while(t1 <= t3 && t2 <= t4) {
                            if((p->documents)[c] != v[c] && (p->documents)[c] > v[c]){
                                v.erase(v.begin()+c);
                                if(t1 == t3){t1 = t1+100;}
                                else {t1 = v[c];}
                            }
                            else if((p->documents)[c] != v[c] && (p->documents)[c] < v[c]){
                                (p->documents).erase((p->documents).begin()+c);
                                if(t2 == t4){t2 = t2+100;}
                                else {t2 = (p->documents)[c];}
                            }
                            else if((p)->documents[c] == v[c]) { c = c+1;}
                        }
                        if ((p->documents).size() == 0) {v = {};}
                    }
                    p = pRoot;
                }
            else{
                c = 0;
                int ind = index(palavra[i]);
                p = p->children[ind];
            }
        }*/
