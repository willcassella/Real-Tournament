// Helmet.cpp

#include <Engine/World.h>
#include <Engine/Components/Physics/SphereColliderComponent.h>
#include "../include/RealTournament/Helmet.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::Helmet);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void Helmet::drop()
	{
		// Set this up as a rigid body
		this->_dropped = true;
		this->set_physics_mode(PhysicsMode::Dynamic);
		this->get_world().bind_event("update", *this, &Helmet::post_drop_update);

		// Remove this object from the stack of helmets
		if (this->previous_helmet.is_null())
		{
			// First helmet, so the player is no longer wearing a helmet
			static_cast<Player*>(this->get_parent())->first_helmet = nullptr;
		}
		else
		{
			auto* prevHelmet = previous_helmet.get_object(this->get_world());
			prevHelmet->next_helmet = nullptr;
		}

		// If we have a helmet above us
		if (!this->next_helmet.is_null())
		{
			// Drop it
			next_helmet.get_object(this->get_world())->drop();
		}

		this->set_parent(nullptr, SP_Keep_World_Offset);
	}

	void Helmet::wobble(Vec2 dir)
	{
		this->set_rotation(Quat{ Vec3{ dir.Y, 0, dir.X}.Normalize() , degrees(dir.Length()) });

		if (!next_helmet.is_null())
		{
			next_helmet.get_object(this->get_world())->wobble(dir);
		}
	}

	void Helmet::on_collision(Entity& entity, const CollisionData& data)
	{
		this->Base::on_collision(entity, data);

		if (spawn_pad.is_null() && !_dropped && !IsCastableTo<Player>(entity) && !IsCastableTo<Pickup>(entity))
		{
			this->drop();
		}
	}

	void Helmet::on_spawn()
	{
		this->Base::on_spawn();

		this->set_physics_mode(PhysicsMode::Ghost);
		auto& mesh = this->connect<StaticMeshComponent>();
		mesh.mesh = "ExportedContent/Meshes/Helmet.wmesh"_p;
		mesh.instance_params["diffuse"] = ResourceHandle<Texture>("Content/Textures/Props/helmet_final.png"_p);

		auto& sphere = this->connect<SphereColliderComponent>();
		sphere.set_radius(0.35f);
	}

	void Helmet::on_pickup(Player& player)
	{
		constexpr auto Helmet_Step = 0.25f;
		constexpr auto Helmet_Start = 1.25f;

		auto top = player.get_top_helmet();

		if (!top)
		{
			this->set_parent(&player, SP_Move_To_Origin);
			this->set_location(Vec3{ 0, Helmet_Start, 0 });
			player.first_helmet = *this;
		}
		else
		{
			this->set_parent(top, SP_Move_To_Origin);
			this->set_location(Vec3{ 0, Helmet_Step, 0 });
			top->next_helmet = *this;
			this->previous_helmet = *top;
		}
	}

	void Helmet::post_drop_update(float dt)
	{
		_life -= dt;

		if (_life < 0)
		{
			this->destroy();
		}
	}
}
