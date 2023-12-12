#include "gameboard.h"
#include "player.h"
#include "battleship.h"
#include <iostream>
#include <cstdlib> // Für srand() und rand()
#include <ctime>

Battleship::Battleship(const string& player1Name, const string& player2Name)
    : m_players{ Player(player1Name), Player(player2Name) } {}

void Battleship::play() {
    // Initialisiere die Spielbretter für beide Spieler
    for (auto& board : m_boards) {
        board.randomPlaceShips(); // Zufällige Platzierung der Schiffe
    }

    int activePlayerIndex = 0; // Index des aktiven Spielers (Player 1)
    int inactivePlayerIndex = 1; // Index des inaktiven Spielers (Player 2)

    bool gameOn = true;
    while (gameOn) {
        // 1. Aktiven Spieler bestimmen (Hier zufällig für den Start)
        std::srand(std::time(nullptr)); // Seed für Zufallszahlengenerator
        activePlayerIndex = std::rand() % 2; // Zufällig wählen zwischen Spieler 1 und Spieler 2
        inactivePlayerIndex = (activePlayerIndex + 1) % 2; // Der andere Spieler ist inaktiv

        // 2. Spielbrett und "Cheatsheet" für aktiven Spieler anzeigen
        std::cout << "Game Board for Player " << m_players[activePlayerIndex].getName() << ":\n";
        m_boards[activePlayerIndex].printBoard(); // Zeige das Spielbrett
        std::cout << "Cheat Sheet for Player " << m_players[activePlayerIndex].getName() << ":\n";
        m_boards[activePlayerIndex].printEnemyBoard(); // Zeige das "Cheatsheet"

        // 3. Aktiven Spieler nach einem Schussort fragen
        int row, col;
        std::cout << m_players[activePlayerIndex].getName() << ", enter row (0-9): ";
        std::cin >> row;
        std::cout << m_players[activePlayerIndex].getName() << ", enter column (0-9): ";
        std::cin >> col;

        // 4. Schieße auf das Spielbrett des inaktiven Spielers
        bool wasHit = m_boards[inactivePlayerIndex].hit(row, col);

        // 5. Aktiven Spieler informieren und das "Cheatsheet" aktualisieren
        if (wasHit) {
            std::cout << "Hit!\n";
            m_boards[activePlayerIndex].mark(row, col, true); // Markiere als getroffen
        } else {
            std::cout << "Miss!\n";
            m_boards[activePlayerIndex].mark(row, col, false); // Markiere als verfehlt
        }

        // 6. Spieler wechseln
        std::swap(activePlayerIndex, inactivePlayerIndex);

        // 7. Überprüfen, ob ein Spieler verloren hat
        if (m_boards[activePlayerIndex].allShipsSunk()) {
            gameOn = false; // Wenn alle Schiffe des aktiven Spielers versenkt sind, ist das Spiel vorbei
            std::cout << m_players[activePlayerIndex].getName() << " has lost!\n";
        }
    }
}

