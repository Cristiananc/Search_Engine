Trie trie;

    DIR* dir;
    struct dirent* entry;
    dir  = opendir("out_rept");
    while((entry = readdir(dir))){
            string s = entry->d_name;
            if( s!= "." && s != "..") {
                trie.leitura("out_rept/"+s);
            }
    }
    trie.serializa("serializada");

    trie.executeSearch();
