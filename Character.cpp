#include "Character.hpp"


/***********************************************************************************************
** Description: A default constructor that initalizes data members.
***********************************************************************************************/
Character::Character() {

  attackPts = 0;
  defensePts = 0;
  armorPts = -1;
  strengthPts = -1;
  numAttackDice = -1;
  numAttackSides = -1;
  numDefenseDice = -1;
  numDefenseSides = -1;
  characteristics = "";
  name = "";

}


/***********************************************************************************************
** Description: An overloaded constructor that takes a string to set the character's name and
** initalizes data members.
***********************************************************************************************/
Character::Character(std::string nameIn) {

  attackPts = 0;
  defensePts = 0;
  armorPts = -1;
  strengthPts = -1;
  numAttackDice = -1;
  numAttackSides = -1;
  numDefenseDice = -1;
  numDefenseSides = -1;
  characteristics = "";
  name = nameIn;

}


/***********************************************************************************************
** Description: A method that takes an integer representing the number of dice that should be
** rolled, and the number of sides on the dice. The result of each roll is summed in a for loop
** and then returned as an integer.
***********************************************************************************************/
int Character::rollDie(int numDice, int numSides) {

  int result = 0;

  for (int i = 0; i < numDice; i++) {
    result += rand() % numSides + 1;
  }

  return result;

}


/***********************************************************************************************
** Description: A method that takes an integer representing the health of a Character before an
** attack, then
***********************************************************************************************/
void Character::restoreHealth(const int &originalStrength) {

  if ( originalStrength != getStrengthPts() ) {

    int addedHealth = rand() % getStrengthPts() + 1;

    if (getStrengthPts() + addedHealth <= originalStrength) {
      setStrengthPts( getStrengthPts() + addedHealth );
    } else {
      setStrengthPts(originalStrength);
    }

  }


}


int Character::getAttackPts() {
  return attackPts;
}


int Character::getDefensePts() {
  return defensePts;
}


int Character::getArmorPts() {
  return armorPts;
}


int Character::getStrengthPts() {
  return strengthPts;
}


int Character::getNumAttackDice() {
  return numAttackDice;
}


int Character::getNumAttackDieSides() {
  return numAttackSides;
}


int Character::getNumDefenseDice() {
  return numDefenseDice;
}


int Character::getNumDefenseDieSides() {
  return numDefenseSides;
}


std::string Character::getCharacteristics() {
  return characteristics;
}


std::string Character::getName() {
  return name;
}


std::string Character::getType() {
  return type;
}


void Character::setAttackPts(int attack) {
  attackPts = attack;
}


void Character::setDefensePts(int defense) {
  defensePts = defense;
}


void Character::setArmorPts(int armor) {
  armorPts = armor;
}


void Character::setStrengthPts(int strength) {
  strengthPts = strength;
}


void Character::setNumAttackDice(int dice) {
  numAttackDice = dice;
}


void Character::setNumAttackDieSides(int sides) {
  numAttackSides = sides;
}


void Character::setNumDefenseDice(int dice) {
  numDefenseDice = dice;
}


void Character::setNumDefenseDieSides(int sides) {
  numDefenseSides = sides;
}


void Character::setCharacteristics(std::string description) {
  characteristics = description;
}


void Character::setName(std::string characterName) {
  name = characterName;
}


void Character::setType(std::string characterType) {
  type = characterType;
}
