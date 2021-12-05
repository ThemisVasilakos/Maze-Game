#include "Moving.h"

Moving::Moving(WINDOW *win,char c,int x,int y){
	this->c=c;
	this->x=x;
	this->y=y;
	this->win=win;
}

void Moving::setX(int x){
	this->x=x;
}

void Moving::setY(int y){
	this->y=y;
}

int Moving::getX()const{
	return x;
}

int Moving::getY()const{
	return y;
}

int Moving::move(){
	return 0;
}