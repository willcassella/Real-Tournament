// RealTournamentPlayer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Handle.h>
#include <Engine/Entities/Player.h>
#include <Engine/Components/Rendering/CameraComponent.h>
#include <Engine/Components/Physics/CapsuleColliderComponent.h>
#include <Engine/Components/Gameplay/CharacterControllerComponent.h>

namespace real_tournament
{
	using namespace willow;

	class RealTournamentPlayer final : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)

		//////////////////
		///   Fields   ///
	public:

		Handle<CameraComponent> view;
		Handle<CapsuleColliderComponent> capsule;
		Handle<CharacterControllerComponent> character_movement;

		///////////////////
		///   Methods   ///
	protected:

		void on_initialize() override;

		void on_spawn() override;

	private:

		void on_update(float dt);

		void on_move(Vec2 dir);

		void on_look(Vec2 dir);

		void on_jump();

		////////////////
		///   Data   ///
	private:

		/** The number of times this character has jumped since touching the ground. */
		uint32 _num_jumps = 0;
	};
}
