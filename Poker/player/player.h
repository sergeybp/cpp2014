#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "pokerController/pokerOn.h"
#include "table/table.h"

class Table;

class Player {
private:
    std::string name;
public:
    Player() {}
    Player(std::string n) { name = n; }
    // Get Player's name
    std::string getName() const { return name; }
    virtual ~Player() {}
    // Get player's bet or zero
    virtual uint32_t bet(uint32_t minBet, Table state) = 0;
};

#endif
