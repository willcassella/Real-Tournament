// RealTournamentSystem.h
#pragma once

#include <Engine/System.h>

namespace real_tournament
{
	using namespace willow;
	
	class RealTournamentSystem final : public System
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(System)

		///////////////////
		///   Methods   ///
	public:

		/** Handles when a player is spawned into the world. */
		void on_player_spawn(class Player& player);

		/** Handles when a player is  */
		void on_player_death(class Player& player);

		////////////////
		///   Data   ///
	private:

		int _last_killed_player = 0;
		Handle<class Player> _player_one_object;
		Handle<class Player> _player_two_object;
	};
}
