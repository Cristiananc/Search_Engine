#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
	
	void serializacao(string name){
		ofstream file;
		file.open(name);
		Node * pNode = pRoot;
		exec_serializacao(pNode, file);
	}
	
	void exec_serializacao(Node * pCur, ofstream & file){
		for(int i = 0 ; i < ALPHABET_SIZE ; i++ ){
			if (pCur -> children[i] != nullptr){
				file << " " << i;
				for(std::vector<int>::iterator it = (pCur->documents).begin() ; it != (pCur->documents).end(); ++it){
					file << "|" << *it;
				}
				exec_serializacao(pCur-> children[i], file);
			}	
		}
		file << "]";
	}

};

int main() {
	
	Trie Trie;
	int docId1 = 8;
	int docId2 = 9;
	Trie.insert("banana", docId1);
	Trie.insert("ba",docId2);
	
	Trie.serializacao("serializa");
	
    return 0;
}
