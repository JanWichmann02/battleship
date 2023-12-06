#include "player.h"
#include <iostream>

Player::Player(const string& playerName)
    : m_playerName(playerName), m_gamesWon(0), m_gamesLost(0) {}

int Player::getGamesLost() const {
    return m_gamesLost;
}

int Player::getGamesWon() const {
    return m_gamesWon;
}

int Player::getGamesPlayed() const {
    return m_gamesWon + m_gamesLost;
}

void Player::addGameWon(){
    m_gamesWon++;
}

void Player::addGameLost(){
    m_gamesLost++;
}


string Player::getName() {
    return m_playerName;
}

