// Weapon.cpp

#include "../include/RealTournament/Weapon.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(RealTournament::Weapon)
.Field("Model", &Weapon::Model)
.Field("MagazineSize", &Weapon::MagazineSize)
.Field("Ammo", &Weapon::Ammo);
