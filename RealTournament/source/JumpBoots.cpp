// JumpBoots.cpp

#include <Engine/World.h>
#include "../include/RealTournament/JumpBoots.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::JumpBoots);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void JumpBoots::on_spawn()
	{
		this->Base::on_spawn();
		
		// Set up mesh
		auto& mesh = this->connect<StaticMeshComponent>();
		mesh.mesh = "ExportedContent/Meshes/JumpBoots.wmesh"_p;
		mesh.instance_params["diffuse"] = ResourceHandle<Texture>("Content/Textures/Props/JumpBoots.jpg"_p);
		_mesh = mesh;
		
		// Set up collider
		this->set_physics_mode(PhysicsMode::Ghost);
		auto& collider = this->connect<SphereColliderComponent>();
		collider.set_radius(0.5f);
		_collider = collider;
	}

	void JumpBoots::on_pickup(Player& player)
	{
		this->get_world().bind_event("update", *this, &JumpBoots::on_update);
		
		auto* characterMovement = player.character_movement.get_object(this->get_world());
		characterMovement->set_jump_speed(30);
		this->_character_movement = *characterMovement;

		_mesh.get_object(this->get_world())->destroy();
		_collider.get_object(this->get_world())->destroy();
		this->set_physics_mode(PhysicsMode::Transient);
	}

	void JumpBoots::on_update(float dt)
	{
		_time_left -= dt;

		if (_time_left < 0)
		{
			auto* characterMovement =_character_movement.get_object(this->get_world());

			if (characterMovement)
			{
				characterMovement->set_jump_speed(10.f);
			}

			this->destroy();
		}
	}
}
