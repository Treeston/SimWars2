#include "Character.h"

Character::Character(SimulationInstance const* instance, Character const& other)
: Unit(instance, other), _profession(other._profession) {}

Character::Character(SimulationInstance const* instance, BasicDoll const* baseStats, Profession const* profession)
: Unit(instance, baseStats), _profession(profession)
{
}