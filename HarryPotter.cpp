#include "HarryPotter.hpp"


/***********************************************************************************************
** Description: An attack method that rolls the number of dice for this object, returns a random
** number, and sets and returns the object's attack points as an integer.
***********************************************************************************************/
int HarryPotter::attack() {

  setAttackPts( rollDie(numAttackDice, numAttackSides) );

  return getAttackPts();

}


/***********************************************************************************************
** Description: A defend method that takes an integer representing the attack points of the
** other character. The number of dice this object has is rolled, then the defense points of the
** object are set to that value. The strength is set to the current strength less the attack
** points passed to the function after the defense roll and armor points are subtracted. If the
** object's strength after the attack is less than or equal to 0 and the object hasn't had the
** Hogwarts special ability activated yet, then the ability is activated with the revive
** method. Then, the defense points are returned as an integer.
***********************************************************************************************/
int HarryPotter:: defend(int hitPts) {

  int damage = 0;

  setDefensePts( rollDie(numDefenseDice, numDefenseSides) );

  damage = hitPts - getDefensePts() - getArmorPts();

  if ( damage > 0) {
    setStrengthPts( getStrengthPts() - damage );
  }

  if (getStrengthPts() <= 0 && !getHasRevived()) {
    revive();
  }

  return getDefensePts();

}



/***********************************************************************************************
** Description: A method that sets the object's strength back to 20, then calls setHasRevived
** passing true to ensure the strength isn't reset to 20 more than once.
***********************************************************************************************/
void HarryPotter::revive() {

    setStrengthPts(20);
    setHasRevived(true);

}


/***********************************************************************************************
** Description: Returns a boolean to indicate if revive has been called previously.
***********************************************************************************************/
bool HarryPotter::getHasRevived() {
  return hasRevived;
}


/***********************************************************************************************
** Description: Takes a boolean to set the hasRevived data member's value.
***********************************************************************************************/
void HarryPotter::setHasRevived(bool lifeUsed) {
  hasRevived = lifeUsed;
}
