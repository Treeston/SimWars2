#pragma once

#include "DollConstants.h"

struct BasicDoll
{
    uint32 stats[NUM_BASE_STATS] = { 0 };
    void SetBasicStat(Stats stat, uint32 value) { stats[stat] = value; }
    uint32 GetBasicStat(Stats stat) const { return stats[stat]; }
};