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

	void Shotgun::on_spawn()
	{
		auto& model = this->connect<StaticMeshComponent>();
		this->model = model;

		model.mesh = "ExportedContent/Meshes/Shotgun.wmesh"_p;
		model.instance_params["diffuse"] = ResourceHandle<Texture>{ "Content/Textures/Weapons/MetalBare0154_1_L.jpg"_p };
	}

	void Shotgun::fire()
	{
		auto& projectile = this->get_world().spawn<ShotgunProjectile>();
		projectile.set_world_location(this->get_world_location());
	}
}
