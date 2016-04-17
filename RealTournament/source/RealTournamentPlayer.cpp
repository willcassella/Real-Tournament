// RealTournamentPlayer.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include "../include/RealTournament/RealTournamentPlayer.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::RealTournamentPlayer)
.Field("view", &RealTournamentPlayer::view)
.Field("capsule", &RealTournamentPlayer::capsule);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void RealTournamentPlayer::on_initialize()
	{
		this->Base::on_initialize();
		this->get_world().events.Bind("update", *this, &RealTournamentPlayer::on_update);
		this->get_world().events.Bind("move", *this, &RealTournamentPlayer::on_move);
		this->get_world().events.Bind("look", *this, &RealTournamentPlayer::on_look);
		this->get_world().events.Bind("jump", *this, &RealTournamentPlayer::on_jump);
	}

	void RealTournamentPlayer::on_spawn()
	{
		this->Base::on_spawn();

		// Set up the view
		this->set_physics_mode(PhysicsMode::Ghost);
		auto& view = this->attach<CameraComponent>();
		this->view = view;
		view.set_location({ 0, 1, 0 });

		// Set up the collider
		auto& capsule = this->connect<CapsuleColliderComponent>();
		this->capsule = capsule;
		capsule.set_height(1.3f);

		// Set up the character movement
		auto& characterMovement = this->connect<CharacterControllerComponent>();
		this->character_movement = characterMovement;
		characterMovement.set_collider(&capsule);
	}

	void RealTournamentPlayer::on_update(float dt)
	{
		auto characterMovement = this->get_world().get_object(this->character_movement);
		
		if (characterMovement->on_ground())
		{
			this->_num_jumps = 0;
		}
	}

	void RealTournamentPlayer::on_move(Vec2 dir)
	{
		Vec3 direction = Mat4::Rotate(this->get_world().get_object(this->view)->get_world_rotation()) * Vec3 { dir.X, 0, -dir.Y };
		this->get_world().get_object(this->character_movement)->walk(Vec2{ direction.X, direction.Z } / 5);
	}

	void RealTournamentPlayer::on_look(Vec2 dir)
	{
		auto view = get_world().get_object(this->view);
		view->rotate_global(Vec3::Up, dir.X);
		view->rotate(Vec3::Right, dir.Y);
	}

	void RealTournamentPlayer::on_jump()
	{
		if (this->_num_jumps < 2)
		{
			this->get_world().get_object(this->character_movement)->jump();
			this->_num_jumps += 1;
		}
	}
}
