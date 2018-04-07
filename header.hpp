#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#define BOARD_SIZE 19
#define REQUIRED_ROW 5

struct board_node {
    bool game_end;
    int left_tiles;
    int heuristic_score;
    char board_status[BOARD_SIZE][BOARD_SIZE];
    vector<bool> is_counted_row; 
    vector<bool> is_counted_col;
    pair<int, int> moved;


    board_node(int x): game_end(false) {
        game_end = false;
        left_tiles = BOARD_SIZE * BOARD_SIZE;
        memset (board_status, '_', sizeof(board_status));
        is_counted_row.assign(BOARD_SIZE, false); 
        is_counted_col.assign(BOARD_SIZE, false); 
    };
};

struct abp_node {
    int heuristic_score;
    pair<int, int> move;
    
    abp_node(int x): heuristic_score(0) {
        heuristic_score = 0;
    };
};
