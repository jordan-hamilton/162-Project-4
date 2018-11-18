#include "Vampire.hpp"


/***********************************************************************************************
** Description: An attack method that rolls the number of dice for this object, returns a random
** number, and sets and returns the object's attack points as an integer.
***********************************************************************************************/
int Vampire::attack() {

  setAttackPts( rollDie(numAttackDice, numAttackSides) );

  return getAttackPts();

}


/***********************************************************************************************
** Description: A defend method that takes an integer representing the attack points of the
** other character. The number of dice this object has is rolled, then the defense points
** of the object are set to the value of the roll. If the charm method returns true, no damage
** is subtracted from the Vampire's strength. Otherwise, the strength is set to the current
** strength less the attack points passed to the function after the defense roll and armor
** points are subtracted. Then, the defense points are returned as an integer.
***********************************************************************************************/
int Vampire::defend(int hitPts) {

  int damage = 0;

  setDefensePts( rollDie(numDefenseDice, numDefenseSides) );

  if (!charm()) {
    damage = hitPts - getDefensePts() - getArmorPts();
  }

  if ( damage > 0) {
    setStrengthPts( getStrengthPts() - damage );
  }

  return getDefensePts();

}


/***********************************************************************************************
** Description: Calls rand() to return a number between 0 and 1 as a boolean value. If the
** result of rand() % 2 is 0 the damage is calculated in defend. Otherwise, the damage caused
** by an attack is set to 0.
***********************************************************************************************/
bool Vampire::charm() {
  return rand() % 2;
}
