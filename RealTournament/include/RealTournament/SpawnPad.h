// SpawnPad.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/SubClassOf.h>
#include <Engine/Entity.h>

namespace real_tournament
{
	using namespace willow;

	class SpawnPad final : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)

		/////////////////
		///   Types   ///
	public:

		enum PerformSpawn
		{
			/** Resets the timer to 'spawn_timer_start'. */
			Reset_Timer,
			
			/** The timer continues where it is. */
			Keep_Timer,

			/** The timer is set to '0'. */
			Stop_Timer,
		};

		//////////////////
		///   Fields   ///
	public:

		/** The type of Entity to spawn. */
		SubClassOf<Entity> spawn_type;

		/** The location offset to spawn this object at. */
		Vec3 spawn_offset = {0, 3, 0};

		/** The amount of time that passes between each spawn ('0' for no timer, only spawns when told). */
		float spawn_timer_start = 0.f;

		/** The amount of time until the object spawns ('0' to disable). */
		float spawn_timer = 0.f;

		///////////////////
		///   Methods   ///
	public:

		/** Spawns the object.
		* 'mode' - whether to reset the timer or not. */
		Entity* perform_spawn(PerformSpawn mode);
	
	protected:

		void on_initialize() override;

	private:

		void on_update(float dt);
	};
}
