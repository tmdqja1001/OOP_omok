#include "board.h"


int main(void){
	int end = 1;
	while(end){
		BOARD game = BOARD();
		game.get_name();
		game.get_first();
		game.put_stone();
		game.print();
		while(game.get_stone() == true){
			game.print();
		}
		game.print();
		if(game.end_phase() == true) end = 0;
	}
	return 0;	
}

