#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream> //files
#include <sstream>
#include <ctime>
#include <dirent.h>
#include <set>

using namespace std;

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
    Trie(){}
    
    bool is_alphabetchar(char c){
	    return (('a' <= c && c <= 'z') or ('0' <= c && c <= '9'));
    }
    bool is_uppercase(char c){
        return ('A' <= c && c <= 'Z');
    }

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
		auto it = equal_range((p->documents).begin(), (p->documents).end(), docId);
		if (it.first == it.second){(p->documents).insert(it.first, docId);}
	}


//Searching for a word in the tree
    vector<int> search(string key){
    Node *pCurr = pRoot;
    vector<int> vec = {};
    for(int i =0; i < key.length(); i++){
        int ind = index(key[i]);
        if(!pCurr -> children[ind]){
            return vec;
        }
        pCurr = pCurr -> children[ind];
    }
    return (pCurr -> documents);
    }


	void serializa(string name){
		ofstream file;
		file.open(name);
		Node * pNode = pRoot;
		exec_serializa(pNode, file);
		}

	void exec_serializa(Node * pCur, ofstream & file){
		if ( !(pCur->documents).empty() ){
					file << "{";
					for(std::vector<int>::iterator it = pCur->documents.begin() ; it != pCur->documents.end(); ++it){
						file << *it << " ";
					}
					file << "}";
				}
		for(int i = 0 ; i < ALPHABET_SIZE ; i++ ){
			if (pCur -> children[i] != nullptr){
				file << i << " ";
				exec_serializa(pCur-> children[i], file);
			}
		}
		file << "]";
	}

	void diserializa(string name){
        ifstream file; 
        string line; 
        file.open(name);
        getline(file, line); 
        Node ** pNode = &pRoot; 
        stringstream split; 
        split << line; 
        string cur_name;
        while(split >> cur_name){
	       	if(exec_diserializa(pNode, cur_name, split)) break;
		}
    }

    bool exec_diserializa(Node ** pNode, string cur, stringstream  & split){
        if(cur == "]") return 1; //se for "]" , eu devo subir, entao retorno verdadeiro

        //se nao for um "[" , eu crio um novo node com cur

    	Node *p;

        (*pNode)->children[stoi(cur)] = p; 
        pNode = &(*pNode)->children[stoi(cur)]; 

        string isvector;string id;
        split >> isvector; //recebe o proximo valor que vai ser "{" ou " "

        if(isvector == "{"){ //se for "{"
        	split >> id; //recebo os ids

        	auto it = equal_range(((*pNode)->documents).begin(), ((*pNode)->documents).end(), stoi(id));
			if (it.first == it.second){((*pNode)->documents).insert(it.first, stoi(id));}
		}

        while(split >> cur){ //continuo recebendo strings da split
           //vou descendo, ate retorna um verdadeiro
            if(exec_diserializa(pNode, cur, split)) break;
        }
        return 0;
    }

bool isdigit (char c){
    return('0' <= c && c <= '9');
}


};

int main() {

Trie Trie;

    Trie.serializa("serializada");

    
    return 0;
}

