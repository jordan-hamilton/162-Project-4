#include "Medusa.hpp"


/***********************************************************************************************
** Description: An attack method that rolls the number of dice for this object, returns a random
** number, and sets and returns the object's attack points as an integer. If the dice roll adds
** up to 12, then glare is activated, instantly turning any character to stone. Only Harry
** Potter or a Vampire have chances of surviving this attack.
***********************************************************************************************/
int Medusa::attack() {

  setAttackPts( rollDie(numAttackDice, numAttackSides) );

  if (getAttackPts() == 12) {
    setAttackPts(1000);
  }

  return getAttackPts();

}


/***********************************************************************************************
** Description: A defend method that takes an integer representing the attack points of the
** other character. The number of dice this object has is rolled, then the defense points of the
** object are set to that value. The strength is set to the current strength less the attack
** points passed to the function after the defense roll and armor points are subtracted. Then,
** the defense points are returned as an integer.
***********************************************************************************************/
int Medusa::defend(int hitPts) {

  int damage = 0;

  setDefensePts( rollDie(numDefenseDice, numDefenseSides) );

  damage = hitPts - getDefensePts() - getArmorPts();

  if ( damage > 0) {
    setStrengthPts( getStrengthPts() - damage );
  }

  return getDefensePts();

}
