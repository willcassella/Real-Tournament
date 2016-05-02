// Shotgun.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Weapon.h"

namespace real_tournament
{
	class Shotgun final : public Weapon
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Weapon)

		///////////////////
		///   Methods   ///
	public:

		void fire() override;

	protected:

		void on_spawn() override;
	};
}
