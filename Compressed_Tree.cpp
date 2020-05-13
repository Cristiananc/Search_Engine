#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;


struct Node{
	char data; // letra (futuramente prefixo)
	bool leaf; // checar se estamos num leaf (leaf = 1) ou não (leaf = 0)
	Node *children[36]; // Alfabeto mais algarismos, 26 + 10 = 36 
	
	Node(char x):data(x) , leaf(true){
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
	
	// checa se alguma parte da palavra já foi inserida
	// retorna ponteiro da bifurcação
	bool find(char* x,Node **&p){
		p = &pRoot;
		int i = 0;
		while(*p or x[i]) {
            if ((*p)->data==x[i]){
            	p = &((*p)->children[(*p)->data == x[i+1]]);
			}
			i++;
        }
        return true ;
	}
	
	void insert(char* x){
		Node **p;
		
	}
		
	//Checa se é um caractere válido (está no alfabeto utilizado)
	bool is_wordchar(char c){
	    return (('a' <= c && c <= 'z') or ('0' <= c && c <= '9'));
	}
		

	//Função para checar se uma string é válida antes de adicioná-la á àrvore 
	bool is_word(string s){
		return true;
	}
	
	void search(char* word){
		
	}
};

int main() {
	
	//teste da dinânica de uma palavra alocada em um espaço de memória char 
	char* word = "arroz8";
	cout << word << endl;
	cout << word[0] << endl; 
	cout << word[5] << endl;
	cout << word[-1] << endl; // null
	
    return 0;
}
