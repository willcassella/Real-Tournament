// Projectile.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Entity.h>

namespace real_tournament
{
	using namespace willow;

	class Projectile : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)

		//////////////////
		///   Fields   ///
	public:

		/** The amount of damage this projectile does when it hits a Player. */
		float damage = 10;

		/** The velocity of this projectile. */
		Vec3 velocity;

		/** The amount of time before this projectile is destroyed. */
		float life = 10;

		///////////////////
		///   Methods   ///
	protected:

		void on_initialize() override;

		/** Handles collision with player. DOES NOT handle destruction of projectile or any other collision behavior. */
		void on_collision(Entity& collidee) override;

	private:

		void on_update(float dt);
	};
}
