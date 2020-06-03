#include "lib/server_http.hpp"
#include <sstream>
#include <fstream>

using namespace std;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main(){
    HttpServer server;
    server.config.port = 8080; //Porta do servidor local

    thread server_thread([&server](){
        server.start();
    });

    this_thread::sleep_for(chrono::seconds(1));
    server_thread.join();
}