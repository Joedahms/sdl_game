#ifndef CHARACTER_H
#define CHARACTER_H

enum character_id { PLAYER, NPC };

class Character 
{
	public:
		virtual void print() = 0;
		virtual ~Character() = default;

		void update_y_pos();
		void update_x_pos();

		int get_y_pos();
		int get_x_pos();

		void set_y_vel(int);
		void set_x_vel(int);

	private:
		// position
		int y_pos;
		int x_pos;
		
		// velocity
		int y_vel;
		int x_vel;
};

#endif
