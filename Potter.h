#ifndef _POTTER_H
#define _POTTER_H

#include "Moving.h"

class Potter:public Moving{
	
	private:
		//An int that represents the direction that the player is about to move
		int choice;
	public:
		Potter(WINDOW *win,char c,int x,int y);
	
		int move();

};

#endif