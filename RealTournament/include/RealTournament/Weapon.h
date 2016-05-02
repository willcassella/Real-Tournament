// Weapon.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/SubClassOf.h>
#include <Engine/Handle.h>
#include <Engine/Entity.h>
#include <Engine/Components/Rendering/StaticMeshComponent.h>
#include <Engine/Components/Rendering/AnimationComponent.h>

namespace real_tournament
{
	using namespace willow;

	class Weapon : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)

		//////////////////
		///   Fields   ///
	public:

		/** The model to use for the weapon. */
		Handle<StaticMeshComponent> model;

		/** Animation to use for the weapon. */
		Handle<AnimationComponent> animation;

		/** The type of projectile to fire. */
		SubClassOf<Entity> projectile;

		/** The ammount of ammo this weapon can contain. */
		uint32 magazine_size = 32;

		/** The ammount of ammo currently loaded in this weapon. */
		uint32 ammo = magazine_size;

		//////////////////
		///   Fields   ///
	public:

		virtual void fire() = 0;
	};
}
