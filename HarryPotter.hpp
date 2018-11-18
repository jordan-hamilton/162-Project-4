/*********************************************************************
** Description: Specification file for the Harry Potter class.
*********************************************************************/

#ifndef HARRYPOTTER_HPP
#define HARRYPOTTER_HPP

#include "Character.hpp"

class HarryPotter : public Character {

  public:
    HarryPotter() : Character() {
      setArmorPts(0);
      setStrengthPts(10);
      setNumAttackDice(2);
      setNumAttackDieSides(6);
      setNumDefenseDice(2);
      setNumDefenseDieSides(6);
      setCharacteristics("Harry Potter is a wizard.");
      setType("Harry Potter");
      setHasRevived(false);
    }

    int attack() override;
    int defend(int hitPts) override;

    private:
      bool hasRevived;
      void revive();
      bool getHasRevived();
      void setHasRevived(bool lifeUsed);

};

#endif
