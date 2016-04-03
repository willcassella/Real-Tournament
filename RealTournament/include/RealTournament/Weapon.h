// Weapon.h
#pragma once

#include <Core/Memory/Pointers/Weak.h>
#include <Engine/Entity.h>
#include <Engine/Components/StaticMeshComponent.h>

namespace RealTournament
{
	class Weapon : public Willow::Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Willow::Entity)

		//////////////////
		///   Fields   ///
	public:

		/** The model to use for the weapon. */
		Weak<Willow::StaticMeshComponent> Model;

		/** The ammount of ammo this weapon can contain. */
		uint32 MagazineSize = 32;

		/** The ammount of ammo currently loaded in this weapon. */
		uint32 Ammo = MagazineSize;
	};
}
