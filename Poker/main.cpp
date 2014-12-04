#include <iostream>
#include "table/table.h"
#include "pokerController/pokerOn.h"
#include "player/player.h"
#include "cards/cards.h"
#include "player/playerH.h"

template <typename... Players>
pokerOn* newGame(uint32_t n, uint32_t startCash, uint32_t littleBlind, Players *... p) {
    pokerOn* res = new pokerOn();
    res->playersCount = n;
    res->littleBlind = littleBlind;
    res->deck = std::vector <CloseCard>();
    res->table = std::vector <OpenCard>();

    res->players = new pokerOn::PlayerData[res->playersCount];
    res->addPlayers(0, p...);

    for (uint32_t i = 0; i < res->playersCount; i++) {
        res->players[i].cash = startCash;
        res->players[i].hand = new OpenCard[2];
    }
    res->shuffle();

    return res;
}

template <typename Player>
void pokerOn::addPlayers(unsigned cnt, Player* p) {
    if (cnt < playersCount) {
        players[cnt].p = p;
    }
}

template <typename Player, typename... Team>
void pokerOn::addPlayers(unsigned cnt, Player* p, Team* ... t) {
    if (cnt < playersCount) {
        players[cnt].p = p;
        addPlayers(++cnt, t...);
    }
}

using namespace std;

int main() {

    //testing game
    pokerOn* game = newGame((uint32_t) 2,
                             (uint32_t) 100,
                             (uint32_t) 10,
                             new playerH("LOL1"),
                             new playerH("LOL2"));
    game->run();
    delete game;
    return 0;
}
