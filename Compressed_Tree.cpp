#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream> //Work with files
using namespace std;

//Precisamos de uma função pra serializar e pra desserializar
//Função que adiciona todas as palavras do arquivo texto
//Função que recebe a pesquisa do usuario e limpa a pesquisa
//Sugestão de palavra
//Devolve o arquivo
//Ordena as páginas


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
	
	//Função auxiliar pra definir o index
	
	int index(char c){
	    if ('a' <= c && c <= 'z'){int index = c - 'a';}
    		else{int index = c - 'a' + 'z';}
	}
	
	//Erro de segmentação
	void insert(string word){
		Node *p = pRoot;
		Node *pChar;
		//Só preciso fazer o insert se a busca da palavra deu falso no search
		for (int i = 0; i < word.length() ; i++){
		    int ind = index(word[i]);
    		if(p -> children[ind] == nullptr){
    		    pChar = new Node(word[i]);
    		    p -> children[ind] = pChar;
    		}
    	    p = p -> children[ind];
		}
		//end of word
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
	
	Trie Trie;
	Trie.insert("oi");
	
    return 0;
}
