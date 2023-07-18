#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

class BOARD {
	private:
		int board_arr[19][19];
		int n_black;
		int n_white;
		int end_flag; // 0 keep going, 1 black win, 2 white win, 3 draw
		std::string p1;
		std::string p2;
		int x;
		int y;
		int p;
	public:
		BOARD();
		void print();
		void get_name();
	 	void get_first();
		bool get_stone();
		void put_stone();
		bool check_pos();
		bool check_ssangsam();
		bool judge();
		bool end_phase();
};

#endif
