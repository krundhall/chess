#pragma once

struct Position
{
    int row;
    int col;

    bool operator==(const Position &other) const
    {
        return this->row == other.row && this->col == other.col;
    }
};
