// SpawnPad.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include "../include/RealTournament/SpawnPad.h"
#include "../include/RealTournament/Pickup.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::SpawnPad)
.Field("spawn_type", &SpawnPad::spawn_type)
.Field("spawn_offset", &SpawnPad::spawn_offset)
.Field("spawn_timer_start", &SpawnPad::spawn_timer_start)
.Field("spawn_timer", &SpawnPad::spawn_timer);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	Entity* SpawnPad::perform_spawn(PerformSpawn mode)
	{
		switch (mode)
		{
		case Reset_Timer:
			this->spawn_timer = this->spawn_timer_start;
			break;

		case Keep_Timer:
			break;

		case Stop_Timer:
			this->spawn_timer = 0;
			break;
		}

		if (!this->spawn_type.is_null())
		{
			auto& object = this->get_world().spawn(this->spawn_type);
			object.set_world_location(this->get_world_location() + this->spawn_offset);
			
			// Special case for spawning pickups
			if (auto pickup = Cast<Pickup>(object))
			{
				pickup->spawn_pad = *this;
			}

			return &object;
		}
		else
		{
			return nullptr;
		}
	}

	void SpawnPad::on_initialize()
	{
		this->Base::on_initialize();
		this->get_world().bind_event("update", *this, &SpawnPad::on_update);
	}

	void SpawnPad::on_update(float dt)
	{
		if (spawn_timer == 0)
		{
			return;
		}

		this->spawn_timer -= dt;
		if (this->spawn_timer <= 0)
		{
			this->perform_spawn(Stop_Timer);
		}
	}
}
