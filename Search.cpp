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
		    int ind = c - 'a' + 10;
		}
   	    else if ('0' <= c && c <= '9'){
		    int ind = c - '0';
	    }
    }

	void insert(string word, int docId){
		Node *p = pRoot;
		Node *pChar;
		for (int i = 0; i < word.length() ; i++){
            if(i == 0){}
            else if(word[i] == ' ') {
                (p->documents).push_back(docId);
                 p = pRoot;
            }
            else if(word[i] == '\n') {(p->documents).push_back(docId); p = pRoot;}
            else {
                int ind = index(word[i]);
                if(p -> children[ind] == nullptr){
                    pChar = new Node();
                    p -> children[ind] = pChar;
                }
                p = p -> children[ind];
            }
		}
	}

	string printa(int id) {
        ifstream arquivo;               // arquivo a ser lido
        string line = "";               // a linha em cada iteração
        string texto;                   // armazena o texto numa string
        int ID = id/10000;              // o módulo id por 10000
        bool b = false;                 // para saber se já iniciamos a leitura do texto em questão
        int t = to_string(id).size();
        arquivo.open("originais_ordenados/orig_docc_"+to_string(ID)+".txt");   // abrindo arquivo
        if(arquivo.is_open()) {
            while(getline(arquivo, line)) {
                    line = line+'\n';
                    if (b) {texto = texto + line;}
                    if(line.size() >= 8+t) {
                        if (line.substr(0,8+t) == "<doc id="+to_string(id)) {   //verifica se o id corresponde
                            b = true;
                            size_t pos = line.find("nonfiltered");      // position of "nonfilteres" in string line
                            texto = texto + line.substr(15 + t, pos - 22);
                            line = "";
                        }
                        else if(line.size() >= 12) {
                            if(line.substr(0,12) == "ENDOFARTICLE" && b) { break;}  //verifica se é o final de um texto
                        }
                    }
            }
        }
        arquivo.close();
        return texto;
    }

	void leitura(string texto,int tf, int t) {

        int id;
        ifstream arquivo;   // arquivo a ser lido
        string line;
        int loc;

        arquivo.open(texto);
        if(arquivo.is_open()){

            while(getline(arquivo, line)) {
                    if(line.size() >= 5){
                            if(line.substr(0,4) == " id=") {
                                    line = line.substr(1,line.size()-1);
                                    loc = line.find(" ");
                                    id = stoi(line.substr(3,loc-3));
                                    line = line.substr(loc,line.size()-loc);}
                    }
                    insert(line,id);
            }
        }
        arquivo.close();
        cout << "texto "  << tf << "  " << endl;
        if (tf % 10 == 0 || tf == 135){ cout <<((float)clock() - (float)t)/CLOCKS_PER_SEC << endl;}
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
    return (pCurr -> documents);}

	/*void serializa(string name){
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
    }*/


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
            cerr << "It was not possible to open the file containing the title page";
            exit(1); //call system to stop
        }
        else{
            while(getline(titlesFile, line) && indexVec < ids.size()){
                int a = ids[indexVec];
                if(countLine == a){
                    cout << "[" << indexVec + 1 << "] " << line << endl;
                    ++ indexVec;

                    if(indexVec == ids.size()) {cout << endl;
                    cout << "type 'r'  to end, another key to search again or the number of the chosen text: "; cin >> aux;
                    bool b2 = true;
                    for(int i = 0; i < aux.size(); i++) {
                        if (!isdigit(aux[i])) {b2 = false;}
                    }
                    if(aux != "" && b2) {cout << printa(ids[stoi(aux)-1]) << endl; cout << endl << ids[stoi(aux)-1] << endl; break;}
                    else if(aux == "r") {continu_searc = false; break;}
                     cout <<  "ending search :)" << endl << endl;}

                    if(indexVec == numberOfTitles*20){
                    cout << "type 's' for the next page, 'r' to end, another key to search again or the number of the chosen text: "; cin >> aux;
                    bool b2 = true;
                    for(int i = 0; i < aux.size(); i++) {
                        if (!isdigit(aux[i])) {b2 = false;}
                    }
                    if(aux != "" && b2) {cout << printa(ids[stoi(aux)-1]) << endl; cout << endl << ids[stoi(aux)-1] << endl; break;}
                    else if(aux == "r") {continu_searc = false; break;}
                    else if(aux != "s")
                        {cout << endl << endl << "ending search :)" << endl; break;}
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
        string word;
        vector<string> words;
        int auxx = 1;

        while(continu_searc){
        cout << "Enter your query: " << endl;
        getline(cin, word);
        words = clean_input(word);

        if(words.size() > 0){
        vector<int> ids;
        clock_t t0 = clock();
        search_words(words, ids);

        double tf = ((double)(clock()-t0))/(CLOCKS_PER_SEC); // calculando tempo em segundos
        cout << "(" << tf << " seconds)" << endl;
        cout << "About " << ids.size() << " results (" << tf << " seconds) \n \n";

        if (ids.size() == 0){
            cout << "Sorry, we could not find your search for " << word << " :(" << endl;;
            set<string> suggestions = {};
            int nSugges = 5;
            if(words.size() == 1){
                suggestion(words[0], suggestions, nSugges);
                if(suggestions.size() > 0){
                    cout << "did you mean: " << endl;
                    int count = 1;
                    for (set<string>::iterator it = suggestions.begin(); it != suggestions.end(); ++it) {
                    cout << "[" << count << "]" << *it << endl;
                    count++;
                    }
                    char aux;
                    cout << "type the suggestion number + enter to search: "; cin >> aux;
                    int ia = aux - '0' - 1;
                    if(0 <= ia < suggestions.size()){
                    string x = *next(suggestions.begin(), ia);
                    vector<string> wordSug = {x};

                    clock_t t0 = clock();
                    search_words(wordSug, ids);
                    double tf = ((double)(clock()-t0))/(CLOCKS_PER_SEC); // calculando tempo em segundos
                    cout << "(" << tf << " seconds)" << endl;

                    cout << "About " << ids.size() << " results (" << tf << " seconds) "<< endl;
                    cout << "Pages found for: " << x << endl;
                    getTitle(ids);
                    }
                }
            }
            else{
                vector<string> suges1 = {};
                int n = 1;
                bool auxI = false;
                for(int i = 0; i < words.size(); ++i){
                    if(search(words[i]).empty()){
                        suggestion(words[i], suggestions, n);
                        for (set<string>::iterator it = suggestions.begin(); it != suggestions.end(); ++it) {
                            suges1.push_back(*it);
                            auxI = true;
                            }
                        }
                    else{
                        suges1.push_back(words[i]);
                    }
                }
                if(auxI){
                    cout << "did you mean: " << endl;
                    for (vector<string>::iterator it = suges1.begin(); it != suges1.end(); ++it) {
                        cout << *it << ' ';
                    }
                    cout << endl;
                    char aux;
                    cout << "type 's' + enter to search: "; cin >> aux;
                    if(aux == 's'){
                        clock_t t0 = clock();
                        search_words(suges1, ids);
                        double tf = ((double)(clock()-t0))/(CLOCKS_PER_SEC); // calculando tempo em segundos
                        cout << "(" << tf << " seconds)" << endl;
                        cout << "About " << ids.size() << " results (" << tf << " seconds) " << endl;
                        cout << "Pages found: " << endl;
                        getTitle(ids);
                    }
                }
            }
        }
        else{
            cout << "Pages found for: " << word << endl;
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
    return('0' <= c && c <= '9');}

};

