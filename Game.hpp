/*********************************************************************
** Description: Specification file for the Game class.
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>

#include "Character.hpp"
#include "Container.hpp"
#include "Menu.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "HarryPotter.hpp"
#include "Medusa.hpp"
#include "Vampire.hpp"

class Game {

  public:
    Game();
    ~Game();
    void play();

  private:
    void fight(Container *team1Queue, Container *team2Queue);
    Container *loserStack, *team1Queue, *team2Queue;
    Menu *gameMenu = nullptr;
    void populateMenu(Menu* menu);
    int firstStrike();
    void displayRoll(Character *character, const bool &isAttacker);
    void displayType(Character *character, const bool &isAttacker);
    void displayDamage(Character *character, const int &originalStrength);
    void addFighter(Container *teamQueue, int choice, std::string fighterName);
    void promptForFighters(Container *teamQueue, int teamSize);

};

#endif
