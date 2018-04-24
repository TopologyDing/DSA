#pragma once
#include"d:\study\programming\CODE\C++\stack\stack\stack.h"
#include"d:\study\programming\CODE\C++\vector_self\vector_self\vector.h"

#define DEFAULT_LABY_SCALE 15
typedef enum{UNKNOWN,NORTH,SOUTH,WEST,EAST,NOWAY} Direction;
typedef enum{AVAILABLE,ROUTE,BACKTRACKED,WALL} Status;

Direction nextDirection(Direction cur_dir) {
	return Direction(cur_dir + 1);
}

struct room {
	int x, y;
	Status room_status;
	Direction in_room, out_room;
	//room() { x = 0; y = 0; room_status = WALL, in_room = out_room = UNKNOWN; };
	room(int xx, int yy, Status s, Direction in_r, Direction out_r) :x(xx), y(yy), room_status(s), in_room(in_r), out_room(out_r) {};
	
};

struct labyrinth {
	int n;
	stack<room*>path_info;
	room*** all_room_info;
	room* start_room;
	room* end_room;
	labyrinth(int scale = DEFAULT_LABY_SCALE) :n(scale) {
		all_room_info = new room**[n];
		for (int i = 0; i < n; i++) {
			all_room_info[i] = new room*[n];
			for (int j = 0; j < n; j++) {
				all_room_info[i][j] = new room(i, j, WALL, UNKNOWN, UNKNOWN);//必须使用new，若直接&room(i, j, WALL, UNKNOWN, UNKNOWN)则每次在同一内存处生成临时变量，地址相同被覆盖
				cout << all_room_info[i][j] << endl;
			}
		}

		for (int i = 1; i < n - 1; i++) {
			for (int j = 1; j < n - 1; j++) {
				if (rand() % 4) {
					all_room_info[i][j]->room_status = AVAILABLE;
				}
			}
		}

		start_room = all_room_info[rand() % (n - 2) + 1][rand() % (n - 2) + 1];
		end_room = all_room_info[rand() % (n - 2) + 1][rand() % (n - 2) + 1];
		start_room->room_status = AVAILABLE;
		end_room->room_status = AVAILABLE;
	}

	~labyrinth() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				delete all_room_info[i][j];
			}
			delete[] all_room_info[i];
		}
		delete[] all_room_info;
	}

	void labyrinth_print_original() {
		cout << "this is the maze before path search\n";
		cout << "----------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				(all_room_info[i][j]->room_status == AVAILABLE) ? (cout << "   ") : (cout << " * ");
			}
			cout << endl;
		}
	}

	void labyrinth_print_after_search() {
		cout << "this is the maze after path search\n";
		cout << "----------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (((i == start_room->x) && (j == start_room->y)) || ((i == end_room->x) && (j == end_room->y))) {
					cout << " O ";
				}
				else {
					if (all_room_info[i][j]->room_status == AVAILABLE) {
						cout << "   ";
					}
					else if (all_room_info[i][j]->room_status == ROUTE) {
						if ((all_room_info[i][j]->out_room == WEST) || (all_room_info[i][j]->out_room == EAST))
							cout<<" I ";
						if ((all_room_info[i][j]->out_room == SOUTH) || (all_room_info[i][j]->out_room == NORTH))
							cout << " - ";
					}
					else if (all_room_info[i][j]->room_status == WALL) {
						cout << " * ";
					}
					else {
						cout << "   ";
					}
				}
			}
			cout << endl;
		}
		
	}

	bool labyrinth_search() {//改进搜索方法提高效率？
		path_info.push(start_room);
		start_room->room_status = ROUTE;
		do {
			room* cur_room = path_info.top();
			if (cur_room == end_room)return true;
			while (NOWAY > (cur_room->out_room = nextDirection(cur_room->out_room)))
				if (neighbor(cur_room)->room_status == AVAILABLE) break;
			if (NOWAY <= cur_room->out_room) {
				cur_room->room_status = BACKTRACKED; path_info.pop();
			}
			else {
				path_info.push(grow(cur_room));
				cur_room = neighbor(cur_room);
				cur_room->out_room = UNKNOWN;
				cur_room->room_status = ROUTE;
			}
		} while (!path_info.empty());
		return false;
	}

	room* neighbor(room* r) {
		switch (r->out_room) {
		case NORTH:
			return all_room_info[r->x][r->y + 1];
		case SOUTH:
			return all_room_info[r->x][r->y - 1];
		case WEST:
			return all_room_info[r->x - 1][r->y];
		case EAST:
			return all_room_info[r->x + 1][r->y];
		default:
			cout << "wrong direction to go out for current room!" << endl;
			exit(-1);
		}
	}

	room* grow(room* r) {
		switch (r->out_room) {
		case NORTH:
			all_room_info[r->x][r->y + 1]->out_room = SOUTH;
			return all_room_info[r->x][r->y + 1];
			break;
		case SOUTH:
			all_room_info[r->x][r->y - 1]->out_room = NORTH;
			return all_room_info[r->x][r->y - 1];
			break;
		case WEST:
			all_room_info[r->x - 1][r->y]->out_room = EAST;
			return all_room_info[r->x - 1][r->y];
			break;
		case EAST:
			all_room_info[r->x + 1][r->y]->out_room = WEST;
			return all_room_info[r->x + 1][r->y];
			break;
		default:
			cout << "wrong direction to go out for current room!" << endl;
			exit(-1);
		}
	}

};