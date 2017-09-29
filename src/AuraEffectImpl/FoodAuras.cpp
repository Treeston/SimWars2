#include "Effect.h"
#include "EffectMgr.h"
#include "Unit.h"

struct SweetSpicyButternutEffect : DollEffect
{
    EffectID GetID() const override { return EFF_FOOD_SWEET_SPICY_BUTTERNUT; }
    char const* GetName() const override { return "Bowl of Sweet and Spicy Butternut Squash Soup"; }
  
    void OnApply(Unit* c) override
    {
        c->ApplyStatBonus(STAT_POWER, 100);
        c->ApplyStatBonus(STAT_FEROCITY, 70);
    }

    void OnRemove(Unit* c) override
    {
        c->ApplyStatBonus(STAT_POWER, -100);
        c->ApplyStatBonus(STAT_FEROCITY, -70);
    }
};
  
void LoadFoodEffectData(StaticEffectManager& mgr)
{
    mgr.RegisterBaseEffect<SweetSpicyButternutEffect>();
}