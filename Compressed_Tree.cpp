#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream> //Work with files
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
	    if ('a' <= c && c <= 'z'){int index = c - 'a';}
    		else{int index = c - 'a' + 'z';}
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
};

int main() {
	//teste da dinânica de uma palavra alocada em um espaço de memória char 
	char* word = "arroz8";
	cout << word << endl;
	cout << word[0] << endl; 
	cout << word[5] << endl;
	cout << word[-1] << endl; // null
	
	Trie Trie;
	int docId = 2;
	Trie.insert("ab", docId);
	
    return 0;
}