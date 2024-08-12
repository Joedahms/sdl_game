#ifndef CAMERA_H 
#define CAMERA_H

class Camera
{
	public:
		Camera();
		~Camera();

		// position
		int x_pos = 0;
		int y_pos = 0;

		// velocity
		int x_vel = 0;
		int y_vel = 0;
		
		// tiles in view
		int visible_x_tiles;
		int visible_y_tiles;

		// get direction
		int get_x_dir();
		int get_y_dir();

		// modify x direction
		void neg_x_dir();
		void pos_x_dir();

		// modify y direction
		void neg_y_dir();
		void pos_y_dir();

		void zero_dir();

		// modify x & y positions so zoom to center of camera
		void zoom_in();
		void zoom_out();

		// move camera and check boundries
		void update(int, int); 

	private:
		// direction
		int x_dir = 0;
		int y_dir = 0;
};

#endif
