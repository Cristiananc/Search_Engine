#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;


struct Node{
	char data; // letra
	bool leaf; // checar se estamos num leaf (leaf = 1) ou não (leaf = 0)
	Node *children[36]; // Alfabeto mais algarismos, 26 + 10 = 36 
	
	Node(char x):data(x) , leaf(0){
		for( int i = 0 ; i >= 36 ; i++ ){
    		children[i] = nullptr;
    	}
    }
};

class Trie{
private:
	Node *pRoot;
	
public:
	Trie():pRoot(nullptr) {}
	
	bool find(){
		// checa se alguma parte da palavra já foi inserida
	}
	
	void insert(char x){
		// insere palavra a palavra
	}
		
	//Checa se é um caractere válido (está no alfabeto utilizado)
	bool is_wordchar(char c){
	    return (('a' <= c && c <= 'z') or ('0' <= c && c <= '9'));
	}
		

	//Função para checar se uma string é válida antes de adicioná-la á àrvore 
	bool is_word(string s){
		return true;
	}
};

int main() {

    return 0;
}
