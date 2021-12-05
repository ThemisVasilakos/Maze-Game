#ifndef _GNOME_H
#define _GNOME_H

#include "Moving.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;

class Gnome:public Moving{

	private:
		
	public:
		Gnome(WINDOW *win,char c,int x,int y);
		
		int move(int potter_y,int potter_x,const vector<string> &map);
};

#endif