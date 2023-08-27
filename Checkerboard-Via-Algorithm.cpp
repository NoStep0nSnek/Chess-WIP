#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    vector<char> board;
    int previous_row = 0;
    for (int i = 0; i < 64; i++) {
        int row = floor(i / 8);
        int column = i % 8;
        if (row != previous_row) {
            cout << "| " << row << "\n";
        }
        if ((column + row) % 2 == 0) {
            cout << "#";
            board.push_back('#');
        } else {
            cout << " ";
            board.push_back(' ');
        }
        previous_row = row;
    }

    int pos = 15;
    cout << "\nActual Piece: " << "\"" << board[pos] << "\" ";
    int row = floor(pos / 8);
    int column = pos % 8;
    if ((column + row) % 2 == 0) {
        cout << "\nCalculated Piece:" << "\"#\"";
    } else {
        cout << "\nCalculated Piece:" << "\" \" ";
    }
}