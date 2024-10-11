#ifndef CAMERA_H 
#define CAMERA_H

#include <SDL2/SDL.h>
#include <vector>

class Camera {
	public:
		Camera(int, int, int);

		int getVisibleXTiles();
		int getVisibleYTiles();

		// position
		int x_pos = 0;
		int y_pos = 0;

		// velocity
		int x_vel = 0;
		int y_vel = 0;
		

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
		void zoomIn(int);
		void zoomOut(int);

		// move camera and check boundries
		void update(int, int); 

		void zoomChange(int);

		SDL_Rect & getDestinationRect(int, int);

		std::vector<std::vector<SDL_Rect>> destinationRect;	// needs to be dependent on screen size
	private:
		// direction
		int x_dir = 0;
		int y_dir = 0;

		int screenHeight;
		int screenWidth;
		
		// tiles in view
		int visibleXTiles;
		int visibleYTiles;

		//dest rect
};

#endif
