/*********************************************************************
** Description: Specification file for the Game class.
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>
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
    int round, team1Score, team2Score;
    std::shared_ptr<Container> loserStack, team1Queue, team2Queue;
    std::shared_ptr<Menu> gameMenu, loserMenu;
    void populateMenus();
    void fight();
    int firstStrike();
    void endFight(const int &origStrength1, const int &origStrength2);
    void addFighter(std::shared_ptr<Container> teamQueue, const int &choice, const std::string &fighterName);
    void promptForFighters(std::shared_ptr<Container> teamQueue, const int &teamSize);
    int getRound();
    int getTeam1Score();
    int getTeam2Score();
    void setRound(const int &roundNumber);
    void setTeam1Score(const int &score);
    void setTeam2Score(const int &score);

};

#endif
