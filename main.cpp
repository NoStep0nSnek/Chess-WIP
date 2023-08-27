#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <bits/stdc++.h> // gives std::find

namespace pieces {
    class piece {
        public:
            int posX = 0;
            int posY = 0;
            int scope = 0; // getscope type
            char display = 'U'; // UNSET
            int type = 0; // 1 = King, 2 = Queen, 3 = Knight, 4 = Rook, 5 = Bishop, 6 = Pawn
    };
}

class pos2d {
    public:
        int X = 0;
        int Y = 0;
};

//pieces::piece iiiii;

//std::vector<pieces::piece> iiiiii = {iiiii};

class pos4d {
    public:
        // pos to move to to
        int X = 0;
        int Y = 0;
        // index of the piece to move
        int base_index = 0;
        //is_white;
        std::vector<pieces::piece> *user_reference_vec;
};

int getscope (int type) {

    switch(type) {
        case 1:
            return 1;
        case 2:
            return 8;
        case 3:
            return 0; // The Knight
        case 4:
            return 8;
        case 5:
            return 8;
        case 6:
            return 1;
    }
    return -1;
}

using namespace std;
using namespace pieces;

////////////////////////////////////////////////////////////////////////////////////////////////

vector<piece> white_pieces = {};
vector<piece> black_pieces = {};

bool whites_turn = true;

////////////////////////////////////////////////////////////////////////////////////////////////

void init_boards() {
    
    white_pieces = {};
    black_pieces = {};
    
    // -1 types means that piece is captured

    // White //
    ////////////////////////////////////////////////
    // creates white pawns

    for (int i = 0; i < 8; i++) {
        piece pawn;
        pawn.type = 6;
        pawn.display = 'P';
        pawn.scope = 0;
        pawn.posY = 6;
        pawn.posX = i;
        white_pieces.push_back(pawn);
    }

    piece rook;
    rook.type = 4;
    rook.display = 'R';
    rook.scope = 8;
    rook.posY = 7;
    rook.posX = 0;
    white_pieces.push_back(rook);

    rook.type = 4;
    rook.display = 'R';
    rook.scope = 8;
    rook.posY = 7;
    rook.posX = 7;
    white_pieces.push_back(rook);

    piece bishop;
    bishop.type = 5;
    bishop.display = 'B';
    bishop.scope = 8;
    bishop.posY = 7;
    bishop.posX = 1;
    white_pieces.push_back(bishop);

    bishop.type = 5;
    bishop.display = 'B';
    bishop.scope = 8;
    bishop.posY = 7;
    bishop.posX = 6;
    white_pieces.push_back(bishop);

    piece knight;
    knight.type = 3;
    knight.display = 'N';
    knight.scope = 8;
    knight.posY = 7;
    knight.posX = 2;
    white_pieces.push_back(knight);

    knight.type = 3;
    knight.display = 'N';
    knight.scope = 8;
    knight.posY = 7;
    knight.posX = 5;
    white_pieces.push_back(knight);

    piece queen;
    queen.type = 2;
    queen.display = 'Q';
    queen.scope = 8;
    queen.posY = 7;
    queen.posX = 3;
    white_pieces.push_back(queen);

    piece king;
    king.type = 1;
    king.display = 'K';
    king.scope = 8;
    king.posY = 7;
    king.posX = 4;
    white_pieces.push_back(king);

    // Black //
    ////////////////////////////////////////////////
    // creates black pawns

    for (int i = 0; i < 8; i++) {
        piece pawn;
        pawn.type = 6;
        pawn.display = 'P';
        pawn.scope = 0;
        pawn.posY = 1;
        pawn.posX = i;
        black_pieces.push_back(pawn);
    }

    rook.type = 4;
    rook.display = 'R';
    rook.scope = 8;
    rook.posY = 0;
    rook.posX = 0;
    black_pieces.push_back(rook);

    rook.type = 4;
    rook.display = 'R';
    rook.scope = 8;
    rook.posY = 0;
    rook.posX = 7;
    black_pieces.push_back(rook);

    bishop.type = 5;
    bishop.display = 'B';
    bishop.scope = 8;
    bishop.posY = 0;
    bishop.posX = 1;
    black_pieces.push_back(bishop);

    bishop.type = 5;
    bishop.display = 'B';
    bishop.scope = 8;
    bishop.posY = 0;
    bishop.posX = 6;
    black_pieces.push_back(bishop);

    knight.type = 3;
    knight.display = 'N';
    knight.scope = 8;
    knight.posY = 0;
    knight.posX = 2;
    black_pieces.push_back(knight);

    knight.type = 3;
    knight.display = 'N';
    knight.scope = 8;
    knight.posY = 0;
    knight.posX = 5;
    black_pieces.push_back(knight);

    queen.type = 2;
    queen.display = 'Q';
    queen.scope = 8;
    queen.posY = 0;
    queen.posX = 3;
    black_pieces.push_back(queen);

    king.type = 1;
    king.display = 'K';
    king.scope = 8;
    king.posY = 0;
    king.posX = 4;
    black_pieces.push_back(king);
}

bool is_pos_taken(vector<piece> vec1, vector<piece> vec2, int posX, int posY) {
/*
checks all of the pieces in the arrays to see if the target pos is taken
*/
    for (int i = 0; i < vec1.size(); i++) {
        if (vec1[i].posX == posX && vec1[i].posY == posY) {
            return true;
        }
    }

    for (int i = 0; i < vec2.size(); i++) {
        if (vec2[i].posX == posX && vec2[i].posY == posY) {
            return true;
        }
    }

    return false;
}

vector<pos2d> get_moves_diag(vector<piece> vec1, vector<piece> vec2, int scope, piece _piece) {
    
    int posD_UpNLeft = -1;
    int posD_UpNRight = -1;
    int posD_DownNLeft = -1;
    int posD_DownNRight = -1;

    vector<pos2d> valid_moves = {};

    for (int i = 0; i < scope; i++) {
        if (is_pos_taken(vec1, vec2, _piece.posX - i, _piece.posY + i) && posD_UpNLeft == -1) {
            posD_UpNLeft = scope;
        } else {
            pos2d move;
            move.X = _piece.posX - i;
            move.Y = _piece.posY + i;
            valid_moves.push_back(move);
        }
    }
    for (int i = 0; i < scope; i++) {
        if (is_pos_taken(vec1, vec2, _piece.posX + i, _piece.posY + i) && posD_UpNRight == -1) {
            posD_UpNRight = scope;
        } else {
            pos2d move;
            move.X = _piece.posX + i;
            move.Y = _piece.posY + i;
            valid_moves.push_back(move);
        }
    }
    for (int i = 0; i < scope; i++) {
        if (is_pos_taken(vec1, vec2, _piece.posX - i, _piece.posY - i) && posD_DownNLeft == -1) {
            int posD_DownNLeft = -1;
        } else {
            pos2d move;
            move.X = _piece.posX - i;
            move.Y = _piece.posY - 1;
            valid_moves.push_back(move);
        }
    }
    for (int i = 0; i < scope; i++) {
        if (is_pos_taken(vec1, vec2, _piece.posX + i, _piece.posY - i) && posD_DownNRight == -1) {
            int posD_DownNRight = -1;
        } else {
            pos2d move;
            move.X = _piece.posX + i;
            move.Y = _piece.posY - i;
            valid_moves.push_back(move);
        }
    }
    
    return valid_moves;
}


/*
https://learn.chessbase.com/en/page/chess-rules-castling?setssocookie=eVSEJkg4HQR%2fdz5TCwmcTFg93m9K7%2bv31ta9afX9%2bMA%3d
The rules for castling
    -castling is only possible if neither the king nor the rook has moved
    -there must not be any pieces between the king and the rook
    -the king may not be in check
    -the square the king goes to and any intervening squares may not be under attack
    -however, there is nothing to prevent castling if the rook is under attack
*/

// returns 0 if not, 1 if in the king is check, 2 if the king is in checkmate

bool can_castle (vector<piece> vec1, vector<piece> vec2, piece start_piece, piece end_piece, bool is_white) {
     
    vector<piece> *users_vec;
    vector<piece> *enemy_vec;

    if (is_white) {
        users_vec = &vec1;
        enemy_vec = &vec2;
    } else {
        users_vec = &vec2;
        enemy_vec = &vec1;
    }

    bool is_blocked;

    if (!(start_piece.type != 1 && end_piece.type != 4) || (start_piece.type != 4 && end_piece.type != 1) && start_piece.posY != end_piece.posY) {
        return false;
    }

    // diff in between the rook and the king
    int x_diff = abs(start_piece.posX - end_piece.posX);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < x_diff; j++) {
            if (white_pieces[i].posX = min(start_piece.posX, end_piece.posX) + j) {
                return false;
            }
            if (black_pieces[i].posX = min(start_piece.posX, end_piece.posX) + j) {
                return false;
            }
        }
    }

    if (x_diff > 4) {
        return false;
    }

    return true;
}

vector<pos2d> get_moves_straight(vector<piece> vec1, vector<piece> vec2, int scope, piece _piece) {
    
    int posX_left = -1;
    int posX_right = -1;
    int posY_up = -1;
    int posY_down = -1;

    vector<pos2d> valid_moves = {};

    for (int i = 0; i < scope; i++) {
        if (is_pos_taken(vec1, vec2, _piece.posX + i, _piece.posY) && posX_right == -1) {
            posX_right == scope;
        } else {
            pos2d move;
            move.X = _piece.posX + i;
            move.Y = _piece.posY;
            valid_moves.push_back(move);
        }
        if (is_pos_taken(vec1, vec2, _piece.posX - i, _piece.posY) && posX_left == -1) {
            posX_left == scope;
        } else {
            pos2d move;
            move.X = _piece.posX - i;
            move.Y = _piece.posY;
            valid_moves.push_back(move);
        }
        if (is_pos_taken(vec1, vec2, _piece.posX, _piece.posY + i) && posY_up == -1) {
            posY_up == scope;
        } else {
            pos2d move;
            move.X = _piece.posX;
            move.Y = _piece.posY + i;
            valid_moves.push_back(move);
        }
        if (is_pos_taken(vec1, vec2, _piece.posX, _piece.posY - i) && posY_up == -1) {
            posY_down == scope;
        } else {
            pos2d move;
            move.X = _piece.posX;
            move.Y = _piece.posY - i;
            valid_moves.push_back(move);
        }
    }

    return valid_moves;
}

vector<pos2d> get_moves_pawns(vector<piece> vec1, vector<piece> vec2, piece _piece, bool is_white) {

    vector<pos2d> valid_moves;

    int a = 1;

    if (is_white) {
        a = -1;
    }

    if (!is_white && _piece.posY == 1) {
        a = 2;
    }

    if (is_white && _piece.posY == 6) {
        a = -2;
    }

    if (is_pos_taken(vec1, vec2, _piece.posX + 1, _piece.posY + a)) {
        pos2d move;
        move.X = _piece.posX + 1;
        move.Y = _piece.posY + a;
        valid_moves.push_back(move);
    }

    if (is_pos_taken(vec1, vec2, _piece.posX - 1, _piece.posY + a)) {
        pos2d move;
        move.X = _piece.posX - 1;
        move.Y = _piece.posY + a;
        valid_moves.push_back(move);
    }

    if (!is_pos_taken(vec1, vec2, _piece.posX , _piece.posY + a)) {
        pos2d move;
        move.X = _piece.posX;
        move.Y = _piece.posY + a;
        valid_moves.push_back(move);
    }

    return valid_moves;
}

vector<pos2d> get_moves_knight(vector<piece> vec1, vector<piece> vec2, piece _piece) {
    
    vector<pos2d> valid_moves;

    for (int i = -2; i <= 2; i += 4) {
        if (!is_pos_taken(vec1, vec2, _piece.posX + i, _piece.posY + 1)) {
            pos2d move;
            move.X = _piece.posX;
            move.Y = _piece.posY;
            valid_moves.push_back(move);
        }
        if (!is_pos_taken(vec1, vec2, _piece.posX + i, _piece.posY - 1)) {
            pos2d move;
            move.X = _piece.posX;
            move.Y = _piece.posY;
            valid_moves.push_back(move);
        }
        if (!is_pos_taken(vec1, vec2, _piece.posX + 1, _piece.posY + i)) {
            pos2d move;
            move.X = _piece.posX;
            move.Y = _piece.posY;
            valid_moves.push_back(move);
        }
        if (!is_pos_taken(vec1, vec2, _piece.posX - 1, _piece.posY + i)) {
            pos2d move;
            move.X = _piece.posX;
            move.Y = _piece.posY;
            valid_moves.push_back(move);
        }
    }

    return valid_moves;
}
/*
searches for a piece in an array at a given position. If it finds it the func returns
the index of the piece.
*/
int search_for_piece(vector<piece> arr, pos2d pos) {
    //if (is_white) {
        //arr = white_pieces;
    //}
    for (int i = 0; i < arr.size(); i++) {
        //cout << "(" << "X:"<< pos.X << "Y:"<< pos.Y << ")";
        //cout << "(" << "X:"<< arr[i].posX << "Y:"<< arr[i].posY << ")";
        if (arr[i].posX == pos.X && arr[i].posY == pos.Y) {
            //cout << i <<"(" << "X:"<< arr[i].posX << "Y:"<< arr[i].posY << ")";
            return i;
        }
    }

    return -1;
}

// start posX & start posY can be retrieved from _piece

bool is_move_valid (vector<piece> vec1, vector<piece> vec2, piece _piece, pos2d endpos, bool is_white) {
    
    vector<pos2d> moves_straight = get_moves_straight(vec1, vec2, getscope(_piece.type), _piece);
    vector<pos2d> moves_diag = get_moves_diag(vec1, vec2, getscope(_piece.type), _piece);
    vector<pos2d> moves_pawns = get_moves_pawns(vec1, vec2, _piece, is_white);
    vector<pos2d> moves_knights = get_moves_knight(vec1, vec2, _piece);

    if (_piece.type == 1 || _piece.type == 2 || _piece.type == 4) {
        for (int i = 0; i < moves_straight.size(); i++) {
            if (moves_straight[i].X == endpos.X || moves_straight[i].Y == endpos.Y) {
                return true;
            }
        }
    }

    if (_piece.type == 1 || _piece.type == 2 || _piece.type == 5) { 
        for (int i = 0; i < moves_diag.size(); i++) {
            if (moves_diag[i].X == endpos.X || moves_diag[i].Y == endpos.Y) {
                return true;
            }
        }
    }
    // checks that the king has not moved more than 1 space
    if (_piece.type == 1) {
        if (abs(_piece.posX - endpos.X) > 1) {
            return false;
        }
        if (abs(_piece.posY -  endpos.Y) > 1) {
            return false;
        }
    }

    if (_piece.type == 4) {
        for (int i = 0; i < moves_knights.size(); i++) {
            if (moves_knights[i].X == endpos.X || moves_knights[i].Y == endpos.Y) {
                return true;
            }
        }
    }

    if (_piece.type == 6) {
        for (int i = 0; i < moves_pawns.size(); i++) {
            if (moves_pawns[i].X == endpos.X || moves_pawns[i].Y == endpos.Y) {
                return true;
            }
        }
    }
    
    return false;
}

// checks to see if is_white can checkmate !is_white
int is_in_check_or_checkmate(vector<piece> vec1, vector<piece> vec2, bool is_white) {

    vector<piece> users_vec;
    vector<piece> enemy_vec;

    if (is_white) {
        users_vec = vec1;
        enemy_vec = vec2;
    } else {
        users_vec = vec2;
        enemy_vec = vec1;
    }

    pos2d kings_pos;
    kings_pos.X = users_vec[15].posX;
    kings_pos.Y = users_vec[15].posY;

    int borders_taken = 9;
    bool in_check = false;

    for (int i = 0; i < enemy_vec.size(); i++) {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {

                pos2d end_pos;
                end_pos.X = kings_pos.X - 1 + x;
                end_pos.Y = kings_pos.Y - 1 + y;

                if (is_move_valid(white_pieces, black_pieces, enemy_vec[i], end_pos, !is_white)) {
                    borders_taken -= 1;
                }
            }
        }

        if (is_move_valid(white_pieces, black_pieces, enemy_vec[i], kings_pos, !is_white)) {
            in_check = true;
        }
    }

    if (borders_taken > 8) {
        return 2;
    }

    if (in_check) {
        return 1;
    }

    return 0;
}

// moves a piece from one pos to another. Returns 1 if succesful, 0 if not.
// vec1 = white
// vec2 = black
bool move_pos(vector<piece>& vec1, vector<piece>& vec2, pos2d start_pos, pos2d end_pos, bool is_white) {

    vector<piece> *users_vec;
    vector<piece> *enemy_vec;

    if (is_white) {
        users_vec = &vec1;
        enemy_vec = &vec2;
    } else {
        users_vec = &vec2;
        enemy_vec = &vec1;
    }

    // check if piece exists
    int a = search_for_piece(*users_vec, start_pos);
    int b = search_for_piece(*users_vec, end_pos);

    piece _piece;
    piece end_piece;

    if (a != -1) {
        _piece = (*users_vec)[a];
    } else {
        printf("a = %d | start pos not found\n", a);
        return -1;
    }
    if (b != -1) {
        end_piece = (*users_vec)[b];
    }

    bool to_castle = false;

    if (!(white_pieces[search_for_piece(*users_vec, start_pos)].type == 1 && white_pieces[search_for_piece(*users_vec, end_pos)].type == 4)) {
        //to_castle = true;
    } else if (!(white_pieces[search_for_piece(*users_vec, end_pos)].type == 4 && white_pieces[search_for_piece(*users_vec, start_pos)].type == 1)) {
        //to_castle = true;
    }

    if (to_castle) {
        int midpoint = ceil(start_pos.X + end_pos.X) / 2;
        int sign = (start_pos.X - end_pos.X) / abs(start_pos.X - end_pos.X);

        (*users_vec)[a].posX = end_pos.X;
        (*users_vec)[b].posX = start_pos.X;
    } else {
        if (is_move_valid(white_pieces, black_pieces, _piece, end_pos, is_white)) {
            cout << "VALID\n";
            (*users_vec)[a].posX = end_pos.X;
            (*users_vec)[a].posY = end_pos.Y;
        } else {
            cout << "INVALID MOVE\n";
        }
    }

    return 0;
}


// type (1 = row, 2 = column, 3 = diagonal)

bool is_piece_at_risk(vector<piece> vec1, vector<piece> vec2, bool is_white, piece _piece) {

    vector<piece> users_vec;
    vector<piece> enemy_vec;

    if (is_white) {
        users_vec = vec1;
        enemy_vec = vec2;
    } else {
        users_vec = vec2;
        enemy_vec = vec1;
    }

    for (int i = 0; i < 8; i++) {
        pos2d end_pos;
        end_pos.X = _piece.posX;
        end_pos.Y = _piece.posY;
        if (is_move_valid(vec1, vec2, enemy_vec[i], end_pos, !is_white)) {
            return true;
        }
    }

    return false;
}

bool is_piece_protected(vector<piece> vec1, vector<piece> vec2, piece _piece, bool is_white) {

    vector<piece> &users_vec = vec1;
    vector<piece> &enemy_vec = vec1;
    
    if (is_white) {
        users_vec = vec1;
        enemy_vec = vec2;
    } else {
        users_vec = vec2;
        enemy_vec = vec1;
    }

    /*int index = 0;
    for (int i = 0; i < users_vec.size(); i++) {
        if (users_vec[i].posX == _piece.posX && users_vec[i].posY == _piece.posY) {
            index = i;
            break;
        }
    }*/

    pos2d endpos;
    endpos.X = _piece.posX;
    endpos.Y = _piece.posY;
    
    _piece.posX -= 10;

    for (int i = 0; i < 8; i++) {
        if (is_move_valid(vec1, vec2, _piece, endpos, is_white)) {
            return true;
        }
    }
    
    _piece.posX += 10;

    return false;
}

bool is_blocked(vector<piece> vec1, vector<piece> vec2, piece _piece, pos2d end_pos, int type, bool is_white) {
    if (type == 1) {
        int min = std::min(_piece.posX, end_pos.X);
        int max = std::max(_piece.posX, end_pos.X);
        for (int i = min; i < max; i++) {
            if (vec1[i].posY == _piece.posY && vec1[i].posX == i) {
                return true;
            }

            if (vec2[i].posY == _piece.posY && vec2[i].posX == i) {
                return true;
            }
        }
    }

    if (type == 2) {
        int min = std::min(_piece.posY, end_pos.Y);
        int max = std::max(_piece.posY, end_pos.Y);
        for (int i = min; i < max; i++) {
            if (vec1[i].posX == _piece.posX && vec1[i].posY == i) {
                return true;
            }

            if (vec2[i].posX == _piece.posX && vec2[i].posY == i) {
                return true;
            }
        }
    }

    return false;
}

int is_rook_strong(vector<piece> vec1, vector<piece> vec2, piece _piece, bool is_white) {

    bool doubled_on_X = false;
    bool doubled_on_Y = false;
    bool rook_on_7th = false;
    
    if (_piece.type != 4) { // checks if its a rook or not
        return false;
    }
    

    vector<piece> user_vec;
    vector<piece> enemy_vec;

    if (is_white) {
        user_vec = vec1;
        enemy_vec = vec2;
    } else {
        enemy_vec = vec1;
        user_vec = vec2;
    }

    // checks if rook is doubled (next to or above each other)
    for (int i = 0; i < user_vec.size(); i++) {
        // is row or column blocked?
        if (user_vec[i].type = _piece.type) {

            pos2d end_pos;
            end_pos.X = user_vec[i].posX;
            end_pos.Y = user_vec[i].posY;

            if (!is_blocked(vec1, vec2, _piece, end_pos, 1, is_white) && user_vec[i].posX == _piece.posX) {
                doubled_on_X = true;
            }

            if (!is_blocked(vec1, vec2, _piece, end_pos, 2, is_white) && user_vec[i].posY == _piece.posY) {
                doubled_on_Y = true;
            }
        }
    }

    // checks if rook is on 7th
    if ((is_white && _piece.posY == 1) || ( !is_white && _piece.posY == 6)) { // counting starts at 0, keep that in mind
        rook_on_7th = true;
    }

    // checks if the file that the rook is on is open (returns an int from 1 - 8; 8 being completely full)
    int open_pieces_x = 0;

    for (int i = 0; i < 8; i++) {
        int max_upper = _piece.posY;
        int max_lower = _piece.posY;
        if (enemy_vec[i].posX == _piece.posX) {
            if (enemy_vec[i].posY > max_upper && max_upper != _piece.posY) {
                max_upper =  enemy_vec[i].posY;
            }
            if (enemy_vec[i].posY < max_lower && max_lower != _piece.posY) {
                max_upper =  enemy_vec[i].posY;
            }
        }
        if (user_vec[i].posX == _piece.posX) {
            if (user_vec[i].posY > max_upper && max_upper != _piece.posY) {
                max_upper =  user_vec[i].posY;
            }
            if (user_vec[i].posY < max_lower && max_lower != _piece.posY) {
                max_upper =  user_vec[i].posY;
            }
        }
    }

    return rook_on_7th + doubled_on_X + doubled_on_Y + open_pieces_x;
}

/*"(a)Advanced knights (at e5, d5, c5, f5, e6, d6, c6, f6), especially if protected by
pawn and free from pawn attack." */
bool is_knight_strong(vector<piece> vec1, vector<piece> vec2, piece _piece, bool is_white) {

    if (_piece.type != 3) {
        return false;
    }

    //bool protected_ = is_piece_protected(vec1, vec2, is_white, _piece);
    bool good_space = false;

    for (int i = 0; i < 2; i++) {
        int a;
        if (is_white) {
            a = 5 + i;
        } else {
            a = 3 + i;
        }
        if ((_piece.posX == 'E' - 65 && _piece.posY == a) || (_piece.posX == 'D' - 65 && _piece.posY == a) || (_piece.posX == 'C' - 65 && _piece.posY == a) || (_piece.posX == 'F' - 65 && _piece.posY == a)) {
            good_space = true;
        }
    }

    return good_space;
}

/*(2)Pawn formation:
(a)Backward, isolated and doubled pawns.
(b)Relative control of centre (pawns at e4, d4, c4).
(c)Weakness of pawns near king (e.g. advanced g pawn).
(d)Pawns on opposite colour squares from bishop.
(e)Passed pawns. 
*/
int is_pawn_strong(vector<piece> vec1, vector<piece> vec2, piece _piece, bool is_white)
{

    if (_piece.type != 6) {
        return false;
    }

    vector<piece> users_vec;
    vector<piece> enemy_vec;

    if (is_white) {
        users_vec = vec1;
        enemy_vec = vec2;
    } else {
        users_vec = vec2;
        enemy_vec = vec1;
    }

    bool isolated = true;
    bool passed = false;
    bool backwards = false;
    bool opposite_of_bishop = false;

    // checks if its isolated (avoid this)

    for (int i = 0; i < users_vec.size(); i++) {
        if (users_vec[i].type == 6 && (users_vec[i].posX == _piece.posX - 1) || (users_vec[i].posX == _piece.posX + 1)) {
            isolated = false;
        }
    }

    // checks if pawn is backwards (avoid this)

    for (int i = 0; i < users_vec.size(); i++) {
        if (users_vec[i].posY > _piece.posY) {
            backwards = true;
            break;
        }
    }


    // checks if pawn is on an oppisite color sqaure from the enemies bishop 
    // first to make sure that there is only one bishop
    bool one_bishop = false;
    int bishop_index = -1;

    for (int i = 0; i < enemy_vec.size(); i++) {
        if (enemy_vec[i].type == 5) {
            one_bishop = true;
            bishop_index = i;
            break;
        }
    }

    if (bishop_index != -1) {
        if ((_piece.posX + _piece.posY) % 2 == !(enemy_vec[bishop_index].posX + enemy_vec[bishop_index].posY) % 2)
        {
            opposite_of_bishop = true;
        }
    }

    // checks if pawn is passed (passed means that it has no pieces in front of it)
    for (int i = 0; i < 8; i++) {
        pos2d check_pos;
        check_pos.X = _piece.posX;
        check_pos.Y = _piece.posY;
        if ((vec1[i].posX == check_pos.X && vec1[i].posY == check_pos.Y + 1) || (vec2[i].posX == check_pos.X && vec2[i].posY == check_pos.Y + 1))
        {
            passed = true;
        }
    }

    // calculates distance from center
    float dist_from_center = sqrt(pow(_piece.posX - 4, 2) + pow(_piece.posY - 4, 2));

    // calculates distances of pawn from king
    pos2d king_pos;
    king_pos.X = users_vec[7].posX;
    king_pos.Y = users_vec[7].posY;

    float dist_from_king = sqrt(pow(_piece.posX - king_pos.X, 2) + pow(_piece.posY - king_pos.Y, 2));

    return !isolated + !backwards + passed + opposite_of_bishop + dist_from_center + dist_from_king;
}

// see: https://vision.unipv.it/IA1/ProgrammingaComputerforPlayingChess.pdf, p. 17
pos4d calc_AI_pos(vector<piece> vec1, vector<piece> vec2, bool is_white) {

    vector<piece> users_vec;
    vector<piece> enemy_vec;

    if (is_white) {
        users_vec = vec1;
        enemy_vec = vec1;
    } else {
        enemy_vec = vec1;
        users_vec = vec1;
    }

    pos4d best_pos;
    int best = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 64; j++) {

            piece end_piece = users_vec[i];
            end_piece.posX = j % 8;
            end_piece.posY = floor(j / 8);

            pos2d end_pos;
            end_pos.X = j % 8;
            end_pos.Y = floor(j / 8);

            int protected_ = is_piece_protected(vec1, vec2, end_piece, is_white);
            int pawn = is_pawn_strong(vec1, vec2, end_piece, is_white);
            int knight = is_knight_strong(vec1, vec2, end_piece, is_white);
            int rook = is_rook_strong(vec1, vec2, end_piece, is_white);

            if (is_move_valid(vec1, vec2, users_vec[i], end_pos, is_white)) {
                float a = protected_ + pawn + knight + rook;
                if (a > best) {
                    best = a;
                    cout << users_vec[i].display << ",";
                    best_pos.X = end_pos.X;
                    best_pos.Y = end_pos.Y;
                    best_pos.base_index = i;
                    best_pos.user_reference_vec = &users_vec;
                }
            }
        }
    }

    // default opening moves
    // see: https://www.masterclass.com/articles/chess-101-what-are-the-best-opening-moves-in-chess-learn-5-tips-for-improving-your-chess-opening
    // for black only
    // Sicilian Defense, Najdorf Variation
    if () {

    }

    // Petrov’s Defense


    return best_pos;
}

// I.E: A,1
pos2d str_to_pos(string str_pos) {

    int posX = str_pos[2] - 48;
    int posY = tolower(str_pos[0]) - 97;

    pos2d pos;
    pos.X = posX - 1;
    pos.Y = posY;

    if (str_pos[1] != ',') {
        pos.X = -1;
    }

    if (posX > 8 || posX < 0 || posY > 8 || posY < 0) {
        pos.X = -1;
    }
    return pos;
}

void render_board(vector<piece> vec1, vector<piece> vec2) {

    //printf("\033c"); // clears board

    printf("   |   |   |   |   |   |   |   |   \n");
    printf("   ");
    for (int i = 0; i < 8; i++) {
        printf("| %c ", i + 49);
    }
    printf("\n   |   |   |   |   |   |   |   |   \n");
    printf("-----------------------------------\n");
    for (int i = 0; i < 8; i++) {
        printf("   |   |   |   |   |   |   |   |   \n");
        printf(" %c |", i + 65);
        for (int j = 0; j < 8; j++) {
            bool printed_char = false;
            for (int k = 0; k < 16; k++) {
                if (vec1[k].posX == j && vec1[k].posY == i) {
                    printf("W.%c", vec1[k].display);
                    printed_char = true;
                    break;
                } else if (vec2[k].posX == j && vec2[k].posY == i) {
                    printf("B.%c", vec2[k].display);
                    printed_char = true;
                    break;
                }
            }

            if (!printed_char) {
                printf("   ");
            }

            if (j < 7) {
                printf("|");
            }
        }
        printf("\n   |   |   |   |   |   |   |   |   \n");
        if (i < 7) {
            printf("-----------------------------------\n");
        }
    }
}

int main() {

    init_boards();

    render_board(white_pieces, black_pieces);

    bool white_won = false;
    bool black_won = false;

    while (!(white_won || black_won)) {
        
        if (whites_turn) {

            printf("\nIt is whites turn. Enter the position of a piece that you would like to move: ");
            string answer;
            std::getline (std::cin, answer);
            pos2d start_pos = str_to_pos(answer);
            if (start_pos.X == -1){
                printf("Invalid Pos.");
            }
            printf("\nEnter a position on the board to move it to: ");
            std::getline (std::cin, answer);
            pos2d end_pos = str_to_pos(answer);
            if (end_pos.X == -1){
                printf("Invalid Pos.");
            }
            move_pos(white_pieces, black_pieces, start_pos, end_pos, whites_turn);

            whites_turn = (!whites_turn);

        } else {
            /*
            printf("\nIt is blacks turn. Enter the position of a piece that you would like to move: ");
            string answer;
            std::getline (std::cin, answer);
            pos2d start_pos = str_to_pos(answer);
            if (start_pos.X == -1){
                printf("Invalid Pos.");
            }
            printf("\nEnter a position on the board to move it to: ");
            std::getline (std::cin, answer);
            pos2d end_pos = str_to_pos(answer);
            if (end_pos.X == -1){
                printf("Invalid Pos.");
            }
            */

            //AI:

            pos4d pos = calc_AI_pos(white_pieces, black_pieces, whites_turn);
            pos2d start_pos;
            start_pos.X = (*pos.user_reference_vec)[pos.base_index].posX;
            start_pos.Y = (*pos.user_reference_vec)[pos.base_index].posY;
            pos2d end_pos;
            end_pos.X = pos.X;
            end_pos.Y = pos.Y;
            cout << "\n STARTPOS: " << start_pos.X << "X, " << start_pos.Y << "Y";
            cout << "\n ENDPOS: " << end_pos.X << "X, " << end_pos.Y << "Y\n";

            move_pos(white_pieces, black_pieces, start_pos, end_pos, whites_turn);

            whites_turn = (!whites_turn);

        }

        render_board(white_pieces, black_pieces);
    }

    return 0;
}
