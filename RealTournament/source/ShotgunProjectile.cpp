// ShotgunProjectile.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/RealTournament/ShotgunProjectile.h"
#include <Engine/World.h>
#include <Engine/Components/Physics/SphereColliderComponent.h>
#include <Engine/Components/Rendering/StaticMeshComponent.h>

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::ShotgunProjectile);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void ShotgunProjectile::on_collision(Entity& entity, const CollisionData& info)
	{
		this->Base::on_collision(entity, info);

		// DO NOT reflect on collisions with other projectiles, that just gets too crazy
		if (!IsCastableTo<Projectile>(entity))
		{
			this->velocity = velocity.Reflect(info.normal);
			_bounces++;

			if (_bounces > 10)
			{
				this->destroy();
			}
		}
	}

	void ShotgunProjectile::on_spawn()
	{
		this->Base::on_spawn();

		this->set_physics_mode(PhysicsMode::Ghost);
		auto& sphere = this->connect<SphereColliderComponent>();
		sphere.set_radius(0.3f);
		auto& model = this->connect<StaticMeshComponent>();
		model.mesh = "ExportedContent/Meshes/Bullet.wmesh"_p;
		model.instance_params["diffuse"] = ResourceHandle<Texture>{ "Content/Textures/Props/Orange.psd"_p };
	}
}
