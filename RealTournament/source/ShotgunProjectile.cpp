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

	void ShotgunProjectile::on_spawn()
	{
		this->Base::on_spawn();

		this->set_physics_mode(PhysicsMode::Ghost);
		auto& sphere = this->connect<SphereColliderComponent>();
		sphere.set_radius(0.5f);
		//auto& model = this->connect<StaticMeshComponent>();
		//model.mesh = "ExportedContent/Bullet.wmesh"_p;
		//model.instance_params["diffuse"] = ResourceHandle<Texture>{ "Content/Textures/Weapons/MetalBare0154_1_L.jpg"_p };
	}

	void ShotgunProjectile::on_collision(Entity& collidee)
	{
		this->Base::on_collision(collidee);
	}
}
