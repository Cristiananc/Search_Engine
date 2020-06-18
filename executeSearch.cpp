#include "Search.cpp"
using namespace std;

int main(){

Trie trie;

    clock_t t0 = clock();
    int c = 0;
    DIR *dir;
    dir = opendir("for_tree");

    if (!dir)
    {
        cout << "Directory not found" << endl;
        return 0;
    }

    for(int i = 0; i<136;i++) {
        trie.leitura("for_tree/nr_f_ordenado_"+to_string(i)+".txt",i,t0);
    }

    trie.executeSearch();
}
