#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>


using namespace std;

void insert(int x, string word) {

}

int main() {
    clock_t t0;
    int x;
    bool f;
    string ids; // lista de ids
    string word ; // a palavra de cada itera��o
    char c ;
    char c2; // a letra em cada itera��o
    ifstream arquivo; // arquivo a ser lido

    arquivo.open("texto_10000.txt");
    if(arquivo.is_open()){

        while(arquivo.get(c)) {

            if (c == ' ' or c == '\n'){ // reconhecendo t�rmino de uma palavra
                if(c == ' ' && c2 == '\n') { f = true;}
                if (f && word[0] == 'i' && word[1] == 'd' && word[2] == '=' && isdigit(word[3]) ){
                    char aux[word.size()-3];
                    memcpy(aux, &word[3], word.size());
                    ids = aux; // registrando IDs momentaneamente no vetor
                    x = stoi(ids);
                    word = "";
                    f = false;
                }
                else if(word == ""){}  // me livrando dos espa�os e endlines
                else {
                insert(x, word); // chamando a fun��o de insertar
                word = ""; // reinicio como vazia a avari�vel word
                f = false;
                }
            }
            else {
                word = word+c; // acrescento � palavra o char atual
            }
            c2 = c;
        }
    }
    arquivo.close();

    clock_t t = ((float)clock() - t0)/CLOCKS_PER_SEC; // calculando tempo em segundos
    cout << t << endl;
}


