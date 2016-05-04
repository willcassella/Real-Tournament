// Helmet.h
#pragma once

#include "Pickup.h"

namespace real_tournament
{
	class Helmet final : public Pickup
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Pickup)

		//////////////////
		///   Fields   ///
	public:

		Handle<Helmet> next_helmet;
		Handle<Helmet> previous_helmet;

		///////////////////
		///   Methods   ///
	public:

		/** Drops the helmet. */
		void drop();

		void on_collision(Entity& entity, const CollisionData& data) override;

	protected:

		void on_spawn() override;

		void on_pickup(Player& player) override;

	private:

		void post_drop_update(float dt);

		////////////////
		///   Data   ///
	private:

		bool _dropped = false;
		float _life = 10.f;
	};
}
