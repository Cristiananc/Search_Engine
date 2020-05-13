#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;


struct Node{
	char data; // letra (futuramente prefixo)
	bool leaf; // checar se estamos num leaf (leaf = 1) ou n�o (leaf = 0)
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
	
	// checa se alguma parte da palavra j� foi inserida
	// retorna ponteiro da bifurca��o
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
		
	//Checa se � um caractere v�lido (est� no alfabeto utilizado)
	bool is_wordchar(char c){
	    return (('a' <= c && c <= 'z') or ('0' <= c && c <= '9'));
	}
		

	//Fun��o para checar se uma string � v�lida antes de adicion�-la � �rvore 
	bool is_word(string s){
		return true;
	}
	
	void search(char* word){
		
	}
};

int main() {
	
	//teste da din�nica de uma palavra alocada em um espa�o de mem�ria char 
	char* word = "arroz8";
	cout << word << endl;
	cout << word[0] << endl; 
	cout << word[5] << endl;
	cout << word[-1] << endl; // null
	
    return 0;
}
