// RealTournamentSystem.cpp

#include <Core/Umbrellas/Reflection.h>
#include <Engine/World.h>
#include "../include/RealTournament/RealTournamentSystem.h"
#include "../include/RealTournament/Player.h"
#include "../include/RealTournament/SpawnPad.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::RealTournamentSystem);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void RealTournamentSystem::on_player_spawn(Player& player)
	{
		// Determine which player should be spawned
		int playerID;

		// If neither player is spawned
		if (_player_one_object.is_null() && _player_two_object.is_null())
		{
			switch (_last_killed_player)
			{
			// Beginning of the game, no player has been killed (spawn player 1 first)
			case 0:
				playerID = 1;
				_player_one_object = player;
				player.get_world().get_object(player.view)->orientation = CameraComponent::SplitScreenOrientation::Top;
				break;

			// Player one was the last one killed, so player two should spawn first (they've been dead for longer)
			case 1:
				playerID = 2;
				_player_two_object = player;
				player.get_world().get_object(player.view)->orientation = CameraComponent::SplitScreenOrientation::Bottom;
				break;

			// Player two was the last one killed, similar to above
			case 2:
				playerID = 1;
				_player_one_object = player;
				player.get_world().get_object(player.view)->orientation = CameraComponent::SplitScreenOrientation::Top;
				break;
			}
		}
		// If player one hasn't spawned yet
		else if (_player_one_object.is_null())
		{
			playerID = 1;
			_player_one_object = player;
			player.get_world().get_object(player.view)->orientation = CameraComponent::SplitScreenOrientation::Top;
		}
		// Player two hasn't spawned yet
		else
		{
			playerID = 2;
			_player_two_object = player;
			player.get_world().get_object(player.view)->orientation = CameraComponent::SplitScreenOrientation::Bottom;
		}

		// Bind events for the player
		player.get_world().bind_event("update", player, &Player::on_update);
		player.get_world().bind_event(Format("move@", playerID), player, &Player::on_move);
		player.get_world().bind_event(Format("look@", playerID), player, &Player::on_look);
		player.get_world().bind_event(Format("jump@", playerID), player, &Player::on_jump);
		player.get_world().bind_event(Format("fire@", playerID), player, &Player::on_fire);
	}

	void RealTournamentSystem::on_player_death(Player& player)
	{
		Handle<Player> handle = player;
		if (_player_one_object == handle)
		{
			_last_killed_player = 1;
			_player_one_object = nullptr;
		}
		else
		{
			_last_killed_player = 2;
			_player_two_object = nullptr;
		}

		// Pick a spawn pad for the player to spawn at
		auto spawnPads = player.get_world().enumerate_objects<SpawnPad>();

		// OK, this is pretty awful, I'll admit
		while (true)
		{
			auto spawnPad = spawnPads[rand() % spawnPads.Size()];
			
			// If the spawnpad spawns players AND it's not currently spawning a player
			if (spawnPad->spawn_timer == 0 && *spawnPad->spawn_type.get_class() == TypeOf<Player>())
			{
				spawnPad->spawn_timer = 3;
				break;
			}
		}
	}
}
