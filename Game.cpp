#include <cstdlib>

#include "Game.hpp"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::to_string;
using std::unique_ptr;


/***********************************************************************************************
** Description: Default constructor that initalizes data members for team scores and the number of
** rounds played, allocates memory for unique pointers to the game and loser menus, and
** allocates memory for shared pointers to the team queues and the loser stack.
***********************************************************************************************/
Game::Game() {
  gameMenu = unique_ptr<Menu>(new Menu);
  loserMenu = unique_ptr<Menu>(new Menu("Would you like to view fighters who lost their fights?"));
  populateMenus();
  team1Queue = make_shared<Container>();
  team2Queue = make_shared<Container>();
  loserStack = make_shared<Container>();
  team1Score = team2Score = 0;
  round = 1;
}


/***********************************************************************************************
** Description: Method that prompts the user to fighters to each team's lineup using the
** promptForFighters method, then uses a while loop to make the first fighter in each team's
** lineup fight until one team no longer has any fighters. The final score is then displayed
** to the user and the user is prompted to display the list of losers in the tournament, or
** continue to the main menu. The team queues and loser stack are cleared, and the scores and
** number of rounds completed in the tournament are reset after the tournament is complete so
** a new tournament can begin if the user selects to play again from the main menu.
***********************************************************************************************/
void Game::play() {

  cout << "\nFighter Tournament" << endl;
  int team1Size = gameMenu->getIntFromPrompt("\nHow many fighters should Team 1 have?", 1, 10, false);
  promptForFighters(team1Queue, team1Size);
  int team2Size = gameMenu->getIntFromPrompt("\nHow many fighters should Team 2 have?", 1, 10, false);
  promptForFighters(team2Queue, team2Size);

  while( !team1Queue->isEmpty() && !team2Queue->isEmpty() ) {
    fight();
  }

  cout << endl << "Game Over" << endl << endl;

  if ( getTeam1Score() > getTeam2Score() ) {
    cout << "Team 1 wins with " << getTeam1Score() << " points!" << endl << endl;
  } else if ( getTeam1Score() < getTeam2Score() ) {
    cout << "Team 2 wins with " << getTeam2Score() << " points!" << endl << endl;
  } else {
    cout << "It's a draw! Team 1 and Team 2 tie with " << getTeam1Score() << " points!" << endl << endl;
  }

  if (loserMenu->getIntFromPrompt(1, loserMenu->getMenuChoices(), true) == 1) {
    cout << endl << "Losers:" << endl;
    loserStack->printContainer();
    cout << endl;
  }

  team1Queue->clear();
  team2Queue->clear();
  loserStack->clear();
  setRound(1);
  setTeam1Score(0);
  setTeam2Score(0);

}

/***********************************************************************************************
** Description: Method that adds relevant options for Characters to the game's menu object and
** the losers menu object using the addMenuItem method in the Menu class.
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
** Description: This method initializes integers for indicating the most recent attacker (Team 1
** or Team 2) and the strength of each character in temporary variables, then either the fighter
** at the top of Team 1 or Team 2's queue attacks first, depending on the return value of the
** firstStrike method. The most recent attacker is updated in the lastAttacker variable,
** with a while loop that alternates the attackers until one Character's strength is depleted.
** The endFight method is called when one fighter's strength is at or below 0 to output results,
** update the score and handle the contents of the team queues and loser stack according to the
** results of the fight.
***********************************************************************************************/
void Game::fight() {

  int lastAttacker = 0;

  int origStrength1 = team1Queue->getFront()->getStrengthPts();
  int origStrength2 = team2Queue->getFront()->getStrengthPts();

  cout << endl << "Round " << round << ":" << endl;
  cout << "Team 1 - " << team1Queue->getFront()->getName()
       << " vs. Team 2 - " << team2Queue->getFront()->getName() << endl;

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
** Description: After a fight is completed, this method takes constant references to two
** integers for each team's fighter's strength prior to a fight. It then outputs the results
** of the fight based on the strength of each fighter, then restores the strength points of the
** winning fighter by passing the corresponding parameter to the Character's restoreHealth
** member function. That fighter is then placed at the back of the team's queue, and the team's
** score is incremented by one. The pointer to the losing fighter is added to the top of the
** loser stack and removed from the front of the team's queue. The round number is then
** incremented by one.
***********************************************************************************************/
void Game::endFight(const int &origStrength1, const int &origStrength2) {

  if (team1Queue->getFront()->getStrengthPts() <= 0) {

    cout << team1Queue->getFront()->getName() << " was defeated by "
         << team2Queue->getFront()->getName() << "." << endl;

    team2Queue->getFront()->restoreHealth(origStrength2);
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

 setRound( getRound() + 1 );

}


/***********************************************************************************************
** Description: Method that takes a shared pointer to a Container for a team's lineup, a
** constant reference to an integer that corresponds to a menu selection for a fighter, and a
** constant reference to a string for the fighter's name. a switch statement creates a shared
** pointer to the correct inherited Character class based on the menu choice passed to the
** method, then adds that Character to the back of the team's queue using the Container's
** addBack member function.
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
** Description: Method that takes a shared pointer to a Container representing a team's queue of
** fighters and a constant reference to an integer that represents the requested number of
** fighters, then uses a loop to prompt the user to add that requested number of fighters to the
** queue using the addFighter method.
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


int Game::getRound() {
  return round;
}


int Game::getTeam1Score() {
  return team1Score;
}


int Game::getTeam2Score() {
  return team2Score;
}


void Game::setRound(const int &roundNumber) {
  round = roundNumber;
}


void Game::setTeam1Score(const int &score) {
  team1Score = score;
}


void Game::setTeam2Score(const int &score) {
  team2Score = score;
}
