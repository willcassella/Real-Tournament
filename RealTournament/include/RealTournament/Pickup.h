// Pickup.h
#pragma once

#include "Player.h"
#include "SpawnPad.h"

namespace real_tournament
{
	using namespace willow;

	class Pickup : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)

		//////////////////
		///   Fields   ///
	public:

		/** The SpawnPad for this pickup. */
		Handle<SpawnPad> spawn_pad;

		///////////////////
		///   Methods   ///
	public:

		void on_collision(Entity& entity, const CollisionData& data) override;

	protected:

		void on_initialize() override;

		virtual void on_pickup(Player& player) = 0;

	private:

		void on_update(float dt);
	};
}
