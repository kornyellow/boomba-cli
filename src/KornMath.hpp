#pragma once

// Includes

class KornMath {
public :

    static int sign(int number) {

        if(number > 0) return 1;
        if(number < 0) return -1;
        return 0;
    }
};