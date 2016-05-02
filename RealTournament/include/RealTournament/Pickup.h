// Pickup.h
#pragma once

#include "Player.h"

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

		///////////////////
		///   Methods   ///
	protected:

		void on_collision(Entity& entity) override;

		virtual void on_pickup(Player& player) = 0;
	};
}
