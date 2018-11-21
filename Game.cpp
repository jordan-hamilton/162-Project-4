#include <cstdlib>

#include "Game.hpp"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::to_string;
using std::unique_ptr;


Game::Game() {
  gameMenu = unique_ptr<Menu>(new Menu);
  loserMenu = unique_ptr<Menu>(new Menu("Would you like to view fighters who lost their fights?"));
  populateMenus();
  team1Queue = make_shared<Container>();
  team2Queue = make_shared<Container>();
  loserStack = make_shared<Container>();
  team1Score = team2Score = 0;
}


/***********************************************************************************************
** Description: Destructor that deletes pointers to teach team's queue and the game's menu.
***********************************************************************************************/
Game::~Game() {

}


void Game::play() {

  unsigned seed = time(0);
  srand(seed);

  cout << "Fighter Tournament" << endl;
  int team1Size = gameMenu->getIntFromPrompt("\nHow many fighters should Team 1 have?", 1, 10, false);
  promptForFighters(team1Queue, team1Size);
  int team2Size = gameMenu->getIntFromPrompt("\nHow many fighters should Team 2 have?", 1, 10, false);
  promptForFighters(team2Queue, team2Size);

  while( !team1Queue->isEmpty() && !team2Queue->isEmpty() ) {
    fight();
  }

  cout << "Game Over" << endl;

  if ( getTeam1Score() > getTeam2Score() ) {
    cout << "Team 1 wins with " << getTeam1Score() << " points!" << endl;
  } else if ( getTeam1Score() < getTeam2Score() ) {
    cout << "Team 2 wins with " << getTeam2Score() << " points!" << endl;
  } else {
    cout << "It's a draw! Team 1 and Team 2 tie with " << getTeam1Score() << " points!" << endl;
  }

  if (loserMenu->getIntFromPrompt(1, loserMenu->getMenuChoices(), true) == 1) {
    cout << "Losers:" << endl;
    loserStack->printContainer();
  }

  team1Queue->clear();
  team2Queue->clear();
  loserStack->clear();
  setTeam1Score(0);
  setTeam2Score(0);

}

/***********************************************************************************************
** Description: Take a pointer to a menu object and adds relevant options for Characters to the
** game's menu object using the addMenuItem method in the Menu class.
***********************************************************************************************/
void Game::populateMenus() {

  if (gameMenu) {
    gameMenu->addMenuItem("Barbarian");
    gameMenu->addMenuItem("Blue Men");
    gameMenu->addMenuItem("Harry Potter");
    gameMenu->addMenuItem("Medusa");
    gameMenu->addMenuItem("Vampire");
  }

  if (loserMenu) {
    loserMenu->addMenuItem("View losers");
    loserMenu->addMenuItem("Continue");
  }

}


/***********************************************************************************************
** Description: Takes two pointers to Container objects, then initializes a random generator
** seed and sets the random generator seed for any random events in the game. The strength
** of each character is stored in temporary variables, then either character1 or character2
** attacks first, depending on the return value of the firstStrike method. Fighter information
** and fight results are displayed with displayType, displayRoll and displayDamage methods.
** The most recent attacker is stored in the lastAttacker variable, then a while loop repeats,
** continues the fight, alternating attackers until one Character's strength is depleted.
***********************************************************************************************/
void Game::fight() {

  int lastAttacker = 0;

  int origStrength1 = team1Queue->getFront()->getStrengthPts();
  int origStrength2 = team2Queue->getFront()->getStrengthPts();

  cout << endl;

  if (firstStrike() == 1) {

    team2Queue->getFront()->defend( team1Queue->getFront()->attack() );
    lastAttacker = 1;

  } else {

    team1Queue->getFront()->defend( team2Queue->getFront()->attack() );
    lastAttacker = 2;

  }

  while ( team1Queue->getFront()->getStrengthPts() > 0 && team2Queue->getFront()->getStrengthPts() > 0 ) {

    if (lastAttacker == 1) {

      team1Queue->getFront()->defend( team2Queue->getFront()->attack() );
      lastAttacker = 2;

    } else {

      team2Queue->getFront()->defend( team1Queue->getFront()->attack() );
      lastAttacker = 1;

    }

  }

  endFight(origStrength1, origStrength2);

}


/***********************************************************************************************
** Description: Randomly returns an integer between 1 and 2 to indicate who should attack first
** during the fight (fighter 1 or fighter 2).
***********************************************************************************************/
int Game::firstStrike() {
  return rand() % 2 + 1;
}


/***********************************************************************************************
** Description: After an attack and defense call, this function takes a pointer to a
** Character, a constant reference to an integer for the fighter number (1 or 2), and a constant
** reference to a boolean to indicate if the character was attacking or defending during the
** encounter. It then outputs the necessary information on the character to the screen using
** public methods in the object and depending on whether the character was attacking or
** defending. If the character's strength was depleted during the encounter, a message outputs
** that the fighter died and that the other fighter won.
***********************************************************************************************/
void Game::endFight(const int &origStrength1, const int &origStrength2) {

  if (team1Queue->getFront()->getStrengthPts() <= 0) {

    cout << team1Queue->getFront()->getName() << " was defeated by "
         << team2Queue->getFront()->getName() << "." << endl;

    team2Queue->getFront()->restoreHealth(origStrength1);
    team2Queue->addBack( team2Queue->getFront() );
    team2Queue->removeFront();
    setTeam2Score( getTeam2Score() + 1 );

    loserStack->addFront( team1Queue->getFront() );
    team1Queue->removeFront();

  } else if (team2Queue->getFront()->getStrengthPts() <= 0) {

    cout << team2Queue->getFront()->getName() << " was defeated by "
         << team1Queue->getFront()->getName() << "." << endl;

    team1Queue->getFront()->restoreHealth(origStrength1);
    team1Queue->addBack( team1Queue->getFront() );
    team1Queue->removeFront();
    setTeam1Score( getTeam1Score() + 1 );

    loserStack->addFront( team2Queue->getFront() );
    team2Queue->removeFront();

 }

}


/***********************************************************************************************
** Description: Function that takes two integers representing the number of the decision order
** from the menu prompt (selecting fighter 1 or fighter 2), followed by the menu choice of
** character type. Memory is then allocated for the appropriate character and the pointer is
** assigned to the correct fighter data member.
***********************************************************************************************/
void Game::addFighter(shared_ptr<Container> teamQueue, const int &choice, const string &fighterName) {

   shared_ptr<Character> newFighter = nullptr;

    switch (choice) {

      case 1 : newFighter = make_shared<Barbarian>(fighterName);
               break;

      case 2 : newFighter = make_shared<BlueMen>(fighterName);
               break;

      case 3 : newFighter = make_shared<HarryPotter>(fighterName);
               break;

      case 4 : newFighter = make_shared<Medusa>(fighterName);
               break;

      case 5 : newFighter = make_shared<Vampire>(fighterName);
               break;

      default : {}

    }

    teamQueue->addBack(newFighter);

}


/**************************************************************************************************
** Description: Function that takes a shared pointer to a Container representing a team's list of
** fighters and an integer that represents the requested number of fighters, then
**************************************************************************************************/
void Game::promptForFighters(shared_ptr<Container> teamQueue, const int &teamSize) {

  int fightersAdded = 0;

  do {

    int fighterChosen = gameMenu->getIntFromPrompt("Who should fighter " + to_string(fightersAdded + 1) + " be?", 1, gameMenu->getMenuChoices(), true);
    string fighterName = gameMenu->getStrFromPrompt("What should this fighter's name be?", false);
    addFighter(teamQueue, fighterChosen, fighterName);
    fightersAdded++;

  } while (fightersAdded < teamSize);

}


int Game::getTeam1Score() {
  return team1Score;
}


int Game::getTeam2Score() {
  return team2Score;
}


void Game::setTeam1Score(const int &score) {
  team1Score = score;
}


void Game::setTeam2Score(const int &score) {
  team2Score = score;
}
