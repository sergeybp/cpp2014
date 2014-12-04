#include <iostream>
#include <string>
#include <sstream>
#include "player/playerH.h"

using namespace std;

uint32_t playerH::bet(uint32_t sum, Table state) {
    std::cout << "[" << this->getName() << "] Your sum to bet \n min-> " << sum << "\n 0 for check/fold: ";
    std::string s;
    std::getline(std::cin, s);
    std::stringstream ss;
        ss << s;
        unsigned long as;
        ss >> as;
    return as;
}
