#pragma once

#include "DollConstants.h"

class Character;
class SimulationInstance;

struct DollModifier
{
  virtual void InitialApply(Character* character) = 0;
};

struct DynamicStatModifier : DollModifier
{
  virtual void ModifyStat(SimulationInstance const* instance, Character const* character, Stats stat, uint16& value) { }
  virtual void ModifyStat(SimulationInstance const* instance, Character const* character, Stats stat, double& value) { }
};
