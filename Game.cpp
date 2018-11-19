#include <cstdlib>

#include "Game.hpp"

using std::cout;
using std::endl;
using std::string;
using std::to_string;


Game::Game() {
  gameMenu = new Menu;
  team1Queue = new Container;
  team2Queue = new Container;
}


/***********************************************************************************************
** Description: Destructor that deletes pointers to teach team's queue and the game's menu.
***********************************************************************************************/
Game::~Game() {

  delete team1Queue;
  team1Queue = nullptr;

  delete team2Queue;
  team2Queue = nullptr;

  delete gameMenu;
  gameMenu = nullptr;

}


void Game::play() {

  populateMenu(gameMenu);

  int team1Size = gameMenu->getIntFromPrompt("\nHow many fighters should Team 1 have?", 1, 10, false);
  promptForFighters(team1Queue, team1Size);
  int team2Size = gameMenu->getIntFromPrompt("\nHow many fighters should Team 2 have?", 1, 10, false);
  promptForFighters(team2Queue, team2Size);

  while( !team1Queue->isEmpty() && !team2Queue->isEmpty() ) {
    fight(team1Queue, team2Queue);
  }
  
}

/***********************************************************************************************
** Description: Take a pointer to a menu object and adds relevant options for Characters to the
** game's menu object using the addMenuItem method in the Menu class.
***********************************************************************************************/
void Game::populateMenu(Menu* menu) {

  if (menu) {
    gameMenu->addMenuItem("Barbarian");
    gameMenu->addMenuItem("Blue Men");
    gameMenu->addMenuItem("Harry Potter");
    gameMenu->addMenuItem("Medusa");
    gameMenu->addMenuItem("Vampire");
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
void Game::fight(Container* team1Queue, Container* team2Queue) {

  unsigned seed = time(0);
  srand(seed);

  int lastAttacker = 0;

  int character1Strength = team1Queue->getFront()->getStrengthPts();
  int character2Strength = team2Queue->getFront()->getStrengthPts();

  cout << endl;

  if (firstStrike() == 1) {

    displayType(team1Queue->getFront(), true);
    displayType(team2Queue->getFront(), false);

    team2Queue->getFront()->defend( team1Queue->getFront()->attack() );

    displayRoll(team1Queue->getFront(), true);
    displayRoll(team2Queue->getFront(), false);

    displayDamage(team2Queue->getFront(), character2Strength);

    lastAttacker = 1;

  } else {

    displayType(team2Queue->getFront(), true);
    displayType(team1Queue->getFront(), false);

    team1Queue->getFront()->defend( team2Queue->getFront()->attack() );

    displayRoll(team2Queue->getFront(), true);
    displayRoll(team1Queue->getFront(), false);

    displayDamage(team1Queue->getFront(), character1Strength);

    lastAttacker = 2;

  }

  while ( team1Queue->getFront()->getStrengthPts() > 0 && team2Queue->getFront()->getStrengthPts() > 0 ) {

    character1Strength = team1Queue->getFront()->getStrengthPts();
    character2Strength = team2Queue->getFront()->getStrengthPts();

    if (lastAttacker == 1) {

      displayType(team2Queue->getFront(), true);
      displayType(team1Queue->getFront(), false);

      team1Queue->getFront()->defend( team2Queue->getFront()->attack() );

      displayRoll(team2Queue->getFront(), true);
      displayRoll(team1Queue->getFront(), false);

      displayDamage(team1Queue->getFront(), character1Strength);

      lastAttacker = 2;

    } else {

      displayType(team1Queue->getFront(), true);
      displayType(team2Queue->getFront(), false);

      team2Queue->getFront()->defend( team1Queue->getFront()->attack() );

      displayRoll(team1Queue->getFront(), true);
      displayRoll(team2Queue->getFront(), false);

      displayDamage(team2Queue->getFront(), character2Strength);

      lastAttacker = 1;

    }

  }

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
void Game::displayDamage(Character *character, const int &originalStrength) {

  if (character->getStrengthPts() <= 0) {
    cout << "Total inflicted damage: " << originalStrength << endl;
  } else if (character->getStrengthPts() > originalStrength) {
    cout << "Total inflicted damage: 0" << endl;
  } else {
    cout << "Total inflicted damage: " << originalStrength - character->getStrengthPts() << endl;
  }

  cout << character->getName() << "'s strength after this attack: ";

  if (character->getStrengthPts() > 0) {
    cout << character->getStrengthPts();
  } else {
    cout << 0 << endl;
    cout << character->getName() << " has died." << endl;
  }

   cout << endl << endl;

}


/***********************************************************************************************
** Description: Following an attack and defense, this function takes a pointer to a
** Character and a constant reference to a boolean, then outputs the result of a dice roll to
** the screen using the getAttackPts or getDefensePts method as appropriate.
***********************************************************************************************/
void Game::displayRoll(Character *character, const bool &isAttacker) {
  if (isAttacker) {
    cout << character->getName() << "'s hit points are " << character->getAttackPts() << endl;
  } else {
    cout << character->getName() << "'s defense points are " << character->getDefensePts() << endl;

  }

}


/***********************************************************************************************
** Description: Before an attack and defense call, this function takes a pointer to a
** Character, a constant reference to an integer for the fighter number (1 or 2), and a constant
** reference to a boolean to indicate if the character is attacking or defending during this
** encounter. It then outputs the necessary information on the character to the screen using
** public methods in the object and depending on whether the character was attacking or
** defending.
***********************************************************************************************/
void Game::displayType(Character *character, const bool &isAttacker) {

  if (isAttacker) {
    cout << "Attacker: " << character->getName() << " - " << character->getType() << endl;
  } else {
    cout << "Defender: " << character->getName() << " - " << character->getType() << endl;
    cout << "Defender Armor: " << character->getArmorPts() << endl;
    cout << "Defender Strength: " << character->getStrengthPts() << endl;
  }

}


/***********************************************************************************************
** Description: Function that takes two integers representing the number of the decision order
** from the menu prompt (selecting fighter 1 or fighter 2), followed by the menu choice of
** character type. Memory is then allocated for the appropriate character and the pointer is
** assigned to the correct fighter data member.
***********************************************************************************************/
void Game::addFighter(Container* teamQueue, int choice, string fighterName) {

   Character* newFighter = nullptr;

    switch (choice) {

      case 1 : newFighter = new Barbarian(fighterName);
               break;

      case 2 : newFighter = new BlueMen(fighterName);
               break;

      case 3 : newFighter = new HarryPotter(fighterName);
               break;

      case 4 : newFighter = new Medusa(fighterName);
               break;

      case 5 : newFighter = new Vampire(fighterName);
               break;

      default : {}

    }

    teamQueue->addBack(newFighter);

}


/***********************************************************************************************
** Description: Function that takes a pointer to a Container representing a team's list of fighters
***********************************************************************************************/
void Game::promptForFighters(Container* teamQueue, int teamSize) {

  int fightersAdded = 0;

  do {

    int fighterChosen = gameMenu->getIntFromPrompt("Who should fighter " + to_string(fightersAdded + 1) + " be?", 1, gameMenu->getMenuChoices(), true);
    string fighterName = gameMenu->getStrFromPrompt("What should this fighter's name be?", false);
    addFighter(teamQueue, fighterChosen, fighterName);
    fightersAdded++;

  } while (fightersAdded < teamSize);

}
