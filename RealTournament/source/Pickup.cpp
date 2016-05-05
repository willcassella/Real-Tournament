// Pickup.cpp

#include <Engine/World.h>
#include "../include/RealTournament/Pickup.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::Pickup);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void Pickup::on_collision(Entity& entity, const CollisionData& /*data*/)
	{
		auto* player = Cast<Player>(entity);
		if (player && !spawn_pad.is_null())
		{
			auto* spawnPad = this->get_world().get_object(spawn_pad);
			spawnPad->spawn_timer = spawnPad->spawn_timer_start;
			spawn_pad = nullptr;

			this->on_pickup(*player);
		}
	}

	void Pickup::on_initialize()
	{
		this->Base::on_initialize();
		this->get_world().bind_event("update", *this, &Pickup::on_update);
	}

	void Pickup::on_update(float dt)
	{
		if (!spawn_pad.is_null())
		{
			this->rotate(Vec3::Up, degrees(dt * 25));
		}
	}
}
