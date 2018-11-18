#include <cstdlib>

#include "Game.hpp"

using std::cout;
using std::endl;


Game::Game() {

}


/***********************************************************************************************
** Description: Overloaded constructor that takes two integers, then calls the setFighter
** function twice to allocate memory for Character objects that will be used in the game.
***********************************************************************************************/
Game::Game(int character1, int character2) {
  setFighter(1, character1);
  setFighter(2, character2);
  fight(fighter1, fighter2);
}


/***********************************************************************************************
** Description: Destructor that deletes pointers to Character objects.
***********************************************************************************************/
Game::~Game() {

  if (fighter1) {
    delete fighter1;
    fighter1 = nullptr;
  }

  if (fighter2) {
    delete fighter2;
    fighter2 = nullptr;
  }

}


/***********************************************************************************************
** Description: Takes two pointers to Character objects, then initializes a random generator
** seed and sets the random generator seed for any random events in the game. The strength
** of each character is stored in temporary variables, then either character1 or character2
** attacks first, depending on the return value of the firstStrike method. Fighter information
** and fight results are displayed with displayType, displayRoll and displayDamage methods.
** The most recent attacker is stored in the lastAttacker variable, then a while loop repeats,
** continues the fight, alternating attackers until one Character's strength is depleted.
***********************************************************************************************/
void Game::fight(Character* character1, Character* character2) {

  unsigned seed = time(0);
  srand(seed);

  int lastAttacker = 0;

  int character1Strength = character1->getStrengthPts();
  int character2Strength = character2->getStrengthPts();

  cout << endl;

  if (firstStrike() == 1) {

    displayType(character1, 1, true);
    displayType(character2, 2, false);

    character2->defend( character1->attack() );

    displayRoll(character1, true);
    displayRoll(character2, false);

    displayDamage(character2, 2, character2Strength);

    lastAttacker = 1;

  } else {

    displayType(character2, 2, true);
    displayType(character1, 1, false);

    character1->defend( character2->attack() );

    displayRoll(character2, true);
    displayRoll(character1, false);

    displayDamage(character1, 1, character1Strength);

    lastAttacker = 2;

  }

  while( character1->getStrengthPts() > 0 && character2->getStrengthPts() > 0 ) {

    character1Strength = character1->getStrengthPts();
    character2Strength = character2->getStrengthPts();

    if (lastAttacker == 1) {

      displayType(character2, 2, true);
      displayType(character1, 1, false);

      character1->defend( character2->attack() );

      displayRoll(character2, true);
      displayRoll(character1, false);

      displayDamage(character1, 1, character1Strength);

      lastAttacker = 2;

    } else {

      displayType(character1, 1, true);
      displayType(character2, 2, false);

      character2->defend( character1->attack() );

      displayRoll(character1, true);
      displayRoll(character2, false);

      displayDamage(character2, 2, character2Strength);

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
void Game::displayDamage(Character *character, const int &characterNumber, const int &originalStrength) {

  if (character->getStrengthPts() <= 0) {
    cout << "Total inflicted damage: " << originalStrength << endl;
  } else if (character->getStrengthPts() > originalStrength) {
    cout << "Total inflicted damage: 0" << endl;
  } else {
    cout << "Total inflicted damage: " << originalStrength - character->getStrengthPts() << endl;
  }

  cout << "Defender's strength after this attack: ";

  if (character->getStrengthPts() > 0) {
    cout << character->getStrengthPts();
  } else {
    cout << 0 << endl;
    cout << "Fighter " << characterNumber << " has died." << endl;
    cout << "Fighter " << (characterNumber % 2 + 1) << " wins this fight.";
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
    cout << "Attacker hit points are " << character->getAttackPts() << endl;
  } else {
    cout << "Defender defense points are " << character->getDefensePts() << endl;

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
void Game::displayType(Character *character, const int &characterNumber, const bool &isAttacker) {

  if (isAttacker) {
    cout << "Attacker: Fighter " << characterNumber << " - " << character->getType() << endl;
  } else {
    cout << "Defender: Fighter " << characterNumber << " - " << character->getType() << endl;
    cout << "Defender Armor: " << character->getArmorPts() << endl;
    cout << "Defender Strength: " << character->getStrengthPts() << endl;
  }

}


/***********************************************************************************************
** Description: Returns a pointer to a character representing the first fighter chosen.
***********************************************************************************************/
Character* Game::getFighter1() {
  return fighter1;
}


/***********************************************************************************************
** Description: Returns a Character pointer for the second fighter chosen.
***********************************************************************************************/
Character* Game::getFighter2() {
  return fighter2;
}


/***********************************************************************************************
** Description: Function that takes two integers representing the number of the decision order
** from the menu prompt (selecting fighter 1 or fighter 2), followed by the menu choice of
** character type. Memory is then allocated for the appropriate character and the pointer is
** assigned to the correct fighter data member.
***********************************************************************************************/
void Game::setFighter(int fighter, int choice) {
  if (fighter == 1) {

    switch (choice) {

      case 1 : fighter1 = new Barbarian;
               break;

      case 2 : fighter1 = new BlueMen;
               break;

      case 3 : fighter1 = new HarryPotter;
               break;

      case 4 : fighter1 = new Medusa;
               break;

      case 5 : fighter1 = new Vampire;
               break;

      default : {}

    }

  } else if (fighter == 2) {

    switch (choice) {

      case 1 : fighter2 = new Barbarian;
               break;

      case 2 : fighter2 = new BlueMen;
               break;

      case 3 : fighter2 = new HarryPotter;
               break;

      case 4 : fighter2 = new Medusa;
               break;

      case 5 : fighter2 = new Vampire;

      default : {}

    }

  }
}
