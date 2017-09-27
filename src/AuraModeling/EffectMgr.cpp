#include "EffectMgr.h"

#define load_decl(T) void Load ## T ## EffectData(StaticEffectManager&);
#define load_call(T) Load ## T ## EffectData(*this);

load_decl(Food);

StaticEffectManager::StaticEffectManager()
{
    load_call(Food);
}

StaticEffectManager::~StaticEffectManager()
{
    for (DollEffect* eff : _data)
        delete eff;
}