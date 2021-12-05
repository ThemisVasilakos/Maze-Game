#ifndef _MOVING_H
#define _MOVING_H

#include <ncurses.h>
#include <string>

class Moving{

	protected:
		//Vars for object coordinates and current window
		char c;
		WINDOW *win;
		int x,y;
	
	public:
		//Constructor
		Moving(WINDOW *win,char c,int x,int y);
		
		//Setters and getters
		void setX(int x);
		void setY(int y);
		int getX()const;	
		int getY()const;
		
		//Move object method
		virtual int move();
};
#endif