#pragma once

#include "typedefs.h"
#include "AuraConstants.h"
#include "DollConstants.h"
#include <vector>
#include <cassert>

struct BasicDoll
{
  uint16 stats[NUM_BASE_STATS];
  void SetBasicStat(Stats stat, uint16 value) { stats[stat] = value; }
  uint16 GetBasicStat(Stats stat) const { return stats[stat]; }
};

class Profession;
class SimulationInstance;
struct DollModifier;
struct DynamicStatModifier;

/* initialization flow for Character is as follows:
    1. create with basic info
    2. apply persistent modifiers (sigils, food, any permanent modifiers from traits etc)
    3. call ::Initialize to calculate derived stats based on this
*/
class Character
{
  public:
    Character(Profession* profession, BasicDoll const& doll);
    
    void Initialize();
    
    void AssertInit() { assert(_hadInitialization); }
    
    // modifier system
    void InitialApply(DollModifier* mod);
    void RegisterDynamicStatModifier(DynamicStatModifier* mod) { _dynamicStatMods.push_back(mod); }
    
    // stats system
    void SetStatDynamic(Stats stat) { _dynamicStats[stat] = true; }
    uint16 GetStat(SimulationInstance const* instance, Stats stat) const;
    double GetFractionalStat(SimulationInstance const* instance, Stats stat) const;
    uint16 GetBaseStat(Stats stat) const { return _baseStats.GetBasicStat(stat); }
    void ApplyStatBonus(Stats stat, uint16 value);
    void ApplyStatBonus(Stats stat, int value) { ApplyStatBonus(stat, uint16(value)); }
    void ApplyStatBonus(Stats stat, double value);
  
  private:
    bool _hadInitialization;
    Profession* const _profession;
    
    BasicDoll const _baseStats;
    bool _dynamicStats[NUM_STATS];
    uint16 _integralStats[NUM_INTEGRAL_STATS];
    double _fractionalStats[NUM_STATS-NUM_INTEGRAL_STATS];
    uint16 _conditionDamage[NUM_CONDITIONS];
    double _conditionDuration[NUM_CONDITIONS];
    double _boonDuration[NUM_BOONS];
    std::vector<DynamicStatModifier*> _dynamicStatMods;
};
