#pragma once

#include "EffectConstants.h"

class Unit;

struct DollEffect
{
    virtual EffectID GetID() const = 0;
    virtual char const* GetName() const = 0;
    virtual char const* GetIconPath() const { return nullptr; }
    // returning non-nullptr value here will substitute the current object with the returned object
    // this can be used to allow effect instances to locally store information on a per-simulation basis
    // (note: returned pointer will be owned by the character instance (and freed there). if an effect instance was created by reinstance, its own reinstance member should never return nullptr!)
    virtual DollEffect* Reinstance() const { return nullptr; }
  
    // ==== HOOKS ====
  
    // Called when effect is initially applied/removed
    virtual void OnApply(Unit* character) { }
    virtual void OnRemove(Unit* character) { }
};
