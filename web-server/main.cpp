#include "lib/server_http.hpp" //Chamando pacotes do Simple Web Server
#include "../Search.cpp"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

//Para abrir localmente
//g++ main.cpp -I /usr/include -lboost_system -lboost_thread -lpthread

using namespace std;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

Trie trie;

string title(int id){
    ifstream titlesFile;
    string line;
    titlesFile.open("../titulos.txt");
    int countLine = 0;
    if(!titlesFile){
        cerr << "Não foi possível abrir o arquivo contendo a página de títulos";
        exit(1); //call system to stop
        }
    else{
        while(getline(titlesFile, line)){
            if(countLine == id){
                return line;
            }
            countLine ++;
        }
    }
}

string showTitles(vector<int> ids, int &count, int qntd){
	string aux;
	for(; count < qntd; count++){
		aux = aux + "<a href =javascript:query_link(\'cpp_server_open_page";
		aux = aux + to_string(count) + "\'); > " + "[" + to_string(count + 1) + "] ";
		aux = aux + title(ids[count]) + "</a></br>";

		if(count + 1 == qntd || (count > 0 && (count+ 1) % 20 == 0)){
			return aux;
		}
	}
	return aux;
}

string createPage(Trie trie, string query){
	string aux;
	string head;
	vector<string> words;
    words = trie.clean_input(query);

	if(words.size() > 0){
	    vector<int> ids;
	    clock_t t0 = clock();
	    trie.search_words(words, ids);
		double tf = ((double)(clock()-t0))/(CLOCKS_PER_SEC/1000);
		aux =  "\n (" + to_string(tf) + " seconds)" ;
		aux = aux + "\n" + to_string(ids.size()) + " results were found!";

		if (ids.size() == 0){
            	aux = aux +  "\n Sorry, we didn't find your query :(";
            	set<string> suggestions = {};
            	int nSugges = 5;
            	if(words.size() == 1){
                trie.suggestion(words[0], suggestions, nSugges);

                if(suggestions.size() > 0){
                    aux = aux + "\n Did you mean...: ";
                    int count = 1;
                    for (set<string>::iterator it = suggestions.begin(); it != suggestions.end(); ++it) {
		    		//Como clicar nas sugestões?
                    aux = aux + "\n" + *it;
                    }
				return aux;
			}
		}
	}
	else{
		int count = 0;
		return aux + '\n' + showTitles(ids, count, ids.size());
	}

}
}

int main(){
    DIR* dir;
    struct dirent* entry;
    dir  = opendir("../out_rept");
    while((entry = readdir(dir))){
            string s = entry->d_name;
            if( s!= "." && s != "..") {
                trie.leitura("../out_rept/"+s);
            }
    }
	HttpServer server;
	server.config.port = 8080; //porta do servidor será localhost/8080

	//função que recebe query do tipo localhost:8080/query?text={text}
	server.resource["^/query$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request){
		stringstream stream;
		//Trecho do código para obter a query (consulta)
		auto query_fields = request->parse_query_string(); //Recebe o conteúdo de "entrada"
		auto it = query_fields.find("text"); // Obtem o texto do conteudo
		
		string html = createPage(trie, it -> second);
		cout << html;
		//A resposta para o servidor vai ser um JSON do formato
		//{"res": "O seu projeto final vai ser incrível, [texto]!"}	
		//JSON
		// {"atributo1":"valor1",
		//	"atributo2": {"sub-atributo": "valor2"}} 
			
		stream << "{\"res\": \"";
		for(char c: html){
		if(c == "\n\t"[0]){
			stream << "</br>"; continue;
}		if(c == "\n\t"[1]){
			stream << "	";continue;
}
		stream << c;
}
		stream << "\"}";
		response->write(stream);
	};
	
	
	
	//O método default do server é abrir um arquivo na pasta web/
	//vai receber querys do tipo localhost:8080/{text}
  	server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
		auto path = "./web/"+request->path; //caminho até os arquivos do tipo HTML
		SimpleWeb::CaseInsensitiveMultimap header;
		std::ifstream ifs(path, ifstream::in | ios::binary | ios::ate); //abrindo o arquivo dentro da pasta /web
		auto length = ifs.tellg();
       	ifs.seekg(0, ios::beg);
       	stringstream stream;
       	stream << ifs.rdbuf(); //salvando o conteúdo em uma stringstream

        header.emplace("Content-Length", to_string(length));
        response->write(header);
        response->write(stream.str().c_str(), length); //e inserindo na resposta do servidor
    };

	//função para lidar com erros (não necessário)
    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
		//code
	};


    thread server_thread([&server]() {
        // Start server
        server.start();
    });

    // Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));

	server_thread.join();
}
