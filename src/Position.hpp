#pragma once

// Includes

class Position {
public:

    // Position
    unsigned long int x;
    unsigned long int y;
    
    // Constructor and Destructor
    Position(unsigned long int x, unsigned long int y) {

        this->x = x;
        this->y = y; 
    }
    ~Position() {

    }

    // Operator
    bool operator==(const Position& pos_check) {

        return (this->x == pos_check.x && this->y == pos_check.y);
    }
};