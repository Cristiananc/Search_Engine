#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>


using namespace std;

int main() {
    clock_t t0;
    int i = 0;
    string ids[10000]; // lista das palavras do texto. Depois será necessário fazer sem indicar tamanho
    string word ; // a palavra de cada iteraação
    char c ; // a letra eem cada ietração
    ifstream arquivo; // arquivo a ser lido

    arquivo.open("texto_20000.txt");
    if(arquivo.is_open()){

        while(arquivo.get(c)) {

            if (c == ' ' or c == '\n') // reconhecendo término de uma palavra
            {
                if ( word[0] == 'i' && word[1] == 'd' && word[2] == '=')
                    { ids[i] = word; i++ ; word = "";} // registrando IDs
                else if(word == ""){}  // me livrando dos espaços e endlines
                else {
                //palavras[i] = word;

                //cout << word << "  ";
                word = ""; // reinicio como vazia a avariável word
                }
            }

            else {
                word = word+c; // acrescento à palavra o char atual
            }
        }
    }
    arquivo.close();


   /* for(int j = 0; j<=i; j++) // para visualizar podemos printar
    {cout << ids[j] << endl;}*/

    clock_t t = ((float)clock() - t0)/CLOCKS_PER_SEC; // calculando tempo em segundos
    cout << t << endl << i;
}
