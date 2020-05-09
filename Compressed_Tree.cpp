#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;


struct Node{
	char data; // letra
	bool leaf; // checar se estamos num leaf (leaf = 1) ou n�o (leaf = 0)
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
		// checa se alguma parte da palavra j� foi inserida
	}
	
	void insert(char x){
		// insere palavra a palavra
	}
		
	//Checa se � um caractere v�lido (est� no alfabeto utilizado)
	bool is_wordchar(char c){
	    return (('a' <= c && c <= 'z') or ('0' <= c && c <= '9'));
	}
		

	//Fun��o para checar se uma string � v�lida antes de adicion�-la � �rvore 
	bool is_word(string s){
		return true;
	}
};

int main() {

    return 0;
}
