#pragma once

#include "typedefs.h"
#include "AuraConstants.h"
#include "DollConstants.h"
#include "EffectConstants.h"
#include <array>
#include <unordered_map>

struct BasicDoll
{
    uint32 stats[NUM_BASE_STATS] = { 0 };
    void SetBasicStat(Stats stat, uint32 value) { stats[stat] = value; }
    uint32 GetBasicStat(Stats stat) const { return stats[stat]; }
};

class Profession;
class SimulationInstance;
struct DollEffect;

class Character
{
    public:
        Character(Character const&) = delete;
        Character(SimulationInstance const* instance, Character const& other);
        Character(SimulationInstance const* instance, Profession const* profession, BasicDoll const* baseStats);
    
        // stats system
        uint32 GetStat(Stats stat) const;
        double GetFractionalStat(Stats stat) const;
        uint32 GetBaseStat(Stats stat) const { return _baseStats->GetBasicStat(stat); }
        void ApplyStatBonus(Stats stat, int32 value);
        void ApplyStatBonus(Stats stat, uint32 value) { ApplyStatBonus(stat, int32(value)); }
        void ApplyStatBonus(Stats stat, double value);

        void ApplyEffect(EffectID id);
        void ApplyEffect(DollEffect* eff);
        void RemoveEffect(DollEffect* eff);
        void RemoveEffectByID(EffectID id);
  
     private:
        SimulationInstance const* const _instance;
        Profession const* const _profession;
    
        BasicDoll const* const _baseStats;
        std::array<uint32,NUM_INTEGRAL_STATS> _integralStats;
        std::array<double,NUM_STATS-NUM_INTEGRAL_STATS> _fractionalStats;
        std::array<uint32,NUM_CONDITIONS> _conditionDamage;
        std::array<double,NUM_CONDITIONS> _conditionDuration;
        std::array<double,NUM_BOONS> _boonDuration;
    
        std::unordered_multimap<EffectID, DollEffect*> _effects;
};
