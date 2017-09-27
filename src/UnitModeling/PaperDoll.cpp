#include "PaperDoll.h"

#include "DollModifiers.h"
#include <cassert>

Character::Character(Profession* profession, BasicDoll const& doll) :
_hadInitialization(false), _profession(profession), _baseStats(doll)
{
  for (int i=0; i < NUM_BASE_STATS; ++i)
    _integralStats[i] = doll.stats[i];
  _fractionalStats[STAT_CRITICAL_DAMAGE-NUM_INTEGRAL_STATS] = 1.5;
}

void Character::Initialize()
{
  assert(!_hadInitialization);
   
  // convert defense and toughness to armor
  ApplyStatBonus(STAT_ARMOR, GetStat(nullptr, STAT_DEFENSE) + GetStat(nullptr, STAT_TOUGHNESS));
  // convert vitality to max health
  // @todo profession max health field
  ApplyStatBonus(STAT_MAX_HEALTH, GetStat(nullptr, STAT_VITALITY) * 10);
  
  // convert precision to crit chance
  ApplyStatBonus(STAT_CRITICAL_CHANCE, double(GetStat(nullptr, STAT_PRECISION)-895)/2100);
  
  // convert ferocity to crit damage
  ApplyStatBonus(STAT_CRITICAL_DAMAGE, double(GetStat(nullptr, STAT_FEROCITY))/1500);
  
  // apply condition damage and duration from gear to all conditions
  uint16 const condiDamage = GetStat(nullptr, STAT_CONDITION_DAMAGE_BASE); 
  double const condiDuration = double(GetStat(nullptr, STAT_EXPERTISE))/1500;
  for (int i=0; i < NUM_CONDITIONS; ++i)
  {
    _conditionDamage[i] += condiDamage;
    _conditionDuration[i] += condiDuration;
  }
  
  // ditto for boon duration
  double const boonDuration = double(GetStat(nullptr, STAT_CONCENTRATION))/1500;
  for (int i=0; i < NUM_BOONS; ++i)
    _boonDuration[i] += boonDuration;
  
  _hadInitialization = true;
}

uint16 Character::GetStat(SimulationInstance const* instance, Stats stat) const
{
  assert(stat < NUM_INTEGRAL_STATS);
  assert(_hadInitialization || stat < NUM_BASE_STATS);
  
  if (!instance || !_dynamicStats[stat])
    return _integralStats[stat];
  
  uint16 value = _integralStats[stat];
  for (DynamicStatModifier* mod : _dynamicStatMods)
    mod->ModifyStat(instance, this, stat, value);
  return value;
}

double Character::GetFractionalStat(SimulationInstance const* instance, Stats stat) const
{
  assert(_hadInitialization);
  assert(stat >= NUM_INTEGRAL_STATS && stat < NUM_STATS);
  
  if (!instance || !_dynamicStats[stat])
    return _fractionalStats[stat-NUM_INTEGRAL_STATS];
  
  double value = _fractionalStats[stat-NUM_INTEGRAL_STATS];
  for (DynamicStatModifier* mod : _dynamicStatMods)
    mod->ModifyStat(instance, this, stat, value);
  return value;
}

void Character::ApplyStatBonus(Stats stat, uint16 value)
{
  assert(!_hadInitialization);
  assert(stat < NUM_INTEGRAL_STATS);
  _integralStats[stat] += value;
}

void Character::ApplyStatBonus(Stats stat, double value)
{
  assert(!_hadInitialization);
  assert(stat >= NUM_INTEGRAL_STATS && stat < NUM_STATS);
  _fractionalStats[stat-NUM_INTEGRAL_STATS] += value;
}
