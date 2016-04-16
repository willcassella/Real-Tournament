// Weapon.h
#pragma once

#include <Engine/Handle.h>
#include <Engine/Entity.h>
#include <Engine/Components/Rendering/StaticMeshComponent.h>

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

		/** The ammount of ammo this weapon can contain. */
		uint32 magazine_size = 32;

		/** The ammount of ammo currently loaded in this weapon. */
		uint32 ammo = magazine_size;
	};
}
