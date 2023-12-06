#include "ship.h"
#include <stdexcept>
#include <vector>
#include <iostream>

Ship::Ship()
{
}

Ship::Ship(int row, int col, int lengthOfShip, Direction direction)
{

    if (static_cast<int>(direction) < 0 || static_cast<int>(direction) > 3)
    {
        throw std::invalid_argument("Ungültige Richtung");
    }
    bool outsideGrid = false;
    if (direction == Direction::north && row - lengthOfShip + 1 < 0)
    {
        outsideGrid = true;
    }
    else if (direction == Direction::south && row + lengthOfShip - 1 > 9)
    {
        outsideGrid = true;
    }
    else if (direction == Direction::west && col - lengthOfShip + 1 < 0)
    {
        outsideGrid = true;
    }
    else if (direction == Direction::east && col + lengthOfShip - 1 > 9)
    {
        outsideGrid = true;
    }

    if (outsideGrid)
    {
        throw std::invalid_argument("Schiff liegt außerhalb des Rasters");
    }

    for (size_t i = 0; i < lengthOfShip; ++i)
    {
        int partRow = row;
        int partCol = col;
        if (direction == Direction::north)
        {
            partRow -= i;
        }
        else if (direction == Direction::south)
        {
            partRow += i;
        }
        else if (direction == Direction::west)
        {
            partCol -= i;
        }
        else if (direction == Direction::east)
        {
            partCol += i;
        }

        m_parts.push_back(Part(partRow, partCol)); //Überprüfen
    }
}

bool Ship::hasPartIn(int row, int col) {
    for (size_t i = 0; i < m_parts.size(); ++i) {
        if (m_parts[i].getRow() == row && m_parts[i].getCol() == col) {
            return true;
    }
    return false;
}
}
