/*********************************************************************
** Description: Specification file for the Vampire class.
*********************************************************************/

#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP

#include "Character.hpp"

class Vampire : public Character {

  public:
    Vampire() : Character() {
      setArmorPts(1);
      setStrengthPts(18);
      setNumAttackDice(1);
      setNumAttackDieSides(12);
      setNumDefenseDice(1);
      setNumDefenseDieSides(6);
      setCharacteristics("Suave, debonair, but vicious and surprisingly \
resilient");
      setType("Vampire");
    }

  int attack() override;
  int defend(int hitPts) override;


  private:
    bool charm();

};

#endif
