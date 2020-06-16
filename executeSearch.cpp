#include "Search.cpp"
using namespace std;

int main(){
Trie trie;

    clock_t t0 = clock();
    int c = 0;
    DIR* dir;
    struct dirent* entry;
    dir  = opendir("out_rept");
    while((entry = readdir(dir))){
            string s = entry->d_name;
            if( s!= "." && s != "..") {
                c = c+1;
                trie.leitura("out_rept/"+s,c,t0);
            }
    }
    //trie.serializa("serializada");

    trie.executeSearch();
}

