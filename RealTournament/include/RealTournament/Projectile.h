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

		/** The velocity of this projectile. */
		Vec3 velocity;

		/** The amount of time before this projectile is destroyed. */
		float life = 7.f;

		///////////////////
		///   Methods   ///
	protected:

		void on_initialize() override;

		void on_collision(Entity& entity, const CollisionData& data) override;

	private:

		void on_update(float dt);
	};
}
