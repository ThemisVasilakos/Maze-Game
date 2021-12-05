#include "Engine.h"

int main(int argc,char *argv[]){
	
	//Constructing and running the game and try catch for map and score file
	try{
		
		if(argc!=3){
			throw 0;
		}
		
		Engine e(argv[1],argv[2]);
		e.start();
	}catch(int e){
		if(e==0){
			cout<<"Wrong arguments given"<<endl;
		}
		if(e==1){
			cout<<"Wrong map file!!"<<endl;
		}
		if(e==2){
			cout<<"Wrong score file!!"<<endl;
		}
	}
	
	return 0;
}
