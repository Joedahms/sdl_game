#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>

#include "character.h"

// factory for character objects
class CharacterFactory
{
	public:
		virtual std::unique_ptr<Character> create(character_id id);
		//virtual ~CharacterFactory() = default;
};

#endif
