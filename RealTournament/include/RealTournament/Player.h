// Player.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Handle.h>
#include <Engine/Components/Rendering/CameraComponent.h>
#include <Engine/Components/Physics/CapsuleColliderComponent.h>
#include <Engine/Components/Gameplay/CharacterControllerComponent.h>
#include "Weapon.h"

namespace real_tournament
{
	using namespace willow;

	class Player final : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)

		//////////////////
		///   Fields   ///
	public:

		/** The currently equipped weapon. */
		Handle<Weapon> weapon;

		/** The view object. */
		Handle<CameraComponent> view;

		/** The capsule collider. */
		Handle<CapsuleColliderComponent> capsule;
		
		/** The character movement component. */
		Handle<CharacterControllerComponent> character_movement;

		/** The amount of health this character has. */
		float health = 100;

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

		void on_fire();

		////////////////
		///   Data   ///
	private:

		/** The number of times this character has jumped since touching the ground. */
		uint32 _num_jumps = 0;
	};
}
