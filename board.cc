#include "board.h"


BOARD::BOARD(void)
{
	n_black = 0;
	n_white = 0;
	for(int i=0;i<19;i++){
		for(int j=0; j<19; j++){
			board_arr[i][j] = 0;
		}
	}
	p1 = "Player1";
	p2 = "Player2";
	end_flag = 0;
	x = 9;
	y = 9;
	p = 1;
}

void BOARD::print(void)
{
	int buff_flag = 0;
	for(int i=0;i<19;i++){
		buff_flag = 0;
		for(int j=0;j<19;j++){
			if(board_arr[i][j]==0){
				if(buff_flag == 0) std::cout << ' ';
				if(i==0 && j==0) std::cout << "┌";
				else if(i==0 && j==18) std::cout << "┐";
				else if(i==0) std::cout << "┬";
				else if(i==18 && j==0) std::cout <<"└";
				else if(i==18 && j==18) std::cout<< "┘";
				else if(j==0) std::cout << "├";
				else if(i==18) std::cout << "┴";
				else if(j==18) std::cout << "┤";
				else std::cout << "┼";
				buff_flag = 0;
			}
			else if(board_arr[i][j]==1){
				if(buff_flag == 0) std::cout << ' ';
				std::cout << "○";
				buff_flag = 1;
			}
			else if(board_arr[i][j]==2){
				if(buff_flag == 0) std::cout << ' ';
				std::cout << "●";
				buff_flag = 1;
			}
		}
		std::cout << '\n';
	}
	std::cout << " The number of black stones : " << n_black << '\n';
        std::cout << " The number of white stones : " << n_white << '\n';	
}

void BOARD::get_name(void)
{
	std::cout << " Please let me know the black player's name : ";
	std::cin >> p1;
	std::cout << " Please let me know the white player's name : ";
	std::cin >> p2;
}

void BOARD::get_first(void)
{
	std::cout << "Who's going first black or white?? (B/W) : ";
	char buf;
	std::cin >> buf;
	if(buf == 'B') p = 1;
	else if(buf == 'W') p = 2;
	else return get_first();
}

bool BOARD::get_stone()
{
	int a, b;
	if(p==1){
		std::cout << " Black player : " << p1 << "'s input (row, column): ";
		std::cin >> a;
		if(a==20000){ end_flag = 3; return false;}
		std::cin >> b;
		if(b==20000){ end_flag = 3; return false;}
		x = a-1;
		y = b-1;
		if(check_pos() == false) return get_stone();
		if(check_ssangsam() == false) return get_stone();
		put_stone();
		if(judge() == false) return false;
		return true;
	}
	else{
		std::cout << " White player : " <<  p2 << "'s input (row, column): ";
		std::cin >> a;
		if(a==20000){ end_flag = 3; return false;}
		std::cin >> b;
		if(b==20000){ end_flag = 3; return false;}
		x = a-1;
		y = b-1;
		if(check_pos() == false) return get_stone();
		if(check_ssangsam() == false) return get_stone();
		put_stone();
		if(judge() == false) return false;
		return true;
	}
}

void BOARD::put_stone()
{
	if(p==1){
		board_arr[x][y] = 1;
		p = 2;
		n_black++;
	}
	else if(p==2){
		board_arr[x][y] = 2;
		p = 1;
		n_white++;
	}
	return;
}

bool BOARD::check_pos()
{
	if(x<0 || x >18 || y<0 || y > 18){
		std::cout << " Out of range !!! " << '\n';
		return false;
	}
	else if(board_arr[x][y]==0) return true;
	else{
		std::cout << " Stone is already exist !!! " << '\n';
		return false;
	}
}

bool BOARD::check_ssangsam()
{
	int pos_x = x;
	int pos_y = y;
	int dir_x[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
	int dir_y[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int dir_f[8] = {0,}; // 1 for blank 1, 2 for blank 2
	int cnt = 0;
	for(int i=0; i<8; i++){
		pos_x = x + dir_x[i];
		pos_y = y + dir_y[i];
		if(pos_x<0 || pos_x>18) continue;
		if(pos_y<0 || pos_y>18) continue;
		if(board_arr[pos_x][pos_y] == p){
			pos_x += dir_x[i];
			pos_y += dir_y[i];
			if(pos_x<0 || pos_x>18) continue;
			if(pos_y<0 || pos_y>18) continue;
			if(board_arr[pos_x][pos_y] == p){
				pos_x += dir_x[i];
				pos_y += dir_y[i];
				if(pos_x<0 || pos_x>18)	continue;
				if(pos_y<0 || pos_y>18)	continue;
				if(board_arr[pos_x][pos_y] == 0){
					dir_f[i] = 2;
					continue;
				}
			}
			else if(board_arr[pos_x][pos_y] == 0){
				dir_f[i] = 1;
				continue;
			}
		}
	}
	for(int i=0; i<4; i++){
		if((dir_f[i] + dir_f[i+4]) == 2) cnt++;
	}
	if(cnt >= 2){
		std::cout << " Prohibited by ssangsam rule!!! " << '\n';
		return false;
	}
	else return true;
}

bool BOARD::judge()
{
	int sum = n_black;
	sum += n_white;
	
	if(sum == 361){
		end_flag = 3;
		return false;
	}

	int pos_x;
	int pos_y;
	int dir_x[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
	int dir_y[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int dir_f[8] = {0};
	for(int i=0; i<8; i++){
		int flag = 1;
		pos_x = x;
		pos_y = y;
		while(flag){
			pos_x += dir_x[i];
			pos_y += dir_y[i];
			if(pos_x < 0 || pos_x > 18) flag = 0;
			else if(pos_y < 0 || pos_y > 18) flag = 0;
			else if(board_arr[pos_x][pos_y] != board_arr[x][y]) flag = 0;
			else{
				dir_f[i] += 1;
			}
		}
	}
	for(int i=0; i<4; i++){
		//std::cout << dir_f[i] << ' ' << dir_f[i+4] << '\n';
		if((dir_f[i] + dir_f[i+4]) == 4){
			end_flag = board_arr[x][y];
			return false;
		}
	}
	return true;
}


bool BOARD::end_phase(void)
{
	if(end_flag == 1){
		std::cout << ' ' << p1 << " (black) wins the game !!!" << '\n';
	}
	else if(end_flag == 2){
		std::cout << ' ' << p2 << " (white) wins the game !!!" << '\n';
	}
	else if(end_flag == 3){
		std::cout << " Game ended with draw !!!" << '\n';
	}
	else{
		std::cout << " Error occurs !!!" << '\n';
	}

	char buf = ' ';
	std::cout << " Do you want to play it agina ??? (Y/N) ";
	while(1){
		std::cin >> buf;
		if(buf == 'Y') return false;
		else if(buf == 'N') return true;
	}
	
}


