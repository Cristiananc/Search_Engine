#include "Search.cpp"
using namespace std;

int main(){

Trie trie;

    clock_t t0 = clock();
    int c = 0;
    DIR* dir;

    struct dirent* entry;
    dir  = opendir("for_tree");
    while((entry = readdir(dir))){
            string s = entry->d_name;
            if( s!= "." && s != "..") {
                c = c+1;
                trie.leitura("for_tree/"+s,c,t0);
            }
    }

    trie.executeSearch();
}

