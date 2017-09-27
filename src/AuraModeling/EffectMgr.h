#pragma once

#include "EffectConstants.h"
#include "Effect.h"
#include <array>
#include <cassert>

// this is a singleton class that manages the base DollEffect* instances
// if a specific effect needs separate effect instances for different contexts, it needs to implement ::ApplyFor and ::ReinstanceFor
class StaticEffectManager
{
    public:
        static StaticEffectManager const& instance()
        {
            static StaticEffectManager i;
            return i;
        }
    
        StaticEffectManager(StaticEffectManager const&) = delete;
        void operator=(StaticEffectManager const&) = delete;
  
    private:
        StaticEffectManager();
        ~StaticEffectManager();
    
    public:
        template <class E> void RegisterBaseEffect()
        {
            static_assert(std::is_base_of<DollEffect, E>::value, "Invalid class to RegisterBaseEffect");
            DollEffect* base = new E();
            _data[base->GetID()] = base;
        }
        DollEffect* GetBaseEffect(EffectID id) const { assert(id < NUM_EFFECTS); return _data[id]; }

        void CleanupEffect(DollEffect* eff) const
        {
            if (_data[eff->GetID()] != eff)
                delete eff;
        }

    private:
        std::array<DollEffect*, NUM_EFFECTS> _data;
};

#define sEffectManager StaticEffectManager::instance()
