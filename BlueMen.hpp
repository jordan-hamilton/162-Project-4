/*********************************************************************
** Description: Specification file for the Blue Men class.
*********************************************************************/

#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP

#include "Character.hpp"

class BlueMen : public Character {

  public:
    BlueMen() : Character() {
      setArmorPts(3);
      setStrengthPts(12);
      setNumAttackDice(2);
      setNumAttackDieSides(10);
      setNumDefenseDice(3);
      setNumDefenseDieSides(6);
      setCharacteristics("They are small, 6 inch tall, but fast and tough. \
They are hard to hit so they can take some damage. They can also do a LOT of \
damage when they crawl inside enemies' armor or clothing.");
      setType("Blue Men");
    }

    int attack() override;
    int defend(int hitPts) override;

  private:


};

#endif
