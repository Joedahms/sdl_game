#ifndef NPC_H
#define NPC_H

#include "character.h"

class Npc : public Character
{
	public:
		Npc();
		~Npc();
		void print();
};

#endif
