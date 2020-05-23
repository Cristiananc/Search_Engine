#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//Checks if a char belongs to the alphabet being used.
bool is_alphabetchar(char c){
	    return (('a' <= c && c <= 'z') or ('0' <= c && c <= '9'));
}
bool is_uppercase(char c){
    return ('A' <= c && c <= 'Z');
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
        //I have to check if the char is in the alphabet, if so 
        if (is_alphabetchar(words[j])){
            word_clean.push_back(words[j]);
        }
        else if(is_uppercase(words[j])){
            word_clean.push_back(words[j]);
        }
        else if (find(a.begin(), a.end(),(int) words[j]) != a.end()){
            word_clean.push_back('a');}
        else if (find(e.begin(), e.end(),(int) words[j]) != e.end()){
            word_clean.push_back('e');
        }
        else if (find(i.begin(), i.end(),(int) words[j]) != i.end()){
            word_clean.push_back('i');
        }
        else if(find(o.begin(), o.end(),(int) words[j]) != o.end()){
            word_clean.push_back('o');
        }
        else if(find(u.begin(), u.end(),(int) words[j]) != u.end()){
            word_clean.push_back('u');
        }
        else if(find(c.begin(), c.end(),(int) words[j]) != c.end()){
            word_clean.push_back('c');
        }
        else if(words[j] == ' '){
            wordsToSearch.push_back(word_clean);
            word_clean.clear();
        }
    }
    return wordsToSearch;
}

//Do the search in the tree for each word returned from the clean-input function
//Return titles sorted
//Return texts


int main() {
string wordsToSearch;
cout << "What do you want to search?" << endl;
getline(cin, wordsToSearch); //Stores the whole sentence searched in a string variable
vector<string> oi;
oi = clean_input(wordsToSearch);
is_alphabetchar('a');
} 