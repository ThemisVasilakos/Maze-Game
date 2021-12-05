#include "Potter.h"

Potter::Potter(WINDOW *win,char c,int x,int y):
	Moving(win,c,x,y)
{
	
}

int Potter::move(){
	
	//Enable keyboard control
	keypad(win,true);
	
	halfdelay(5);
	
	choice=wgetch(win);
	
	//Check for right arrow key
	if(choice==KEY_RIGHT){
		return choice;
		}
	
	//Check for left arrow key
	if(choice==KEY_LEFT){
		return choice;
	}
	
	//Check for up arrow key
	if(choice==KEY_UP){
		return choice;
	}
	
	//Check for down arrow key
	if(choice==KEY_DOWN){
		return choice;
	}
	
	//Check for ESC key
	if(choice==27){
		return choice;
	}
		
	return 0;
}
