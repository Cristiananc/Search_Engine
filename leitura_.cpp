#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>


using namespace std;

void insert(vector<char> x, string word) {

    //cout << id << endl;
    //for(int i = 0; i<word.size();i++){ s2 = s2+word[i];}
    //for(int i = 0; i<x.size();i++){ s = s+x[i];}
    //cout << s << "  " << s2 << endl;

}

int main() {

    clock_t t0;
    bool f;
    int i = 0;
    vector <char> ids; // lista de ids
    string word ;
    string DocId;
    char c ;// a letra em cada iteração
    char c2;// a letra da iteração anterior
    ifstream arquivo; // arquivo a ser lido

    arquivo.open("new_2.txt");
    if(arquivo.is_open()){

        while(arquivo.get(c)) {

            if (c == ' ' or c == '\n'){ // reconhecendo término de uma palavra
                if(c == ' ' && c2 == '\n') { f = true;
                }
                if (f && word[0] == 'i' && word[1] == 'd' && word[2] == '=' && isdigit(word[3]) ){
                    ids = {};
                    for(int i = 0; i< word.size();i++) {
                    ids.push_back(word[i]); // registrando IDs momentaneamente
                    }
                    word = "";
                    f = false;
                    i ++;
                }
                else if(word == ""){ // me livrando dos espaços e endlines
                }
                else {
                    insert(ids, word); // chamando a função de insertar
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

    clock_t t = ((float)clock() - t0)/CLOCKS_PER_SEC; // calculando tempo em segundos
    cout << t << endl << i;
}
