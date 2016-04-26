// Player.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include "../include/RealTournament/Player.h"
#include "../include/RealTournament/Shotgun.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::Player)
.Field("health", &Player::health)
.Field("view", &Player::view)
.Field("capsule", &Player::capsule);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void Player::on_initialize()
	{
		this->Base::on_initialize();
		this->get_world().bind_event("update", *this, &Player::on_update);
		this->get_world().bind_event("move", *this, &Player::on_move);
		this->get_world().bind_event("look", *this, &Player::on_look);
		this->get_world().bind_event("jump", *this, &Player::on_jump);
		this->get_world().bind_event("fire", *this, &Player::on_fire);
	}

	void Player::on_spawn()
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
		capsule.set_radius(0.5f);

		// Set up the character movement
		auto& characterMovement = this->connect<CharacterControllerComponent>();
		this->character_movement = characterMovement;
		characterMovement.set_collider(&capsule);

		// Set up weapon
		auto& weapon = view.get_entity().attach<Shotgun>();
		this->weapon = weapon;
		weapon.set_scale({ 0.2f, 0.2f, 0.2f });
		weapon.set_location({ 0.7f, -0.5, -0.45f });
	}

	void Player::on_update(float dt)
	{
		auto characterMovement = this->get_world().get_object(this->character_movement);
		
		if (characterMovement->on_ground())
		{
			this->_num_jumps = 0;
		}
	}

	void Player::on_move(Vec2 dir)
	{
		Vec3 direction = Mat4::Rotate(this->get_world().get_object(this->view)->get_world_rotation()) * Vec3{ dir.X, 0, -dir.Y };
		this->get_world().get_object(this->character_movement)->walk(Vec2{ direction.X, direction.Z } / 5);
	}

	void Player::on_look(Vec2 dir)
	{
		auto view = get_world().get_object(this->view);
		view->rotate_global(Vec3::Up, dir.X);
		view->rotate(Vec3::Right, dir.Y);
	}

	void Player::on_jump()
	{
		if (this->_num_jumps < 2)
		{
			this->get_world().get_object(this->character_movement)->jump();
			this->_num_jumps += 1;
		}
	}

	void Player::on_fire()
	{
		auto weapon = this->get_world().get_object(this->weapon);
		weapon->ammo--;
		weapon->fire();
	}
}
