/*********************************************************************
** Description: Specification file for the Character class.
*********************************************************************/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

class Character {

  public:
  Character();
  Character(std::string nameIn);
  virtual ~Character() {};
  virtual int attack() = 0;
  virtual int defend(int hitPts) = 0;

  int rollDie(int numSides, int numDice);
  void restoreHealth(const int &originalStrength);

  int getAttackPts();
  int getDefensePts();
  int getArmorPts();
  int getStrengthPts();
  int getNumAttackDice();
  int getNumAttackDieSides();
  int getNumDefenseDice();
  int getNumDefenseDieSides();
  std::string getCharacteristics();
  std::string getName();
  std::string getType();

  void setAttackPts(int attack);
  void setDefensePts(int defense);
  void setArmorPts(int armor);
  void setStrengthPts(int strength);
  void setNumAttackDice(int dice);
  void setNumAttackDieSides(int sides);
  void setNumDefenseDice(int dice);
  void setNumDefenseDieSides(int sides);
  void setCharacteristics(std::string description);
  void setName(std::string characterName);
  void setType(std::string characterType);

  private:

  protected:
    int attackPts, defensePts, armorPts, strengthPts, numAttackDice,
    numAttackSides, numDefenseDice, numDefenseSides;
    std::string characteristics, name, type;

};

#endif
