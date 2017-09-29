#pragma once

#include "typedefs.h"
#include "AuraConstants.h"
#include "EffectConstants.h"
#include "PaperDoll.h"
#include <array>
#include <unordered_map>

class SimulationInstance;
struct DollEffect;

class Unit
{
    public:
        Unit(Unit const&) = delete;
        Unit(SimulationInstance const* instance, Unit const& other);
        Unit(SimulationInstance const* instance, BasicDoll const* baseStats);
    
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
  
    protected:
        SimulationInstance const* const _instance;
        BasicDoll const* const _baseStats;
        
    private:
        std::array<uint32,NUM_INTEGRAL_STATS> _integralStats;
        std::array<double,NUM_STATS-NUM_INTEGRAL_STATS> _fractionalStats;
        std::array<uint32,NUM_CONDITIONS> _conditionDamage;
        std::array<double,NUM_CONDITIONS> _conditionDuration;
        std::array<double,NUM_BOONS> _boonDuration;
    
        std::unordered_multimap<EffectID, DollEffect*> _effects;
};
