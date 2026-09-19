#include <iostream>
using namespace std;

const int ROWS = 7;
const int COLS = 7;

char maze[ROWS][COLS] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', 'S', '#', '.', '.', '.', '#'},
    {'#', '.', '#', '.', '#', 'G', '#'},
    {'#', '.', '.', '.', '#', '.', '#'},
    {'#', '#', '#', '.', '.', '.', '#'},
    {'#', 'X', '.', '.', 'F', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

void printMaze() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            cout << maze[r][c] << ' ';
        }
        cout << endl;
    }
}

int main() {
    printMaze();
    return 0;
}