// JumpBoots.h
#pragma once

#include <Engine/Components/Physics/SphereColliderComponent.h>
#include "Pickup.h"

namespace real_tournament
{
	class JumpBoots final : public Pickup
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Pickup)

		///////////////////
		///   Methods   ///
	protected:

		void on_spawn() override;

		void on_pickup(Player& player) override;

	private:

		void on_update(float dt);

		////////////////
		///   Data   ///
	private:

		Handle<StaticMeshComponent> _mesh;
		Handle<SphereColliderComponent> _collider;
		Handle<CharacterControllerComponent> _character_movement;
		float _time_left = 20.f;
	};
}
