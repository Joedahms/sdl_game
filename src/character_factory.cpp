#include <memory>

#include "character.h"
#include "character_factory.h"
#include "player.h"
#include "npc.h"

// factory for character objects
std::unique_ptr<Character> CharacterFactory::create(character_id id)	
{
	if (character_id::PLAYER == id)			// make player
	{
		return std::make_unique<Player>();
	}
	if (character_id::NPC == id)			// make npc
	{
		return std::make_unique<Npc>();
	}
	return nullptr;
}
