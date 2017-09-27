#include "PaperDoll.h"

#include "Effect.h"
#include "EffectMgr.h"
#include <cassert>

#define ct_copy_init(d, ...) d(other.d), ct_copy_init(__VA_ARGS__)

Character::Character(SimulationInstance const* instance, Character const& other)
: _instance(instance), _profession(other._profession),
  _baseStats(other._baseStats), _integralStats(other._integralStats), _fractionalStats(other._fractionalStats),
  _conditionDamage(other._conditionDamage), _conditionDuration(other._conditionDuration), _boonDuration(other._boonDuration)
{
    _effects.reserve(other._effects.size());
    for (auto const& pair : other._effects)
    {
        if (DollEffect* copy = pair.second->Reinstance())
            _effects.emplace(pair.first, copy);
        else
            _effects.insert(pair);
    }
}

Character::Character(SimulationInstance const* instance, Profession const* profession, BasicDoll const* baseStats)
: _instance(instance), _profession(profession), _baseStats(baseStats)
{
    // initialize array members
    _integralStats.fill(0);
    _fractionalStats.fill(0.0);
    _conditionDamage.fill(0);
    _conditionDuration.fill(0.0);
    _boonDuration.fill(0.0);

    // default values for derived stats
    _fractionalStats[STAT_CRITICAL_CHANCE-NUM_INTEGRAL_STATS] = -895.0 / 2100;
    _fractionalStats[STAT_CRITICAL_DAMAGE-NUM_INTEGRAL_STATS] = 1.5;
    for (int i=0; i < NUM_BASE_STATS; ++i)
        ApplyStatBonus(Stats(i), baseStats->GetBasicStat(Stats(i)));
}

uint32 Character::GetStat(Stats stat) const
{
    assert(stat < NUM_INTEGRAL_STATS);
    return _integralStats[stat];
}

double Character::GetFractionalStat(Stats stat) const
{
    assert(stat >= NUM_INTEGRAL_STATS && stat < NUM_STATS);
    return _fractionalStats[stat-NUM_INTEGRAL_STATS];
}

void Character::ApplyStatBonus(Stats stat, int32 value)
{
    assert(stat < NUM_INTEGRAL_STATS);
    if (value < 0 && uint32(-value) > _integralStats[stat])
        value = -int32(_integralStats[stat]);
    _integralStats[stat] += value;
  
    // update derived stats
    switch(stat)
    {
        case STAT_DEFENSE:
        case STAT_TOUGHNESS:
            ApplyStatBonus(STAT_ARMOR, value);
            break;
        case STAT_VITALITY:
            ApplyStatBonus(STAT_MAX_HEALTH, value*10);
            break;
        case STAT_PRECISION:
            ApplyStatBonus(STAT_CRITICAL_CHANCE, double(value)/2100);
            break;
        case STAT_FEROCITY:
            ApplyStatBonus(STAT_CRITICAL_DAMAGE, double(value)/1500);
            break;
        case STAT_CONDITION_DAMAGE_BASE:
            for (int i=0; i < NUM_CONDITIONS; ++i)
                _conditionDamage[i] += value;
            break;
        case STAT_EXPERTISE:
        {
            double const delta = double(value)/1500;
            for (int i=0; i < NUM_CONDITIONS; ++i)
                _conditionDuration[i] += delta;
            break;
        }
        case STAT_CONCENTRATION:
        {
            double const delta = double(value)/1500;
            for (int i=0; i < NUM_BOONS; ++i)
                _boonDuration[i] += delta;
            break;
        }
        default:
            break;
  }
}

void Character::ApplyStatBonus(Stats stat, double value)
{
    assert(stat >= NUM_INTEGRAL_STATS && stat < NUM_STATS);
    _fractionalStats[stat-NUM_INTEGRAL_STATS] += value;
}

void Character::ApplyEffect(EffectID id)
{
    DollEffect* eff = sEffectManager.GetBaseEffect(id);
    if (DollEffect* copy = eff->Reinstance())
        ApplyEffect(copy);
    else
        ApplyEffect(eff);
}

void Character::ApplyEffect(DollEffect* eff)
{
    _effects.emplace(eff->GetID(), eff);
    eff->OnApply(this);
}

void Character::RemoveEffect(DollEffect* eff)
{
    auto pair = _effects.equal_range(eff->GetID());
    for (auto it = pair.first; it != pair.second; ++it)
    {
        if (it->second == eff)
        {
            _effects.erase(it);
            eff->OnRemove(this);
            break;
        }
    }
    sEffectManager.CleanupEffect(eff);
}

void Character::RemoveEffectByID(EffectID id)
{
    std::vector<DollEffect*> del;
    auto pair = _effects.equal_range(id);
    for (auto it = pair.first; it != pair.second; ++it)
        del.push_back(it->second);
    _effects.erase(pair.first, pair.second);
    for (DollEffect* eff : del)
    {
        eff->OnRemove(this);
        sEffectManager.CleanupEffect(eff);
    }
}
