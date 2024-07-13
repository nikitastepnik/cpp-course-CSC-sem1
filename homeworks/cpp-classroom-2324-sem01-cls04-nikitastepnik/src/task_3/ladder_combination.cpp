#include "ladder_combination.hpp"

uint64_t ladderCombinations(uint8_t steps) {
    static uint8_t stepsCombinationCount[21] = {0};

    if (steps <= 1) {
        return stepsCombinationCount[0];
    }


}
