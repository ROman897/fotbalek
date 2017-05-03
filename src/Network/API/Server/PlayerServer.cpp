//
// Created by pnavratil on 4/5/17.
//
#include "PlayerServer.h"

void PlayerServer::startComm(UdpServer &srv) {
    srv.init();
}
/*

int main(void) { //zatial void
    PlayerServer mainSrv;

    while (1) {
        std::string ln;
        std::getline(std::cin, ln);
        if (ln == "quit") {
            break;
        }
        else
            std::cout << "nope\n";
    }
}
*/
