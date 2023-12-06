#include "gameboard.h"
#include <iostream>
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
                if (m_ships[k].hasPartIn(i, j))
                {
                    if (!m_ships[k].getPartIn(i, j).isDamaged())
                    {
                        cout << k + '0';
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
                    break; // Stoppe die Suche, wenn ein Schiffsteil gefunden wurde
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
    for (size_t k = 0; k < m_ships.size(); ++k) {
        if (m_ships[k].hasPartIn(row, col)) {
            m_ships[k].getPartIn(row, col).setDamaged();
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
    // Ein Dreadnought mit 5 Teilen
    Ship dreadnought(0, 0, 5, Direction::east);
    m_ships[0] = dreadnought;

    // Zwei Kreuzer mit je 4 Teilen
    Ship cruiser1(1, 1, 4, Direction::north);
    Ship cruiser2(2, 2, 4, Direction::west);
    m_ships[1] = cruiser1;
    m_ships[2] = cruiser2;

    // Drei Zerstörer mit je 3 Teilen
    Ship destroyer1(3, 3, 3, Direction::south);
    Ship destroyer2(4, 4, 3, Direction::east);
    Ship destroyer3(5, 5, 3, Direction::north);
    m_ships[3] = destroyer1;
    m_ships[4] = destroyer2;
    m_ships[5] = destroyer3;

    // Vier U-Boote mit je 2 Teilen
    Ship submarine1(6, 6, 2, Direction::west);
    Ship submarine2(7, 7, 2, Direction::south);
    Ship submarine3(8, 8, 2, Direction::east);
    Ship submarine4(9, 9, 2, Direction::north);
    m_ships[6] = submarine1;
    m_ships[7] = submarine2;
    m_ships[8] = submarine3;
    m_ships[9] = submarine4;

    //nur Idee
}