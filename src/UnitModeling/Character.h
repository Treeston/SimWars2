#pragma once

#include "Unit.h"

class Profession;

class Character : public Unit
{
  public:
    Character(SimulationInstance const* instance, Character const& other);
    Character(SimulationInstance const* instance, BasicDoll const* baseStats, Profession const* profession);
    
  private:
    Profession const* const _profession;
};
