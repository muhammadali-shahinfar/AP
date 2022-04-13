#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#define pandas_visibled_path '$'
#define EMPTY_HOUSE '.'
#define BOMBO_HOUSE '*'
#define STONE_TILE '#'
#define UP 8
#define DOWN 2
#define LEFT 4
#define RIGHT 6
#define UP_BOARD_DIRECTION 0
#define DOWN_BOARD_DIRECTION 1
#define LEFT_BOARD_DIRECTION 2
#define RIGHT_BOARD_DIRECTION 3
#define VISIBLED 1
using namespace std;
int min_length_of_path(vector <string>, vector <int>, vector <vector <vector <bool> > >, int);
void change_loce_by_direction(int& horizon_location, int& vertical_location,int direction, vector <vector <vector <bool> > >& board_directions) {
	switch (direction)
	{
	case UP: 
		board_directions[horizon_location][vertical_location][UP_BOARD_DIRECTION] = VISIBLED;
		horizon_location--;
		break;
	case DOWN: 
		board_directions[horizon_location][vertical_location][DOWN_BOARD_DIRECTION] = VISIBLED;
		horizon_location++;
		break;
	case LEFT: 
		board_directions[horizon_location][vertical_location][LEFT_BOARD_DIRECTION] = VISIBLED;
		vertical_location--;
		break;
	case RIGHT:
		board_directions[horizon_location][vertical_location][RIGHT_BOARD_DIRECTION] = VISIBLED; 
		vertical_location++;
		break;
	default:
		break;
	}
}
void change_loce_by_direction_without_vision(int& horizon_location, int& vertical_location, int direction) {
	switch (direction)
	{
	case UP:
		horizon_location--;
		break;
	case DOWN:
		horizon_location++;
		break;
	case LEFT:
		vertical_location--;
		break;
	case RIGHT:
		vertical_location++;
		break;
	default:
		break;
	}
}
bool is_tile_empty(vector <string> board,int horizon_location,int vertical_location,int direction, vector <vector <vector <bool> > >& board_directions) {
	if (horizon_location == board.size() - 1 && direction == DOWN) return 0;
	if (horizon_location == 0 && direction == UP) return 0;
	if (vertical_location == board[0].length() - 1 && direction == RIGHT) return 0;
	if (vertical_location == 0 && direction == LEFT) return 0;
	change_loce_by_direction_without_vision(horizon_location, vertical_location, direction);
	if (board[horizon_location][vertical_location] == EMPTY_HOUSE) return 1;
	else return 0;
}
bool is_bambo(vector <string> board, int horizon_location, int vertical_location, int direction, vector <vector <vector <bool> > >& board_directions) {
	if (horizon_location == board.size() - 1 && direction == DOWN) return 0;
	if (horizon_location == 0 && direction == UP) return 0;
	if (vertical_location == board[0].length() - 1 && direction == RIGHT) return 0;
	if (vertical_location == 0 && direction == LEFT) return 0;
	change_loce_by_direction_without_vision(horizon_location, vertical_location, direction);
	if (board[horizon_location][vertical_location] == BOMBO_HOUSE) return 1;
	else return 0;
}
bool is_visibled_tile(vector <string> board, vector <int> panda_location, int direction, vector <vector <vector <bool> > > board_directions) {
	if (panda_location[0] == board.size() - 1 && direction == DOWN) return 0;
	if (panda_location[0] == 0 && direction == UP) return 0;
	if (panda_location[1] == board[0].length() - 1 && direction == RIGHT) return 0;
	if (panda_location[1] == 0 && direction == LEFT) return 0;
	if (direction == DOWN && board_directions[panda_location[0]][panda_location[1]][DOWN_BOARD_DIRECTION] == 1) return 1;
	if (direction == UP && board_directions[panda_location[0]][panda_location[1]][UP_BOARD_DIRECTION] == 1) return 1;
	if (direction == LEFT && board_directions[panda_location[0]][panda_location[1]][LEFT_BOARD_DIRECTION] == 1) return 1;
	if (direction == RIGHT && board_directions[panda_location[0]][panda_location[1]][RIGHT_BOARD_DIRECTION] == 1) return 1;
	return 0;
}
int if_stone_or_wall_tile(vector <string> board, vector <int>& panda_location, int direction, vector <vector <vector <bool> > >& board_directions) {
	int min_path_length = board.size()*board[0].length() + 5;
	if (direction == UP && board_directions[panda_location[0]][panda_location[1]][UP_BOARD_DIRECTION] != VISIBLED) {
		board_directions[panda_location[0]][panda_location[1]][UP_BOARD_DIRECTION] = VISIBLED;
		min_path_length = min_length_of_path(board, panda_location, board_directions, LEFT) ;
		if(min_length_of_path(board,panda_location,board_directions,RIGHT) < min_path_length) min_path_length = min_length_of_path(board, panda_location, board_directions, RIGHT) ;
	}
	if (direction == DOWN && board_directions[panda_location[0]][panda_location[1]][DOWN_BOARD_DIRECTION] != VISIBLED) {
		board_directions[panda_location[0]][panda_location[1]][DOWN_BOARD_DIRECTION] = VISIBLED;
		min_path_length = min_length_of_path(board, panda_location, board_directions, LEFT) ;
		if (min_length_of_path(board, panda_location, board_directions, RIGHT) < min_path_length) min_path_length = min_length_of_path(board, panda_location, board_directions, RIGHT);
	}
	if (direction == LEFT && board_directions[panda_location[0]][panda_location[1]][LEFT_BOARD_DIRECTION] != VISIBLED) {
		board_directions[panda_location[0]][panda_location[1]][LEFT_BOARD_DIRECTION] = VISIBLED;
		min_path_length = min_length_of_path(board, panda_location, board_directions, UP) ;
		if (min_length_of_path(board, panda_location, board_directions, DOWN) < min_path_length) min_path_length = min_length_of_path(board, panda_location, board_directions, DOWN);
	}
	if (direction == RIGHT && board_directions[panda_location[0]][panda_location[1]][RIGHT_BOARD_DIRECTION] != VISIBLED) {
		board_directions[panda_location[0]][panda_location[1]][RIGHT_BOARD_DIRECTION] = VISIBLED;
		min_path_length = min_length_of_path(board, panda_location, board_directions, UP) ;
		if (min_length_of_path(board, panda_location, board_directions, DOWN) < min_path_length) min_path_length = min_length_of_path(board, panda_location, board_directions, DOWN) ;
	}
	return min_path_length;
}
int min_length_of_path(vector <string> board, vector <int> panda_location, vector <vector <vector <bool> > > board_directions,int direction) {
		int min_path_length;
		if (is_bambo(board, panda_location[0], panda_location[1], direction,board_directions)) {
			min_path_length = 0;
			return min_path_length;
		}
		if (is_visibled_tile(board, panda_location, direction, board_directions)) {
			min_path_length= board.size()*board[0].length() + 5;
			return min_path_length;
		}
		if (is_tile_empty(board, panda_location[0], panda_location[1], direction,board_directions)) {
			change_loce_by_direction(panda_location[0], panda_location[1], direction,board_directions);
			min_path_length = min_length_of_path(board, panda_location,board_directions, direction) + 1;
			return min_path_length;
		}
		min_path_length = if_stone_or_wall_tile(board, panda_location, direction, board_directions);
		return min_path_length;
}
//int min_length_of_path(vector <string> board, int panda_initialy_location[2],int direction) {
//	vector <string> board_tmp = board;
//	int panda_location[2] = { panda_initialy_location[0],panda_initialy_location[1] };
//	int min_path_length;
//	if (is_bambo(board_tmp, panda_location[0], panda_location[1], direction)) {
//		min_path_length = 0;
//		return min_path_length;
//	}
//	board_tmp[panda_location[0]][panda_location[1]] = pandas_visibled_path;
//	if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], direction)) {
//		change_loce_by_direction(panda_location[0], panda_location[1], direction);
//		min_path_length = min_length_of_path(board_tmp, panda_location, direction) + 1;
//		return min_path_length;
//	}
//	else if (is_visibled_tile(board_tmp, panda_location[0], panda_location[1], direction)) {
//		min_path_length = board.size()*board[0].length() +1;
//		return min_path_length;
//	}
//	else {
//		min_path_length ;
//		if (direction == UP) {
//			if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], LEFT) || is_bambo(board_tmp, panda_location[0], panda_location[1], LEFT)) if (min_path_length > min_length_of_path(board_tmp, panda_location, LEFT)) {
//				if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], LEFT)) change_loce_by_direction(panda_location[0], panda_location[1], LEFT);
//				min_path_length = min_length_of_path(board_tmp, panda_location, LEFT) + 1;
//			}
//			if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], RIGHT) || is_bambo(board_tmp, panda_location[0], panda_location[1], RIGHT)) if (min_path_length > min_length_of_path(board_tmp, panda_location, RIGHT)) {
//				if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], RIGHT)) change_loce_by_direction(panda_location[0], panda_location[1], RIGHT);
//				min_path_length = min_length_of_path(board_tmp, panda_location, RIGHT) + 1;
//			}
//		}
//		if (direction == DOWN) {
//			if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], LEFT) || is_bambo(board_tmp, panda_location[0], panda_location[1], LEFT)) if (min_path_length > min_length_of_path(board_tmp, panda_location, LEFT)) {
//				if(is_tile_empty(board_tmp, panda_location[0], panda_location[1], LEFT)) change_loce_by_direction(panda_location[0], panda_location[1], LEFT);
//				min_path_length = min_length_of_path(board_tmp, panda_location, LEFT) + 1;
//			}
//			if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], RIGHT) || is_bambo(board_tmp, panda_location[0], panda_location[1], RIGHT)) if (min_path_length > min_length_of_path(board_tmp, panda_location, RIGHT)) {
//				if(is_tile_empty(board_tmp, panda_location[0], panda_location[1], RIGHT)) change_loce_by_direction(panda_location[0], panda_location[1], RIGHT);
//				min_path_length = min_length_of_path(board_tmp, panda_location, RIGHT) + 1;
//			}
//		}
//		if (direction == LEFT) {
//			if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], UP) || is_bambo(board_tmp, panda_location[0], panda_location[1], UP)) if (min_path_length > min_length_of_path(board_tmp, panda_location, UP)) {
//				if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], UP))change_loce_by_direction(panda_location[0], panda_location[1], UP);
//				min_path_length = min_length_of_path(board_tmp, panda_location, UP) + 1;
//			}
//			if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], DOWN) || is_bambo(board_tmp, panda_location[0], panda_location[1], DOWN)) if (min_path_length > min_length_of_path(board_tmp, panda_location, DOWN)) {
//				if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], DOWN))change_loce_by_direction(panda_location[0], panda_location[1], DOWN);
//				min_path_length = min_length_of_path(board_tmp, panda_location, DOWN) + 1;
//			}
//		}
//		if (direction == RIGHT) {
//			if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], UP) || is_bambo(board_tmp, panda_location[0], panda_location[1], UP)) if (min_path_length > min_length_of_path(board_tmp, panda_location, UP)) {
//				if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], UP)) change_loce_by_direction(panda_location[0], panda_location[1], UP);
//				min_path_length = min_length_of_path(board_tmp, panda_location, UP) + 1;
//			}
//			if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], DOWN) || is_bambo(board_tmp, panda_location[0], panda_location[1], DOWN)) if (min_path_length > min_length_of_path(board_tmp, panda_location, DOWN)) {
//				if (is_tile_empty(board_tmp, panda_location[0], panda_location[1], DOWN))change_loce_by_direction(panda_location[0], panda_location[1], DOWN);
//				min_path_length = min_length_of_path(board_tmp, panda_location, DOWN) + 1;
//			}
//		}
//	}
//	return min_path_length;
//}
int main() {
	vector <string> board;
	vector <int> panda_location(2, 0);
	string board_horizon_tmp;
	int board_horizon_size = board.size(), board_vertical_size = board[0].size();
	vector <bool> is_board_direction(4, 0);
	vector <vector <bool> > board_vertical_direction(board_vertical_size, is_board_direction);
	vector <vector <vector <bool> > > board_direction(board_horizon_size, board_vertical_direction);
	while (cin >> board_horizon_tmp) {
		board.push_back(board_horizon_tmp);
	}
	int min_length_of_path_value = (board.size()+1)*(board[0].length() + 1);
	if (is_tile_empty(board, panda_location[0], panda_location[1], RIGHT,board_direction)) {
		min_length_of_path_value = min_length_of_path(board, panda_location,board_direction, RIGHT) +1;
	}
	if (is_tile_empty(board, panda_location[0], panda_location[1], DOWN,board_direction)) {
		if (min_length_of_path_value > min_length_of_path(board, panda_location,board_direction, DOWN)) {
			min_length_of_path_value = min_length_of_path(board, panda_location,board_direction, DOWN) +1;
		}
	}
	if (min_length_of_path_value > (board.size()) * (board[0].length())) min_length_of_path_value = 0;
	if (min_length_of_path_value != 0) cout << min_length_of_path_value;
	else cout << "NO path found" << endl ;
}