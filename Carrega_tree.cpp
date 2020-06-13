#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream> //files
#include <sstream>
#include <ctime>
#include <dirent.h>
#include <set>

#include <typeinfo>

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
    bool continu_searc = true;  // identifica se o usuario quer continuar a pesquisar
    //Checks if a char belongs to the alphabet being used.
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

	void printa(int id) {

        ifstream arquivo;               // arquivo a ser lido
        string line = "";               // a linha em cada iteração
        int ID = id/10000;              // o módulo id por 10000
        bool b = false;                 // para saber se já iniciamos a leitura do texto em questão
        int t = to_string(id).size();
        arquivo.open("retorna/orig_docc_"+to_string(ID)+".txt");   // abrindo arquivo
        if(arquivo.is_open()) {
            while(getline(arquivo, line)) {
                    line = line+'\n';
                    if(line.size() >= 8+t) {
                        if (line.substr(0,8+t) == "<doc id="+to_string(id)) {   //verifica se o id corresponde
                            b = true;
                            cout << line << endl;
                            line = "";
                        }
                        else if(line.size() >= 12) {
                            if(line.substr(0,12) == "ENDOFARTICLE" && b) { break;}  //verifica se é o final de um texto
                            else {if(b) {cout << line;} line = "";}
                        }
                        else { if(b) {cout << line;} line = "";}
                    }
                    else if(line.size() >= 12 && b) {
                        if (line.substr(0,12) == "ENDOFARTICLE" && b) { break;}
                        else {if(b) {cout << line;} line = "";}
                    }
                    else if(b) {cout << line;}
            }
        }
        arquivo.close();


    }

void leitura(string texto) {
        clock_t t0 = clock();
        bool f;             // verifica se faz parte de um id
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
        //cout << ((((((pRoot)->children[23])->children[28])->children[29])->children[23])->documents)[2l] << endl;

        clock_t tf = ((float)(clock()-t0))/CLOCKS_PER_SEC; // calculando tempo em segundos
        cout << "segundos: "  << tf << endl << "palavras: " << i << endl;
    }
    
    //Clean the user-input considering the alphabet used in the trie and split words if necessary
    vector<string> clean_input(string words){
    vector<string> wordsToSearch;
    // Char to convert (numbers as represented in ascci)
    vector<int> a{65, 131, 132, 133, 134, 142, 143, 160, 181, 182, 183, 198, 199};
    vector<int> e{69, 130, 136, 137, 138, 144, 210, 211, 212};
    vector<int> i{73, 139, 140, 141, 161, 214, 215, 216};
    vector<int> o{79, 147, 148, 149, 153, 162, 224, 226, 227, 228, 229};
    vector<int> u{85, 129, 150, 151, 154, 163, 233, 234, 235};
    vector<int> c{67,128,135};
    string word_clean;

    for (int j= 0; j < words.length(); j++){
        int letter = (int) words[j];
        //I have to check if the char is in the alphabet, if so
        if (is_alphabetchar(words[j])){word_clean.push_back(words[j]);
        }
        else if(is_uppercase(words[j])){word_clean.push_back(tolower(words[j]));
        }
        else if (find(a.begin(), a.end(), letter) != a.end()){word_clean.push_back('a');}
        else if (find(e.begin(), e.end(), letter) != e.end()){word_clean.push_back('e');
        }
        else if (find(i.begin(), i.end(), letter) != i.end()){word_clean.push_back('i');
        }
        else if(find(o.begin(), o.end(), letter) != o.end()){word_clean.push_back('o');
        }
        else if(find(u.begin(), u.end(), letter) != u.end()){word_clean.push_back('u');
        }
        else if(find(c.begin(), c.end(), letter) != c.end()){word_clean.push_back('c');
        }
        else if(words[j] == ' '){
            wordsToSearch.push_back(word_clean);
            word_clean.clear();
        }
    }
    if(word_clean.length() > 0){
        wordsToSearch.push_back(word_clean);
    }
    return wordsToSearch;
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
				file << " |";
				for(std::vector<int>::iterator it = pCur->documents.begin() ; it != pCur->documents.end(); ++it){
					file << " " << *it ;
				}
				file << " |";
			}
		for(int i = 0 ; i < ALPHABET_SIZE ; i++ ){
			if (pCur -> children[i] != nullptr){
				file << " " << i;
				exec_serializa(pCur-> children[i], file);
			}
		}
		file << " ]";
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
		
        if(cur == "|"){ //se for "|" a seguir � um id
            cout << endl;
        	string id;
        	while(split >> id){
        		if(id == "|") break;
        		cout << id << " ";
        		((*pNode)->documents).push_back(stoi(id));
			}
		}
		
		else{
			cout << cur;
			Node *p = new Node;
			(*pNode)->children[stoi(cur)] = p; 
        	pNode = &(*pNode)->children[stoi(cur)];
		}
        while(split >> cur){ //continuo recebendo strings da split
           //vou descendo, ate retorna um verdadeiro
            if(exec_diserializa(pNode, cur, split)) break;
        }
        return 0;
    }
    


//Return titles sorted
    void getTitle(vector<int> ids){
        ifstream titlesFile;
        string line;
        //Exemplo
        titlesFile.open("titulos.txt");
        int countLine = 0;
        int indexVec = 0;
        string aux;
        int numberOfTitles = 1;
        if(!titlesFile){
            cerr << "Não foi possível abrir o arquivo contendo a página de títulos";
            exit(1); //call system to stop
        }
        else{
            while(getline(titlesFile, line) && indexVec < ids.size()){
                int a = ids[indexVec];
                if(countLine == a){
                    cout << "[" << indexVec + 1 << "] " << line << endl;
                    ++ indexVec;

                    if(indexVec == ids.size()) {cout << endl;
                    cout << "tecle r + ENTER para encerrar, outra tecla + ENTER para sair ou o numero do texto escolhido: "; cin >> aux;
                    bool b2 = true;
                    for(int i = 0; i < aux.size(); i++) {
                        if (!isdigit(aux[i])) {b2 = false;}
                    }
                    if(aux != "" && b2) {printa(ids[stoi(aux)-1]); cout << endl << ids[stoi(aux)-1] << endl; break;}
                    else if(aux == "r") {continu_searc = false; break;}
                     cout <<  "encerrando pesquisa para a palavra :)" << endl << endl;}

                    if(indexVec == numberOfTitles*20){
                    cout << "tecle s + ENTER para a proxima pagina, outra tecla + ENTER para sair, r para encerrar ou o numero do texto escolhido: "; cin >> aux;
                    bool b2 = true;
                    for(int i = 0; i < aux.size(); i++) {
                        if (!isdigit(aux[i])) {b2 = false;}
                    }
                    if(aux != "" && b2) {printa(ids[stoi(aux)-1]); cout << endl << ids[stoi(aux)-1] << endl; break;}
                    else if(aux == "r") {continu_searc = false; break;}
                    else if(aux != "s")
                        {cout << endl << endl << "encerrando pesquisa :)" << endl; break;}
                    else{numberOfTitles += 1;}
                    }
                }
                ++ countLine;
            }
        titlesFile.close();
        }
    }

    void search_words(vector<string> words, vector<int> &ids){
        vector<int> ids2;

        ids = search(words[0]);
        for(int i = 1; i < words.size(); i++){
                ids2 = search(words[i]);
                ids = intersection(ids, ids2);
            }
    }

//Do the search in the tree for each word returned from the clean-input function
    void executeSearch(){
	    Node *p = pRoot;
        string word;
        vector<string> words;
        int auxx = 1;

        while(continu_searc){
        cout << "O que procuras (aperte ENTER para pesquisar): " << endl;
        getline(cin, word);
        words = clean_input(word);

        if(words.size() > 0){
        vector<int> ids;
        clock_t t0 = clock();
        search_words(words, ids);

        double tf = ((double)(clock()-t0))/(CLOCKS_PER_SEC/1000); // calculando tempo em segundos
        cout << "(" << tf << " segundos)" << endl;
        cout << "Foram encontrados " << ids.size() << " resultados para sua pesquisa!" << endl;

        if (ids.size() == 0){
            cout << "Desculpe, não encontramos sua pesquisa para " << word << " :(" << endl;
            set<string> suggestions = {};
            int nSugges = 5;
            if(words.size() == 1){
                suggestion(words[0], suggestions, nSugges);
                if(suggestions.size() > 0){
                    cout << "Você quis dizer: " << endl;
                    int count = 1;
                    for (set<string>::iterator it = suggestions.begin(); it != suggestions.end(); ++it) {
                    cout << "[" << count << "]" << *it << endl;
                    count++;
                    }
                    char aux;
                    cout << "tecle o número da sugestão + ENTER para pesquisá-la: "; cin >> aux;
                    int ia = aux - '0' - 1;
                    if(0 <= ia < suggestions.size()){
                    string x = *next(suggestions.begin(), ia);
                    vector<string> wordSug = {x};
                    search_words(wordSug, ids);
                    cout << "Pagínas encontradas para: " << x << endl;
                    getTitle(ids);
                    }
                }
            }
        }
        else{
            cout << "Pagínas encontradas para: " << word << endl;
            getTitle(ids);
        }
    }

    cin.ignore();
    }
}

	//Intersecao de ids no caso de mais de uma palavra sendo pesquisada
	vector<int> intersection(vector<int> ids1, vector<int> ids2){
	    vector<int> idsIntersec = {};
	    int i = 0;
	    int j = 0;
	    while(i < ids1.size() && j < ids2.size()){
	    if(ids1[i] == ids2[j]){
	        idsIntersec.push_back(ids1[i]);
	        i ++;
	        j ++;
	    }
	    else if(ids1[i] < ids2[j]){i ++;}
	    else{j ++;}
	}
	return idsIntersec;
	}

	//Suggestion of words
	//Its given a word that wasn't find in the trie and returns a suggestion
	 void edits1(string word, vector<string> &results){
	    //Deletion
	    for(int i = 0; i < word.size(); i++){
	        results.push_back(word.substr(0,i) + word.substr(i + 1));
	        }
	    //Transposes
	    for (int i = 0; i < word.size() - 1; i++){
	        results.push_back(word.substr(0, i) + word[i + 1] + word[i] + word.substr(i + 2));
	    }
	    for (char j = 'a'; j <= 'z'; ++ j){
	    //Replaces
	        for(int i = 0; i < word.size(); i++){
	            results.push_back(word.substr(0, i) + j + word.substr(i + 1));
	        }
	    //Inserts
	        for(int i = 0; i < word.size() + 1; i++){
	            results.push_back(word.substr(0, i) + j + word.substr(i));
	        }
	    }
	}

	void edits2(string word, vector<string> &results2){
	    vector<string> results = {};
	    edits1(word, results);
	    results2.insert(results2.end(), results.begin(), results.end());
	    for(int i = 0; i < results.size(); i++){
	        vector<string> results1 = {};
	        edits1(results[i], results1);
	        results2.insert(results2.end(), results1.begin(), results1.end());
	    }
	}

	void suggestion(string word, set<string> &sugges, int numSuge){
	    vector<string> results;
	    edits2(word, results);
	    for(int i =0; i < results.size(); i++){
	        if(!search(results[i]).empty()){
	            sugges.emplace(results[i]);
	        }
	        if (sugges.size() == numSuge){break;}
	    }
	}

	bool isdigit (char c){
	    return('0' <= c && c <= '9');
	}
	//Return texts

};

int main() {

Trie Trie;


//    DIR* dir;
//    struct dirent* entry;
//    dir  = opendir("out_rept");
//    while((entry = readdir(dir))){
//            string s = entry->d_name;
//            if( s!= "." && s != "..") {
//                Trie.leitura("out_rept/"+s);
//            }
//    }
//	Trie.serializa("Trie_carrega_tree");

    Trie.diserializa("Trie_carrega_tree");
    
    
    //Trie.executeSearch();
    return 0;
}
