/*********************************************************************
** Description: Specification file for the Barbarian class.
*********************************************************************/

#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include "Character.hpp"

class Barbarian : public Character {

  public:
    Barbarian() : Character() {
      setArmorPts(0);
      setStrengthPts(12);
      setNumAttackDice(2);
      setNumAttackDieSides(6);
      setNumDefenseDice(1);
      setNumDefenseDieSides(6);
      setCharacteristics("Think Conan or Hercules from the movies. Big sword, \
big muscles, bare torso.");
      setType("Barbarian");
    }

    int attack() override;
    int defend(int hitPts) override;

};

#endif
