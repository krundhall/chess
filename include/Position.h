#pragma once

using namespace std;

struct Position
{
    int row;
    int col;
    
    Position(int row, int col);
    
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

};