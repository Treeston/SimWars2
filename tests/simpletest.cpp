#include <cstdio>
#include "PaperDoll.h"

void summarize(Character const& c)
{
    printf("Character dump:\n");
    for (uint8 i = 0; i < NUM_INTEGRAL_STATS; ++i)
        printf("%s: %u\n", GetStatName(Stats(i)), c.GetStat(Stats(i)));
    for (uint8 i = NUM_INTEGRAL_STATS; i < NUM_STATS; ++i)
        printf("%s: %.2f%%\n", GetStatName(Stats(i)), c.GetFractionalStat(Stats(i)) * 100);
}

int main()
{
    BasicDoll doll;
    doll.SetBasicStat(STAT_POWER, 1000);
    doll.SetBasicStat(STAT_DEFENSE, 0);
    doll.SetBasicStat(STAT_TOUGHNESS, 1000);
    doll.SetBasicStat(STAT_VITALITY, 1000);
    doll.SetBasicStat(STAT_PRECISION, 1000);
    doll.SetBasicStat(STAT_FEROCITY, 0);
    doll.SetBasicStat(STAT_CONDITION_DAMAGE_BASE, 0);
    doll.SetBasicStat(STAT_EXPERTISE, 0);
    doll.SetBasicStat(STAT_CONCENTRATION, 0);
    doll.SetBasicStat(STAT_HEALING_POWER, 0);
    doll.SetBasicStat(STAT_AGONY_RESISTANCE, 0);

    Character c(nullptr, nullptr, &doll);
    printf("We created a character at %p - its stats are:\n", &c);
    summarize(c);
    printf("\n");

    c.ApplyEffect(EFF_FOOD_SWEET_SPICY_BUTTERNUT);
    printf("After eating Butternut Squash, its stats are:\n");
    summarize(c);
    printf("\n");

    c.RemoveEffectByID(EFF_FOOD_SWEET_SPICY_BUTTERNUT);
    printf("Now we removed the Butternut Squash, stats are:\n");
    summarize(c);
    printf("\n");

    system("pause");
}
