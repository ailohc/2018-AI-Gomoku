#include "header.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


board_node heuristic_func(board_node current_node, char current_player) {
    current_node.heuristic_score = 0;
    for (int i = 0 ; i < BOARD_SIZE; i++) {
            for (int j = 0;  j < BOARD_SIZE; j++) {
                    int temp_row = j;
                    int temp_column = i;
                    if (current_node.board_status[temp_row][temp_column] != '_') {
                        pair<int, int> cur_check_tile;
                        cur_check_tile.first = temp_row;
                        cur_check_tile.second = temp_column;
                        if (current_node.board_status[temp_row][temp_column] == current_player) { //현재 플레이어 세로줄 체크
                            int matched_row = 1;
                            int vert_starting_point = cur_check_tile.first;
                            int vert_ending_point = cur_check_tile.first;
                            if (temp_row < (BOARD_SIZE - 1)) {
                                temp_row++;
                                while (current_node.board_status[temp_row][temp_column] == current_player) {
                                    cur_check_tile.first = temp_row;
                                    cur_check_tile.second = temp_column;
                                    vert_ending_point = cur_check_tile.first;
                                    matched_row++;
                                    if (temp_row < (BOARD_SIZE - 1)) {
                                        temp_row++;
                                    }
                                    else
                                        break;
                                }
                            }
                            if (matched_row == REQUIRED_ROW) { //승리했을 때 점수 부여
                                current_node.heuristic_score = 181818;
                                current_node.game_end = true;
                                return current_node;
                            }
                            else if (matched_row == (REQUIRED_ROW-1)) { //4칸 맞추었을 때
                                if ((vert_starting_point-1) >=0) {
                                    if (current_node.board_status[vert_starting_point-1][temp_column] == '_')
                                        current_node.heuristic_score += 2018;
                                }
                                if ((vert_ending_point+1) < BOARD_SIZE) {
                                    if (current_node.board_status[vert_ending_point+1][temp_column] == '_')
                                        current_node.heuristic_score += 2018;
                                }
                            }
                            else if (matched_row == (REQUIRED_ROW-2)) { //3칸 맞추었을 때
                                if (((vert_starting_point-1)==0) && (current_node.board_status[vert_ending_point+1][temp_column]!='_')) {
                                    current_node.heuristic_score += (-118);
                                }
                                int is_open_togo = 0;
                                if ((vert_starting_point-1) >=0) {
                                    if (current_node.board_status[vert_starting_point-1][temp_column] == '_')
                                        is_open_togo++;
                                        current_node.heuristic_score ++;
                                }
                                if ((vert_ending_point+1) < BOARD_SIZE) {
                                    if (current_node.board_status[vert_ending_point+1][temp_column] == '_') {
                                        is_open_togo++;
                                        current_node.heuristic_score ++;
                                    }
                                }
                                if (is_open_togo == 1) {
                                    current_node.heuristic_score ++;
                                }
                                else if (is_open_togo == 2){ //열린 삼일 때
                                    bool is_space = false;
                                    if ((vert_starting_point-2) >=0) {
                                        if (current_node.board_status[vert_starting_point-2][temp_column] == '_')
                                            is_space = true;
                                    }
                                    if ((vert_ending_point+2) < BOARD_SIZE) {
                                        if (current_node.board_status[vert_ending_point+2][temp_column] == '_') {
                                            is_space = true;
                                        }
                                    }
                                    if (is_space)
                                        current_node.heuristic_score += 218; //돌 놓을 공간이 있으면 +
                                    else
                                        current_node.heuristic_score += (-118); //돌 놓을 공간이 없으면 -
                                }
                                else
                                    current_node.heuristic_score += (-118); //그외엔 -
                            }
                            else if (matched_row == (REQUIRED_ROW-3)) { //2칸 맞추었을 때
                                if ((vert_ending_point+3) < BOARD_SIZE) {
                                    if ((current_node.board_status[vert_ending_point+1][temp_column] == '_')
                                        && (current_node.board_status[vert_ending_point+2][temp_column] == current_player)
                                        && (current_node.board_status[vert_ending_point+3][temp_column] == current_player)){
                                        current_node.heuristic_score += 2018;
                                    }
                                }
                                if ((vert_ending_point-3) >= 0) {
                                    if ((current_node.board_status[vert_ending_point-1][temp_column] == '_')
                                        && (current_node.board_status[vert_ending_point-2][temp_column] == current_player)
                                        && (current_node.board_status[vert_ending_point-3][temp_column] == current_player)){
                                        current_node.heuristic_score += 2018;
                                    }
                                }
                            }
                        }
                        else { // 상대편 플레이어 세로줄 체크
                            char check_player = current_node.board_status[temp_row][temp_column];
                            int matched_row = 1;
                            int vert_starting_point = cur_check_tile.first;
                            int vert_ending_point = cur_check_tile.first;
                            if (temp_row < (BOARD_SIZE - 1)) {
                                temp_row++;
                                while (current_node.board_status[temp_row][temp_column] == check_player) {
                                    cur_check_tile.first = temp_row;
                                    cur_check_tile.second = i;
                                    vert_ending_point = cur_check_tile.first;
                                    matched_row++;
                                    if (temp_row < (BOARD_SIZE - 1)) {
                                        temp_row++;
                                    }
                                    else
                                        break;
                                }
                            }
                            if (matched_row == REQUIRED_ROW) {
                                current_node.heuristic_score = -181818;
                                current_node.game_end = true;
                                return current_node;
                            }
                            else if (matched_row == (REQUIRED_ROW-1)) {
                                if ((vert_starting_point-1) >=0) {
                                    if (current_node.board_status[vert_starting_point-1][temp_column] == '_') {
                                        current_node.heuristic_score += (-2018);
                                    }
                                }
                                if ((vert_ending_point+1) < BOARD_SIZE) {
                                    if (current_node.board_status[vert_ending_point+1][temp_column] == '_')
                                        current_node.heuristic_score += (-2018);
                                }
                            }
                            else if (matched_row == (REQUIRED_ROW-2)) {
                                if (((vert_starting_point-1)==0) && (current_node.board_status[vert_ending_point+1][temp_column]!='_')) {
                                    current_node.heuristic_score += 118;
                                }
                                int is_open_togo = 0;
                                if ((vert_starting_point-1) >=0) {
                                    if (current_node.board_status[vert_starting_point-1][temp_column] == '_')
                                        is_open_togo++;
                                    current_node.heuristic_score --;
                                }
                                if ((vert_ending_point+1) < BOARD_SIZE) {
                                    if (current_node.board_status[vert_ending_point+1][temp_column] == '_')
                                        is_open_togo++;
                                    current_node.heuristic_score --;
                                }
                                if (is_open_togo == 1) {
                                    current_node.heuristic_score --;
                                }
                                else if (is_open_togo == 2){
                                    bool is_space = false;
                                    if ((vert_starting_point-2) >=0) {
                                        if (current_node.board_status[vert_starting_point-2][temp_column] == '_')
                                            is_space = true;
                                    }
                                    if ((vert_ending_point+2) < BOARD_SIZE) {
                                        if (current_node.board_status[vert_ending_point+2][temp_column] == '_')
                                            is_space = true;
                                    }
                                    if (is_space)
                                        current_node.heuristic_score += (-218);
                                    else
                                        current_node.heuristic_score += (118);
                                }
                                else
                                    current_node.heuristic_score += (118);
                            }
                            else if (matched_row == (REQUIRED_ROW-3)) {
                                if ((vert_ending_point+3) < BOARD_SIZE) {
                                    if ((current_node.board_status[vert_ending_point+1][temp_column] == '_')
                                        && (current_node.board_status[vert_ending_point+2][temp_column] == current_player)
                                        && (current_node.board_status[vert_ending_point+3][temp_column] == current_player)){
                                        current_node.heuristic_score += (-2018);
                                    }
                                }
                                if ((vert_ending_point-3) >= 0) {
                                    if ((current_node.board_status[vert_ending_point-1][temp_column] == '_')
                                        && (current_node.board_status[vert_ending_point-2][temp_column] == current_player)
                                        && (current_node.board_status[vert_ending_point-3][temp_column] == current_player)){
                                        current_node.heuristic_score += (-2018);
                                    }
                                }
                            }
                        }
                    }
                    temp_row = j;
                    temp_column = i;
                    if (current_node.board_status[temp_row][temp_column] != '_') {
                        pair<int, int> cur_check_tile;
                        cur_check_tile.first = temp_row;
                        cur_check_tile.second = temp_column;
                        if (current_node.board_status[temp_row][temp_column] == current_player) { //현재 플레이어 가로줄 체크
                            int matched_row = 1;
                            int horz_starting_point = cur_check_tile.second;
                            int horz_ending_point = cur_check_tile.second;
                            if (temp_column < (BOARD_SIZE - 1)) {
                                temp_column++;
                                while (current_node.board_status[temp_row][temp_column] == current_player) {
                                    cur_check_tile.first = temp_row;
                                    cur_check_tile.second = temp_column;
                                    horz_ending_point = cur_check_tile.second;
                                    matched_row++;
                                    if (temp_column < (BOARD_SIZE - 1)) {
                                        temp_column++;
                                    }
                                    else
                                        break;
                                }
                            }
                            if (matched_row == REQUIRED_ROW) { //승리했을 때 점수 부여
                                current_node.heuristic_score = 181818;
                                current_node.game_end = true;
                                return current_node;
                            }
                            else if (matched_row == (REQUIRED_ROW-1)) { //4칸 맞추었을 때
                                int is_open_togo = 0;
                                if ((horz_starting_point-1) >=0) {
                                    if (current_node.board_status[temp_row][horz_starting_point-1] == '_')
                                        is_open_togo++;
                                    current_node.heuristic_score += 2018;
                                }
                                if ((horz_ending_point+1) < BOARD_SIZE) {
                                    if (current_node.board_status[temp_row][horz_ending_point+1] == '_')
                                        is_open_togo++;
                                    current_node.heuristic_score += 2018;
                                }
                            }
                            else if (matched_row == (REQUIRED_ROW-2)) { //3칸 맞추었을 때
                                if (((horz_starting_point-1)==0) && (current_node.board_status[temp_row][horz_ending_point+1]!='_')) {
                                    current_node.heuristic_score += (-118);
                                }
                                int is_open_togo = 0;
                                if ((horz_starting_point-1) >=0) {
                                    if (current_node.board_status[temp_row][horz_starting_point-1] == '_')
                                        is_open_togo++;
                                    current_node.heuristic_score ++;
                                }
                                if ((horz_ending_point+1) < BOARD_SIZE) {
                                    if (current_node.board_status[temp_row][horz_ending_point+1] == '_') {
                                        is_open_togo++;
                                        current_node.heuristic_score ++;
                                    }
                                }
                                if (is_open_togo == 1) {
                                    current_node.heuristic_score ++;
                                }
                                else if (is_open_togo == 2){ //열린 삼일 때
                                    bool is_space = false;
                                    if ((horz_starting_point-2) >=0) {
                                        if (current_node.board_status[temp_row][horz_starting_point-2] == '_')
                                            is_space = true;
                                    }
                                    if ((horz_ending_point+2) < BOARD_SIZE) {
                                        if (current_node.board_status[temp_row][horz_ending_point+2] == '_') {
                                            is_space = true;
                                        }
                                    }
                                    if (is_space)
                                        current_node.heuristic_score += 218; //돌 놓을 공간이 있으면 +
                                    else
                                        current_node.heuristic_score += (-118); //돌 놓을 공간이 없으면 --
                                }
                                else
                                    current_node.heuristic_score += (-118); //그 외엔 -
                            }
                            else if (matched_row == (REQUIRED_ROW-3)) {
                                if ((horz_ending_point+3) < BOARD_SIZE) {
                                    if ((current_node.board_status[temp_row][horz_ending_point+1] == '_')
                                        && (current_node.board_status[temp_row][horz_ending_point+2] == current_player)
                                        && (current_node.board_status[temp_row][horz_ending_point+3] == current_player)){
                                        current_node.heuristic_score += 2018;
                                    }
                                }
                                if ((horz_ending_point-3) >= 0) {
                                    if ((current_node.board_status[temp_row][horz_ending_point-1] == '_')
                                        && (current_node.board_status[temp_row][horz_ending_point-2] == current_player)
                                        && (current_node.board_status[temp_row][horz_ending_point-3] == current_player)){
                                        current_node.heuristic_score += 2018;
                                    }
                                }
                            }
                        }
                        else { // 상대편 플레이어 가로줄 체크
                            char check_player = current_node.board_status[temp_row][temp_column];
                            int matched_row = 1;
                            int horz_starting_point = cur_check_tile.second;
                            int horz_ending_point = cur_check_tile.second;
                            if (temp_column < (BOARD_SIZE - 1)) {
                                temp_column++;
                                while (current_node.board_status[temp_row][temp_column] == check_player) {
                                    cur_check_tile.first = temp_row;
                                    cur_check_tile.second = temp_column;
                                    horz_ending_point = cur_check_tile.second;
                                    matched_row++;
                                    if (temp_column < (BOARD_SIZE - 1)) {
                                        temp_column++;
                                    }
                                    else
                                        break;
                                }
                            }
                            if (matched_row == REQUIRED_ROW) {
                                current_node.heuristic_score = -181818;
                                current_node.game_end = true;
                                return current_node;
                            }
                            else if (matched_row == (REQUIRED_ROW-1)) {
                                int is_open_togo = 0;
                                if ((horz_starting_point-1) >=0) {
                                    if (current_node.board_status[temp_row][horz_starting_point-1] == '_') {
                                        is_open_togo++;
                                        current_node.heuristic_score += (-2018);
                                    }
                                }
                                if ((horz_ending_point+1) < BOARD_SIZE) {
                                    if (current_node.board_status[temp_row][horz_ending_point+1] == '_') {
                                        is_open_togo++;
                                        current_node.heuristic_score += (-2018);
                                    }
                                }
                                else if (matched_row == (REQUIRED_ROW-2)) {
                                    if (((horz_starting_point-1)==0) && (current_node.board_status[temp_row][horz_ending_point+1]!='_')) {
                                    current_node.heuristic_score += 118;
                                }
                                    int is_open_togo = 0;
                                    if ((horz_starting_point-1) >=0) {
                                        if (current_node.board_status[temp_row][horz_starting_point-1] == '_')
                                            is_open_togo++;
                                        current_node.heuristic_score --;
                                    }
                                    if ((horz_ending_point+1) < BOARD_SIZE) {
                                        if (current_node.board_status[temp_row][horz_ending_point+1] == '_')
                                            is_open_togo++;
                                        current_node.heuristic_score --;
                                    }
                                    if (is_open_togo == 1) {
                                        current_node.heuristic_score --;
                                    }
                                    else if (is_open_togo == 2){
                                        bool is_space = false;
                                        if ((horz_starting_point-2) >=0) {
                                            if (current_node.board_status[temp_row][horz_starting_point-2] == '_')
                                                is_space = true;
                                        }
                                        if ((horz_ending_point+2) < BOARD_SIZE) {
                                            if (current_node.board_status[temp_row][horz_ending_point+2] == '_')
                                                is_space = true;
                                        }
                                        if (is_space)
                                            current_node.heuristic_score += (-218);
                                        else
                                            current_node.heuristic_score += (118);
                                    }
                                    else
                                        current_node.heuristic_score += (118);
                                }
                                else if (matched_row == (REQUIRED_ROW-3)) {
                                    if ((horz_ending_point+3) < BOARD_SIZE) {
                                        if ((current_node.board_status[temp_row][horz_ending_point+1] == '_')
                                            && (current_node.board_status[temp_row][horz_ending_point+2] == current_player)
                                            && (current_node.board_status[temp_row][horz_ending_point+3] == current_player)){
                                            current_node.heuristic_score += (-2018);
                                        }
                                    }
                                    if ((horz_ending_point-3) >= 0) {
                                        if ((current_node.board_status[temp_row][horz_ending_point-1] == '_')
                                            && (current_node.board_status[temp_row][horz_ending_point-2] == current_player)
                                            && (current_node.board_status[temp_row][horz_ending_point-3] == current_player)){
                                            current_node.heuristic_score += (-2018);
                                        }
                                    }
                                }
                            }
                        }    
                    }
                        temp_row = j;
                        temp_column = i;
                        if (current_node.board_status[temp_row][temp_column] != '_') {
                            pair<int, int> cur_check_tile;
                            cur_check_tile.first = temp_row;
                            cur_check_tile.second = temp_column;
                            if (current_node.board_status[temp_row][temp_column] == current_player) { //현재 플레이어 위대각선 체크
                                int matched_row = 1;
                                pair<int, int> upper_diag_starting_point = cur_check_tile;
                                pair<int, int> upper_diag_ending_point = cur_check_tile;
                                if ((temp_column < (BOARD_SIZE - 1)) && (temp_row > 0)) {
                                    temp_column++;
                                    temp_row--;
                                    while (current_node.board_status[temp_row][temp_column] == current_player) {
                                        cur_check_tile.first = temp_row;
                                        cur_check_tile.second = temp_column;
                                        upper_diag_ending_point = cur_check_tile;
                                        matched_row++;
                                        if ((temp_column < (BOARD_SIZE - 1)) && (temp_row > 0)) {
                                            temp_column++;
                                            temp_row--;
                                        }
                                        else
                                            break;
                                    }
                                }
                                if (matched_row == REQUIRED_ROW) {
                                    current_node.heuristic_score = 181818;
                                    current_node.game_end = true;
                                    return current_node;
                                }
                                else if (matched_row == (REQUIRED_ROW-1)) {
                                    if (((upper_diag_starting_point.first+1) < BOARD_SIZE) && ((upper_diag_starting_point.second-1) >=0)) {
                                        if (current_node.board_status[upper_diag_starting_point.first+1][upper_diag_starting_point.second-1] == '_')
                                            current_node.heuristic_score += 2018;
                                    }
                                    if (((upper_diag_ending_point.first-1) >= 0) && ((upper_diag_ending_point.second+1) < BOARD_SIZE)) {
                                        if (current_node.board_status[upper_diag_ending_point.first-1][upper_diag_ending_point.second+1] == '_')
                                            current_node.heuristic_score += 2018;
                                    }
                                }
                                else if (matched_row == (REQUIRED_ROW-2)) {
                                    if (((upper_diag_starting_point.first+1)==0) && ((upper_diag_starting_point.second-1)==0) && 
                                    (current_node.board_status[upper_diag_ending_point.first-1][upper_diag_ending_point.second+1]!='_')) {
                                    current_node.heuristic_score += (-118);
                                }
                                    int is_open_togo = 0;
                                    if (((upper_diag_starting_point.first+1) < BOARD_SIZE) && ((upper_diag_starting_point.second-1) >=0)) {
                                        if (current_node.board_status[upper_diag_starting_point.first+1][upper_diag_starting_point.second-1] == '_')
                                            is_open_togo++;
                                        current_node.heuristic_score ++;
                                    }
                                    if (((upper_diag_ending_point.first-1) >= 0) && ((upper_diag_ending_point.second+1) < BOARD_SIZE)) {
                                        if (current_node.board_status[upper_diag_ending_point.first-1][upper_diag_ending_point.second+1] == '_') {
                                            is_open_togo++;
                                            current_node.heuristic_score ++;
                                        }
                                    }
                                    if (is_open_togo == 1) {
                                        current_node.heuristic_score ++;
                                    }
                                    else if (is_open_togo == 2){
                                        bool is_space = false;
                                        if (((upper_diag_starting_point.first+2) < BOARD_SIZE) && ((upper_diag_starting_point.second-2) >=0)) {
                                            if (current_node.board_status[upper_diag_starting_point.first+2][upper_diag_starting_point.second-2] == '_')
                                                is_space = true;
                                        }
                                        if (((upper_diag_ending_point.first-2) >= 0) && ((upper_diag_ending_point.second+2) < BOARD_SIZE)) {
                                            if (current_node.board_status[upper_diag_ending_point.first-2][upper_diag_ending_point.second+2] == '_') {
                                                is_space = true;
                                            }
                                        }
                                        if (is_space)
                                            current_node.heuristic_score += 218;
                                        else
                                            current_node.heuristic_score += (-118);
                                    }
                                    else
                                        current_node.heuristic_score += (-118);
                                }
                                else if (matched_row == (REQUIRED_ROW-3)) {
                                    if (((upper_diag_ending_point.first-3) >= 0) && (upper_diag_ending_point.second + 3 < BOARD_SIZE)) {
                                        if ((current_node.board_status[upper_diag_ending_point.first-1][upper_diag_ending_point.second+1] == '_')
                                            && (current_node.board_status[upper_diag_ending_point.first-2][upper_diag_ending_point.second+2] == current_player)
                                            && (current_node.board_status[upper_diag_ending_point.first-3][upper_diag_ending_point.second+3] == current_player)){
                                            current_node.heuristic_score += 2018;
                                        }
                                    }
                                    if ((upper_diag_ending_point.first < (BOARD_SIZE - 3)) && ((upper_diag_ending_point.second - 3) >= 0)) {
                                        if ((current_node.board_status[upper_diag_ending_point.first+1][upper_diag_ending_point.second-1] == '_')
                                            && (current_node.board_status[upper_diag_ending_point.first+2][upper_diag_ending_point.second-2] == current_player)
                                            && (current_node.board_status[upper_diag_ending_point.first+3][upper_diag_ending_point.second-3] == current_player)){
                                            current_node.heuristic_score += 2018;
                                        }
                                    }
                                }
                            }
                            else { //상대편 플레이어 위대각선 체크
                                char check_player = current_node.board_status[temp_row][temp_column];
                                int matched_row = 1;
                                pair<int, int> upper_diag_starting_point = cur_check_tile;
                                pair<int, int> upper_diag_ending_point = cur_check_tile;
                                if ((temp_column < (BOARD_SIZE - 1)) && (temp_row > 0)) {
                                    temp_column++;
                                    temp_row--;
                                    while (current_node.board_status[temp_row][temp_column] == check_player) {
                                        cur_check_tile.first = temp_row;
                                        cur_check_tile.second = temp_column;
                                        upper_diag_ending_point = cur_check_tile;
                                        matched_row++;
                                        if ((temp_column < (BOARD_SIZE - 1)) && (temp_row > 0)) {
                                            temp_column++;
                                            temp_row--;
                                        }
                                        else
                                            break;
                                    }
                                }
                                if (matched_row == REQUIRED_ROW) {
                                    current_node.heuristic_score = -181818;
                                    current_node.game_end = true;
                                    return current_node;
                                }
                                else if (matched_row == (REQUIRED_ROW-1)) {
                                    if (((upper_diag_starting_point.first+1) < BOARD_SIZE) && ((upper_diag_starting_point.second-1) >=0)) {
                                        if (current_node.board_status[upper_diag_starting_point.first+1][upper_diag_starting_point.second-1] == '_')
                                            current_node.heuristic_score += (-2018);
                                        
                                    }
                                    if (((upper_diag_ending_point.first-1) >= 0) && ((upper_diag_ending_point.second+1) < BOARD_SIZE)) {
                                        if (current_node.board_status[upper_diag_ending_point.first-1][upper_diag_ending_point.second+1]== '_')
                                            current_node.heuristic_score += (-2018);
                                    }
                                }
                                else if (matched_row == (REQUIRED_ROW-2)) {
                                    if (((upper_diag_starting_point.first+1)==0) && ((upper_diag_starting_point.second-1)==0) && 
                                    (current_node.board_status[upper_diag_ending_point.first-1][upper_diag_ending_point.second+1]!='_')) {
                                    current_node.heuristic_score += 118;
                                }
                                    int is_open_togo = 0;
                                    if (((upper_diag_starting_point.first+1) < BOARD_SIZE) && ((upper_diag_starting_point.second-1) >=0)) {
                                        if (current_node.board_status[upper_diag_starting_point.first+1][upper_diag_starting_point.second-1] == '_')
                                            is_open_togo++;
                                        current_node.heuristic_score --;
                                    }
                                    if (((upper_diag_ending_point.first-1) >= 0) && ((upper_diag_ending_point.second+1) < BOARD_SIZE)) {
                                        if (current_node.board_status[upper_diag_ending_point.first-1][upper_diag_ending_point.second+1] == '_') {
                                            is_open_togo++;
                                            current_node.heuristic_score --;
                                        }
                                    }
                                    if (is_open_togo == 1) {
                                        current_node.heuristic_score --;
                                    }
                                    else if (is_open_togo == 2){
                                        bool is_space = false;
                                        if (((upper_diag_starting_point.first+2) < BOARD_SIZE) && ((upper_diag_starting_point.second-2) >=0)) {
                                            if (current_node.board_status[upper_diag_starting_point.first+2][upper_diag_starting_point.second-2] == '_')
                                                is_space = true;
                                        }
                                        if (((upper_diag_ending_point.first-2) >= 0) && ((upper_diag_ending_point.second+2) < BOARD_SIZE)) {
                                            if (current_node.board_status[upper_diag_ending_point.first-2][upper_diag_ending_point.second+2] == '_') {
                                                is_space = true;
                                            }
                                        }
                                        if (is_space)
                                            current_node.heuristic_score += (-218);
                                        else
                                            current_node.heuristic_score += (118);
                                    }
                                    else
                                        current_node.heuristic_score += (118);
                                }
                                else if (matched_row == (REQUIRED_ROW-3)) {
                                    if (((upper_diag_ending_point.first-3) >= 0) && (upper_diag_ending_point.second + 3 < BOARD_SIZE)) {
                                        if ((current_node.board_status[upper_diag_ending_point.first-1][upper_diag_ending_point.second+1] == '_')
                                            && (current_node.board_status[upper_diag_ending_point.first-2][upper_diag_ending_point.second+2] == current_player)
                                            && (current_node.board_status[upper_diag_ending_point.first-3][upper_diag_ending_point.second+3] == current_player)){
                                            current_node.heuristic_score += (-2018);
                                        }
                                    }
                                    if ((upper_diag_ending_point.first < (BOARD_SIZE -3)) && ((upper_diag_ending_point.second - 3) >= 0)) {
                                        if ((current_node.board_status[upper_diag_ending_point.first+1][upper_diag_ending_point.second-1] == '_')
                                            && (current_node.board_status[upper_diag_ending_point.first+2][upper_diag_ending_point.second-2] == current_player)
                                            && (current_node.board_status[upper_diag_ending_point.first+3][upper_diag_ending_point.second-3] == current_player)){
                                            current_node.heuristic_score += (-2018);
                                        }
                                    }
                                }
                            }
                        }
                        temp_row = j;
                        temp_column = i;
                        if (current_node.board_status[temp_row][temp_column] != '_') {
                            pair<int, int> cur_check_tile;
                            cur_check_tile.first = temp_row;
                            cur_check_tile.second = temp_column;
                            if (current_node.board_status[temp_row][temp_column] == current_player) { // 현재 플레이어 아래대각선 체크
                                int matched_row = 1;
                                pair<int, int> down_diag_starting_point = cur_check_tile;
                                pair<int, int> down_diag_ending_point = cur_check_tile;
                                if ((temp_column < (BOARD_SIZE - 1)) && (temp_row < (BOARD_SIZE - 1))) {
                                    temp_column++;
                                    temp_row++;
                                    while (current_node.board_status[temp_row][temp_column] == current_player) {
                                        cur_check_tile.first = temp_row;
                                        cur_check_tile.second = temp_column;
                                        down_diag_ending_point = cur_check_tile;
                                        matched_row++;
                                        if ((temp_column < (BOARD_SIZE - 1)) && (temp_row < (BOARD_SIZE - 1))) {
                                            temp_column++;
                                            temp_row++;
                                        }
                                        else
                                            break;
                                    }
                                }
                                if (matched_row == REQUIRED_ROW) {
                                    current_node.heuristic_score = 181818;
                                    current_node.game_end = true;
                                    return current_node;
                                }
                                else if (matched_row == (REQUIRED_ROW-1)) {
                                    if (((down_diag_starting_point.first-1) >=0) && ((down_diag_starting_point.second-1) >=0)) {
                                        if (current_node.board_status[down_diag_starting_point.first-1][down_diag_starting_point.second-1] == '_')
                                            current_node.heuristic_score += 2018;
                                    }
                                    if (((down_diag_ending_point.first+1) < BOARD_SIZE) && ((down_diag_ending_point.second+1) < BOARD_SIZE)) {
                                        if (current_node.board_status[down_diag_ending_point.first+1][down_diag_ending_point.second+1] == '_')
                                            current_node.heuristic_score += 2018;
                                    }
                                }
                                else if (matched_row == (REQUIRED_ROW-2)) {
                                    if (((down_diag_starting_point.first-1)==0) && ((down_diag_starting_point.second-1)==0) && 
                                    (current_node.board_status[down_diag_ending_point.first+1][down_diag_ending_point.second+1]!='_')) {
                                    current_node.heuristic_score += (-118);
                                }
                                    int is_open_togo = 0;
                                    if (((down_diag_starting_point.first-1) >=0) && ((down_diag_starting_point.second-1) >=0)) {
                                        if (current_node.board_status[down_diag_starting_point.first-1][down_diag_starting_point.second-1] == '_')
                                            is_open_togo++;
                                        current_node.heuristic_score ++;
                                    }
                                    if (((down_diag_ending_point.first+1) < BOARD_SIZE) && ((down_diag_ending_point.second+1) < BOARD_SIZE)) {
                                        if (current_node.board_status[down_diag_ending_point.first+1][down_diag_ending_point.second+1] == '_') {
                                            is_open_togo++;
                                            current_node.heuristic_score ++;
                                        }
                                    }
                                    if (is_open_togo == 1) {
                                        current_node.heuristic_score ++;
                                    }
                                    else if (is_open_togo == 2){
                                        bool is_space = false;
                                        if (((down_diag_starting_point.first-2) >=0) && ((down_diag_starting_point.second-2) >=0)) {
                                            if (current_node.board_status[down_diag_starting_point.first-2][down_diag_starting_point.second-2] == '_')
                                                is_space = true;
                                        }
                                        if (((down_diag_ending_point.first+2) < BOARD_SIZE) && ((down_diag_ending_point.second+2) < BOARD_SIZE)) {
                                            if (current_node.board_status[down_diag_ending_point.first+2][down_diag_ending_point.second+2] == '_') {
                                                is_space = true;
                                            }
                                        }
                                        if (is_space)
                                            current_node.heuristic_score += 218;
                                        else
                                            current_node.heuristic_score += (-118);
                                    }
                                    else
                                        current_node.heuristic_score += (-118);
                                }
                                else if (matched_row == (REQUIRED_ROW-3)) {
                                    if (((down_diag_ending_point.first+3) < BOARD_SIZE) && (down_diag_ending_point.second + 3 < BOARD_SIZE)) {
                                        if ((current_node.board_status[down_diag_ending_point.first+1][down_diag_ending_point.second+1] == '_')
                                            && (current_node.board_status[down_diag_ending_point.first+2][down_diag_ending_point.second+2] == current_player)
                                            && (current_node.board_status[down_diag_ending_point.first+3][down_diag_ending_point.second+3] == current_player)){
                                            current_node.heuristic_score += 2018;
                                        }
                                    }
                                    if (((down_diag_ending_point.first - 3) >= 0) && ((down_diag_ending_point.second - 3) >= 0)) {
                                        if ((current_node.board_status[down_diag_ending_point.first-1][down_diag_ending_point.second-1] == '_')
                                            && (current_node.board_status[down_diag_ending_point.first-2][down_diag_ending_point.second-2] == current_player)
                                            && (current_node.board_status[down_diag_ending_point.first-3][down_diag_ending_point.second-3] == current_player)){
                                            current_node.heuristic_score += 2018;
                                        }
                                    }
                                }
                            }
                            else { // 상대편 플레이어 아래대각선 체크
                                char check_player = current_node.board_status[temp_row][temp_column];
                                int matched_row = 1;
                                pair<int, int> down_diag_starting_point = cur_check_tile;
                                pair<int, int> down_diag_ending_point = cur_check_tile;
                                if ((temp_column < (BOARD_SIZE - 1)) && (temp_row < (BOARD_SIZE - 1))) {
                                    temp_column++;
                                    temp_row++;
                                    while (current_node.board_status[temp_row][temp_column] == check_player) {
                                        cur_check_tile.first = temp_row;
                                        cur_check_tile.second = temp_column;
                                        down_diag_ending_point = cur_check_tile;
                                        matched_row++;
                                        if ((temp_column < (BOARD_SIZE - 1)) && (temp_row < (BOARD_SIZE - 1))) {
                                            temp_column++;
                                            temp_row++;
                                        }
                                        else
                                            break;
                                    }
                                }
                                if (matched_row == REQUIRED_ROW) {
                                    current_node.heuristic_score = -181818;
                                    current_node.game_end = true;
                                    return current_node;
                                }
                                else if (matched_row == (REQUIRED_ROW-1)) {
                                    int is_open_togo = 0;
                                    if (((down_diag_starting_point.first-1) >=0) && ((down_diag_starting_point.second-1) >=0)) {
                                        if (current_node.board_status[down_diag_starting_point.first-1][down_diag_starting_point.second-1] == '_')
                                            is_open_togo++;
                                        current_node.heuristic_score += (-2018);
                                    }
                                    if (((down_diag_ending_point.first+1) < BOARD_SIZE) && ((down_diag_ending_point.second+1) < BOARD_SIZE)) {
                                        if (current_node.board_status[down_diag_ending_point.first+1][down_diag_ending_point.second+1] == '_')
                                            is_open_togo++;
                                        current_node.heuristic_score += (-2018);
                                    }
                                }
                                else if (matched_row == (REQUIRED_ROW-2)) {
                                    if (((down_diag_starting_point.first-1)==0) && ((down_diag_starting_point.second-1)==0) && 
                                    (current_node.board_status[down_diag_ending_point.first+1][down_diag_ending_point.second+1]!='_')) {
                                    current_node.heuristic_score += (-118);
                                }
                                    int is_open_togo = 0;
                                    if (((down_diag_starting_point.first-1) >=0) && ((down_diag_starting_point.second-1) >=0)) {
                                        if (current_node.board_status[down_diag_starting_point.first-1][down_diag_starting_point.second-1] == '_')
                                            is_open_togo++;
                                        current_node.heuristic_score --;
                                    }
                                    if (((down_diag_ending_point.first+1) < BOARD_SIZE) && ((down_diag_ending_point.second+1) < BOARD_SIZE)) {
                                        if (current_node.board_status[down_diag_ending_point.first+1][down_diag_ending_point.second+1] == '_') {
                                            is_open_togo++;
                                            current_node.heuristic_score --;
                                        }
                                    }
                                    if (is_open_togo == 1) {
                                        current_node.heuristic_score --;
                                    }
                                    else if (is_open_togo == 2){
                                        bool is_space = false;
                                        if (((down_diag_starting_point.first-2) >=0) && ((down_diag_starting_point.second-2) >=0)) {
                                            if (current_node.board_status[down_diag_starting_point.first-2][down_diag_starting_point.second-2] == '_')
                                                is_space = true;
                                        }
                                        if (((down_diag_ending_point.first+2) < BOARD_SIZE) && ((down_diag_ending_point.second+2) < BOARD_SIZE)) {
                                            if (current_node.board_status[down_diag_ending_point.first+2][down_diag_ending_point.second+2] == '_') {
                                                is_space = true;
                                            }
                                        }
                                        if (is_space)
                                            current_node.heuristic_score += (-218);
                                        else
                                            current_node.heuristic_score += (118);
                                    }
                                    else
                                        current_node.heuristic_score += (118);
                                }
                                else if (matched_row == (REQUIRED_ROW-3)) {
                                    if (((down_diag_ending_point.first+3) < BOARD_SIZE) && (down_diag_ending_point.second + 3 < BOARD_SIZE)) {
                                        if ((current_node.board_status[down_diag_ending_point.first+1][down_diag_ending_point.second+1] == '_')
                                            && (current_node.board_status[down_diag_ending_point.first+2][down_diag_ending_point.second+2] == current_player)
                                            && (current_node.board_status[down_diag_ending_point.first+3][down_diag_ending_point.second+3] == current_player)){
                                            current_node.heuristic_score += (-2018);
                                        }
                                    }
                                    if (((down_diag_ending_point.first - 3) >= 0) && ((down_diag_ending_point.second - 3) >= 0)) {
                                        if ((current_node.board_status[down_diag_ending_point.first-1][down_diag_ending_point.second-1] == '_')
                                            && (current_node.board_status[down_diag_ending_point.first-2][down_diag_ending_point.second-2] == current_player)
                                            && (current_node.board_status[down_diag_ending_point.first-3][down_diag_ending_point.second-3] == current_player)){
                                            current_node.heuristic_score += (-2018);
                                        }
                                    }
                                }
                            
                       
                    }
                }
            }
        }
        if (current_node.left_tiles == 0) {
            current_node.game_end = true;
        }
        return current_node;
    }

    vector<board_node> get_moves(board_node current_node, char score_player, char player) {
        vector<board_node> move_list;
        vector< pair<int, int> > get_list;
        int counted_col = 0;
        int counted_row = 0;
        for (vector<bool>::iterator iter = current_node.is_counted_col.begin(); iter!= current_node.is_counted_col.end(); iter++){
            if (*iter) {
                counted_col ++;
            }
        }
        for (vector<bool>::iterator iter = current_node.is_counted_row.begin(); iter!= current_node.is_counted_row.end(); iter++){
            if (*iter) {
                counted_row ++;
            }
        }
        if ((counted_col == 0) && (counted_row == 0)) {
            pair<int, int> temp(BOARD_SIZE/2, BOARD_SIZE/2);
            get_list.push_back(temp);
        }
        else {
            for (int i = 0; i < BOARD_SIZE; i++) {            
                for (int j = 0; j < BOARD_SIZE; j++) {
                        if (current_node.board_status[j][i] == '_'){
                            pair<int, int> temp (j, i);
                            get_list.push_back(temp);
                        }
                    }
            }
        }
        for (vector< pair<int, int> >::iterator iter = get_list.begin(); iter != get_list.end(); iter++) {
            board_node temp_board = current_node;
            int row = iter->first;
            int column = iter->second;
            temp_board.board_status[row][column] = player;
            temp_board.is_counted_col[column] = true;
            temp_board.is_counted_row[row] = true;
            temp_board.moved.second = column;
            temp_board.moved.first = row;
            temp_board = heuristic_func(temp_board, score_player);
            move_list.push_back(temp_board);
        }
        return move_list;
    }
    
    abp_node abp_minimax(board_node abp_root, abp_node alpha,
                                           abp_node beta, int depth, char player, bool minimaxflag,
                                           timespec &start_time, int time_limit, bool &timecut) {
        
        timespec current_time;
        char player_flag;
        clock_gettime(CLOCK_REALTIME, &current_time);
        double taken_time = (current_time.tv_sec - start_time.tv_sec);        
        if (taken_time > time_limit) {
            timecut = true;
            if (minimaxflag) return alpha;
            else return beta;
        }
        if (depth == 0 || abp_root.left_tiles == 0) {
            abp_node heuristic_node(0);
            heuristic_node.heuristic_score = abp_root.heuristic_score;
            heuristic_node.move = abp_root.moved;
            return heuristic_node;
        }
        if (player == 'X') {
            player_flag = minimaxflag ? 'X' : 'O';
        }
        else {
            if (player == 'O') {
                player_flag = minimaxflag ? 'O' : 'X';
            }
        }
        vector <board_node> moves = get_moves(abp_root, player, player_flag);
        if (minimaxflag) {
            for (vector<board_node>::iterator iter = moves.begin(); iter != moves.end(); iter++) {
                abp_node temp_score(0);
                temp_score = abp_minimax(*iter, alpha, beta, depth-1, player, false, start_time, time_limit, timecut);
                if (timecut) {
                    return alpha;
                }
                if (temp_score.heuristic_score > alpha.heuristic_score) {
                    alpha.heuristic_score = temp_score.heuristic_score;
                    alpha.move = iter->moved;
                }
                if (alpha.heuristic_score >= beta.heuristic_score)
                    break;
            }
            return alpha;
        }
        else {
            for (vector<board_node>::iterator iter = moves.begin(); iter != moves.end(); iter++) {
                abp_node temp_score(0);
                temp_score = abp_minimax(*iter, alpha, beta, depth-1, player, true, start_time, time_limit, timecut);
                if (timecut) {
                    return beta;
                }
                if (temp_score.heuristic_score < beta.heuristic_score) {
                    beta.heuristic_score = temp_score.heuristic_score;
                    beta.move = iter->moved;
                    
                }
                if (alpha.heuristic_score >= beta.heuristic_score)
                    break;
            }
            return beta;
        }
    }
    
    pair<int, int> iter_deep(board_node root, char current_player, int time_limit) {
        timespec start_time;
        abp_node alpha(0);
        abp_node beta(0);
        abp_node select(0);
        pair<int, int> result_move;
        alpha.heuristic_score = -10000000;
        beta.heuristic_score = 10000000;
        select.heuristic_score = 0;
        select.move.first = 0;
        select.move.second = 0;   
        int depth = 1;
        bool timecut = false;
        clock_gettime(CLOCK_REALTIME, &start_time);
        while (!timecut) {
            select = abp_minimax(root, alpha, beta, depth, current_player, true, start_time, time_limit, timecut);
            if (!timecut) {
                result_move = select.move;
                depth ++ ;
                cout << depth;
            }
        }
        return result_move;
    }
    
    board_node make_random_move (board_node current_node, char current_player) {
        int random_row = rand() % BOARD_SIZE;
        int random_column = rand() % BOARD_SIZE;
        if (current_node.board_status[random_row][random_column] == '_') {
            current_node.board_status[random_row][random_column] = current_player;
            current_node.left_tiles--;
            current_node.moved.first = random_row;
            current_node.moved.second = random_column;
            current_node.is_counted_col[random_column] = true;
            current_node.is_counted_row[random_row] = true;
        }
        else {
            while (current_node.board_status[random_row][random_column] != '_') {
                random_row = rand() % BOARD_SIZE;
                random_column = rand() % BOARD_SIZE;
            }
            current_node.board_status[random_row][random_column] = current_player;
            current_node.left_tiles--;
            current_node.moved.first = random_row;
            current_node.moved.second = random_column;
            current_node.is_counted_col[random_column] = true;
            current_node.is_counted_row[random_row] = true;
        }
        return current_node;
    }
    
    board_node move_aux(board_node current_node, char current_player, int row, int column) {
        board_node checknode (BOARD_SIZE);
        checknode = heuristic_func(current_node, current_player);
        if (checknode.game_end == true){
            cout << "게임이 끝났습니다." << endl;
        }
        else if (current_node.left_tiles == 0) {
            cout << "보드가 꽉찼습니다." << endl;
            return current_node;
        }
        else if ((row < 0 || row >= BOARD_SIZE) || (column < 0 || column >= BOARD_SIZE))  {
            cout << "잘못된 위치에 놓인 돌입니다.";
        }
        else if (current_node.board_status[row][column] != '_') {
            cout << "이미 공간에 돌이 놓여 있습니다. 임의의 장소에 놓여집니다.";
            current_node = make_random_move(current_node, current_player);
            return current_node;
        }
        else {
            current_node.board_status[row][column] = current_player;
            current_node.left_tiles--;
            current_node.moved.second = column;
            current_node.moved.first = row;
            current_node.is_counted_col[column] = true;
            current_node.is_counted_row[row] = true;
        }
        current_node = heuristic_func(current_node, current_player);
        return current_node;
    }
    
    void print_aux(board_node current_state, char current_player) {
        cout << endl;
        for (int i = 0; i <= 9; i++) {
            cout << i << "|";
        }
        for (int i = 0; i < 9; i++) {
            cout << i << "|";
        }
        for (int i = 0; i < BOARD_SIZE; i++) {
            cout << endl;
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << current_state.board_status[i][j] << "|";
                if (j == BOARD_SIZE-1) {
                    cout << i;
                }
            }
        }
        cout << endl;
        if (current_state.game_end) {
            cout << "게임이 끝났습니다." << endl << current_player << " player가 이겼습니다." << endl;
        }
    }
    
    void game_start(char selected_player, int time_limit) {
        board_node current_node(BOARD_SIZE);
        bool player_flag = true;
        while (current_node.game_end == false) {
            char current_player;
            current_player = player_flag ? 'X' : 'O';
            if (current_player == selected_player) {
                int row;
                int column;
                cout << "말의 행을 입력하세요 (0~18): ";
                cin >> row;
                cout << "말의 열을 입력하세요 (0~18): ";
                cin >> column;
                current_node = move_aux(current_node, current_player, row, column);
            }
            else {
                pair<int, int> results = iter_deep(current_node, current_player, time_limit);
                current_node = move_aux(current_node, current_player, results.first, results.second);
            }
            print_aux(current_node, current_player);
            player_flag = !player_flag;
        }
    }
    
    int main() {
        srand(time(NULL));
        int time_limit;
        int select_player;
        char selected_player;
        cout << "시간 제한을 입력하세요: ";
        cin >> time_limit;
        cout << "말을 선택하세요 (1 또는 2)" << endl;
        cout << "1은 X말, 선공 / 2는 O말, 후공: ";
        cin >> select_player;
        if (select_player == 1) {
            selected_player = 'X';
        }
        else if (select_player == 2) {
            selected_player = 'O';
        }
        game_start(selected_player, time_limit);
    }

