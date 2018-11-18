/*********************************************************************
** Description: Specification file for the Game class.
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "Character.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "HarryPotter.hpp"
#include "Medusa.hpp"
#include "Vampire.hpp"

class Game {

  public:
    Game();
    Game(int character1, int character2);
    ~Game();

  private:
    void fight(Character* character1, Character* character2);
    Character* fighter1 = nullptr;
    Character* fighter2 = nullptr;
    int firstStrike();
    void displayRoll(Character* character, const bool &isAttacker);
    void displayType(Character* character, const int &characterNumber, const bool &isAttacker);
    void displayDamage(Character* character, const int &characterNumber, const int &originalStrength);
    Character* getFighter1();
    Character* getFighter2();
    void setFighter(int fighter, int choice);

};

#endif
