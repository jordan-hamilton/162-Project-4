/*********************************************************************
** Description: Specification file for the Medusa class.
*********************************************************************/

#ifndef MEDUSA_HPP
#define MEDUSA_HPP

#include "Character.hpp"

class Medusa : public Character {

  public:
    Medusa() : Character() {
      setArmorPts(3);
      setStrengthPts(8);
      setNumAttackDice(2);
      setNumAttackDieSides(6);
      setNumDefenseDice(1);
      setNumDefenseDieSides(6);
      setCharacteristics("Scrawny lady with snakes for hair which helps her \
during combat. Just don't look at her!");
      setType("Medusa");
    }

int attack() override;
int defend(int hitPts) override;


  private:


};

#endif
