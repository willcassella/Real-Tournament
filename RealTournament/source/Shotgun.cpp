// Shotgun.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include "../include/RealTournament/Shotgun.h"
#include "../include/RealTournament/ShotgunProjectile.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::Shotgun);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void Shotgun::fire()
	{
		for (auto i = 0; i < 8; ++i)
		{
			// Spawn a projectile
			auto& projectile = this->get_world().spawn<ShotgunProjectile>();
			
			// Calculate gun vector
			auto vector = Mat4::Rotate(this->get_world_rotation()) * Vec3 { 0, 0, -1 };
			projectile.set_world_location(this->get_world_location() + vector * 2);
			
			// Give it a semi-random velocity
			vector = Mat4::Rotate(Quat{ Vec3::Right, degrees(float(rand() % 20)) }) * vector;
			vector = Mat4::Rotate(Quat{ Vec3::Up, degrees(float(rand() % 20)) }) * vector;
			projectile.velocity = vector;
		}
	}

	void Shotgun::on_spawn()
	{
		auto& model = this->connect<StaticMeshComponent>();
		this->model = model;

		model.mesh = "ExportedContent/Meshes/Shotgun.wmesh"_p;
		model.instance_params["diffuse"] = ResourceHandle<Texture>{ "Content/Textures/Weapons/shotgun_final.png"_p };
	}
}
