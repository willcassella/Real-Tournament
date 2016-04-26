// Weapon.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/RealTournament/Weapon.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::Weapon)
.Field("model", &Weapon::model)
.Field("magazine_size", &Weapon::magazine_size)
.Field("ammo", &Weapon::ammo);
