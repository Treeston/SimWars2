#pragma once

enum Stats
{
    STAT_POWER,
    STAT_DEFENSE,
    STAT_TOUGHNESS,
    STAT_VITALITY,
    STAT_PRECISION,
    STAT_FEROCITY,
    STAT_CONDITION_DAMAGE_BASE,
    STAT_EXPERTISE,
    STAT_CONCENTRATION,
    STAT_HEALING_POWER,
    STAT_AGONY_RESISTANCE,
    NUM_BASE_STATS,
  
    STAT_ARMOR = NUM_BASE_STATS,
    STAT_MAX_HEALTH,
    NUM_INTEGRAL_STATS,
  
    STAT_CRITICAL_CHANCE = NUM_INTEGRAL_STATS,
    STAT_CRITICAL_DAMAGE,
    NUM_STATS
};

inline char const* GetStatName(Stats stat)
{
    switch (stat)
    {
        case STAT_POWER: return "Power";
        case STAT_DEFENSE: return "Defense";
        case STAT_TOUGHNESS: return "Toughness";
        case STAT_VITALITY: return "Vitality";
        case STAT_PRECISION: return "Precision";
        case STAT_FEROCITY: return "Ferocity";
        case STAT_CONDITION_DAMAGE_BASE: return "Condition Damage";
        case STAT_EXPERTISE: return "Expertise";
        case STAT_CONCENTRATION: return "Concentration";
        case STAT_HEALING_POWER: return "Healing Power";
        case STAT_AGONY_RESISTANCE: return "Agony Resistance";
        case STAT_ARMOR: return "Armor";
        case STAT_MAX_HEALTH: return "Health";
        case STAT_CRITICAL_CHANCE: return "Critical Chance";
        case STAT_CRITICAL_DAMAGE: return "Critical Damage";
        default: return "Invalid stat";
    }
}
