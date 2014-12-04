#ifndef PLAYERH_H
#define PLAYERH_H

#include "player/player.h"
#include "cards/cards.h"

class playerH: public Player {
private:
public:
    playerH() {}
    playerH(std::string name): Player(name) { }
    ~playerH() {}
    // Player make's bet
    uint32_t bet(uint32_t sum, Table state);
};


#endif
