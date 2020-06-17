#include "Search.cpp"
using namespace std;

int main(){

Trie trie;

    clock_t t0 = clock();
    int c = 0;
    for(int i = 0; i<135;i++) {
        trie.leitura("for_tree/nr_f_ordenado_"+to_string(i)+".txt",i,t0);
    }

    trie.executeSearch();
}
