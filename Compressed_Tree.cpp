#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream> //Work with files
using namespace std;

//Precisamos de uma funï¿½ï¿½o pra serializar e pra desserializar
//Funï¿½ï¿½o que adiciona todas as palavras do arquivo texto
//Funï¿½ï¿½o que recebe a pesquisa do usuario e limpa a pesquisa
//Sugestï¿½o de palavra
//Devolve o arquivo
//Ordena as pï¿½ginas

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
		
	//Checa se ï¿½ um caractere vï¿½lido (estï¿½ no alfabeto utilizado)
	bool is_wordchar(char c){
	    return (('a' <= c && c <= 'z') or ('0' <= c && c <= '9'));
	}
		

	//Funï¿½ï¿½o para checar se uma string ï¿½ vï¿½lida antes de adicionï¿½-la ï¿½ ï¿½rvore 
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
	Trie.insert("abc", docId1);
	Trie.insert("abd",docId2);
	
	Trie.serializacao("serialização");
	
    return 0;
}
