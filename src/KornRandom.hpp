#pragma once

// Includes

class KornRandom {
public :

    static int randomInt(int a) {

        return rand() % a + 1;
    }

    static int randomIntRange(int a, int b) {
        
        return rand() % (b + 1 - a) + a;
    }
};