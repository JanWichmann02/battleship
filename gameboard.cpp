#include "battleship.h"
#include "ship.h"
#include "player.h"
#include "battleship.cpp"
#include "part.cpp"
#include "ship.cpp"
#include "player.cpp"
#include "gameboard.h"


#include <iostream>
#include <ctime>
using namespace std;

GameBoard::GameBoard()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            m_enemyBoard[i][j] = '.';
        }
    }
}

void GameBoard::printBoard()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            // Prüfe, ob die Position ein Schiffsteil enthält
            bool found = false; // Flag, um zu überprüfen, ob ein Schiffsteil gefunden wurde
            // Prüfe, ob die Position ein Schiffsteil enthält
            for (size_t k = 0; k < m_ships.size(); ++k)
            {
                if (m_ships[k].hasPartIn(i, j)) //Überprüft für jedes Schiff ob ein Teil an (i,j) existiert
                {
                    if (!m_ships[k].getPartIn(i, j).isDamaged())
                    {
                        cout << static_cast<char>(k+48);
                    }
                    else if (m_ships[k].isSunk())
                    {
                        cout << 'S';
                    }
                    else
                    {
                        cout << 'X';
                    }
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << '.';
            }
        }
        std::cout << std::endl;
    }
}
void GameBoard::printEnemyBoard()
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            switch (m_enemyBoard[i][j]) {
            case '.':
                cout << ". ";
                break;
            case 'X':
                cout << "X ";
                break;
            case 'O':
                cout << "O ";
                break;
            default:
                break;
            }
        }
        std::cout << std::endl;
    }
}

bool GameBoard::hit(int row, int col)
{
    for (size_t i = 0; i < m_ships.size(); ++i) {
        if (m_ships[i].hasPartIn(row, col)) {
            m_ships[i].getPartIn(row, col).setDamaged();
            return true;
        }
    }
    return false;
}

void GameBoard::mark(int row, int col, bool wasHit) {
    if (wasHit) {
        m_enemyBoard[row][col] = 'X';
    } else {
        m_enemyBoard[row][col] = 'O';
    }
}

void GameBoard::randomPlaceShips(){
    srand(time(nullptr)); // Initialisiere den Zufallszahlengenerator mit der aktuellen Zeit

    //Ein Dreadnought mit 5 Teilen
    //Ship dreadnought(rand() % 10, rand() % 10, 5, static_cast<Direction>(rand() % 4));
    //m_ships[0] = dreadnought;

    // Zwei Kreuzer mit je 4 Teilen
    //Ship cruiser1(rand() % 10, rand() % 10, 4, static_cast<Direction>(rand() % 4));
    //Ship cruiser2(rand() % 10, rand() % 10, 4, static_cast<Direction>(rand() % 4));
    //m_ships[1] = cruiser1;
    //m_ships[2] = cruiser2;

    // Drei Zerstörer mit je 3 Teilen
    //Ship destroyer1(rand() % 10, rand() % 10, 3, static_cast<Direction>(rand() % 4));
    //Ship destroyer2(rand() % 10, rand() % 10, 3, static_cast<Direction>(rand() % 4));
    //Ship destroyer3(rand() % 10, rand() % 10, 3, static_cast<Direction>(rand() % 4));
    //m_ships[3] = destroyer1;
    //m_ships[4] = destroyer2;
    //m_ships[5] = destroyer3;

    // Vier U-Boote mit je 2 Teilen
    Ship submarine1(rand() % 10, rand() % 10, 2, static_cast<Direction>(rand() % 4));
    //Ship submarine2(rand() % 10, rand() % 10, 2, static_cast<Direction>(rand() % 4));
    //Ship submarine3(rand() % 10, rand() % 10, 2, static_cast<Direction>(rand() % 4));
    //Ship submarine4(rand() % 10, rand() % 10, 2, static_cast<Direction>(rand() % 4));
    m_ships[6] = submarine1;
    //m_ships[7] = submarine2;
    //m_ships[8] = submarine3;
    //m_ships[9] = submarine4;
    //for (int i = 0; i < 10; ++i) {
    //m_ships[i] = Ship(i, i, 1, Direction::north);
    //}
}

bool GameBoard::allShipsSunk(){
    for (size_t i = 0; i < m_ships.size(); ++i) {
        if (!m_ships[i].isSunk()) {
            return false; // Es gibt mindestens ein nicht versenktes Schiff
        }
    }
    return true; // Alle Schiffe sind versenkt
}
