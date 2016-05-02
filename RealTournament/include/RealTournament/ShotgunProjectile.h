// ShotgunProjectile.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Projectile.h"

namespace real_tournament
{
	class ShotgunProjectile final : public Projectile
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Projectile)

		///////////////////
		///   Methods   ///
	public:

		void on_collision(Entity& entity, const CollisionData& info) override;

	protected:

		void on_spawn() override;

		////////////////
		///   Data   ///
	public:

		int _bounces = 0;
	};
}
