#include <iostream>
#include <queue>
#include <string>
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

int startRow, startCol;
int flagRow, flagCol;
int goalRow, goalCol;
int robotRow, robotCol;
bool hasFlag = false;
int stepCount = 0;

void printMaze() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (r == robotRow && c == robotCol) {
                cout << 'R' << ' ';
            } else if (maze[r][c] == 'F' && hasFlag) {
                cout << '.' << ' ';
            } else {
                cout << maze[r][c] << ' ';
            }
        }
        cout << endl;
    }
}

void findPositions() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (maze[r][c] == 'S') { startRow = r; startCol = c; }
            if (maze[r][c] == 'F') { flagRow = r; flagCol = c; }
            if (maze[r][c] == 'G') { goalRow = r; goalCol = c; }
        }
    }
}

bool isSafe(int r, int c) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return false;
    if (maze[r][c] == '#' || maze[r][c] == 'X') return false;
    return true;
}

const int dRow[4] = {-1, 1, 0, 0};
const int dCol[4] = {0, 0, -1, 1};
const string dirName[4] = {"UP", "DOWN", "LEFT", "RIGHT"};

void printPath(int path[], int length) {
    for (int i = 0; i < length; i++) {
        cout << dirName[path[i]];
        if (i < length - 1) cout << ", ";
    }
    cout << endl;
}

void walk(int path[], int length) {
    for (int i = 0; i < length; i++) {
        int d = path[i];
        robotRow += dRow[d];
        robotCol += dCol[d];
        stepCount++;

        cout << "STEP " << stepCount << " - MOVE " << dirName[d]
                << " - POSITION (" << robotRow << "," << robotCol << ")" << endl;
        printMaze();
        cout << endl;
    }
}

int findPath(int fromRow, int fromCol, int toRow, int toCol, int path[]) {
    bool visited[ROWS][COLS] = {};
    int prevRow[ROWS][COLS];
    int prevCol[ROWS][COLS];
    int prevDir[ROWS][COLS];

    queue<int> rowQueue;
    queue<int> colQueue;
    rowQueue.push(fromRow);
    colQueue.push(fromCol);
    visited[fromRow][fromCol] = true;

    while (!rowQueue.empty()) {
        int r = rowQueue.front();
        int c = colQueue.front();
        rowQueue.pop();
        colQueue.pop();

        if (r == toRow && c == toCol) break;

        for (int d = 0; d < 4; d++) {
            int nr = r + dRow[d];
            int nc = c + dCol[d];
            if (!isSafe(nr, nc) || visited[nr][nc]) continue;

            visited[nr][nc] = true;
            prevRow[nr][nc] = r;
            prevCol[nr][nc] = c;
            prevDir[nr][nc] = d;
            rowQueue.push(nr);
            colQueue.push(nc);
    }
}

    if (!visited[toRow][toCol]) return -1;

    int length = 0;
    int r = toRow;
    int c = toCol;
    while (r != fromRow || c != fromCol) {
        int pr = prevRow[r][c];
        int pc = prevCol[r][c];
        r = pr;
        c = pc;
        length++;
    }

    r = toRow;
    c = toCol;
    for (int i = length - 1; i >= 0; i--) {
        path[i] = prevDir[r][c];
        int pr = prevRow[r][c];
        int pc = prevCol[r][c];
        r = pr;
        c = pc;
    }
    return length;
}

int main() {
    printMaze();
    findPositions();
    int pathToFlag[ROWS * COLS];
    int pathToBase[ROWS * COLS];
    int lengthToFlag = findPath(startRow, startCol, flagRow, flagCol, pathToFlag);
    int lengthToBase = findPath(flagRow, flagCol, goalRow, goalCol, pathToBase);

    if (lengthToFlag < 0 || lengthToBase < 0) {
        cout << "MISSION FAILED" << endl;
        return 0;
    }

    cout << "PATH TO FLAG   : ";
    printPath(pathToFlag, lengthToFlag);
    printMaze();
    cout << endl;
    walk(pathToFlag, lengthToFlag);

    hasFlag = true;
    cout << "FLAG CAPTURED  : (" << robotRow << "," << robotCol << ")" << endl;
    cout << "PATH TO BASE   : ";
    printPath(pathToBase, lengthToBase);
    walk(pathToBase, lengthToBase);

    cout << "BASE REACHED   : (" << robotRow << "," << robotCol << ")" << endl;
    cout << "MISSION COMPLETE" << endl;
    cout << "TOTAL MOVES    : " << stepCount << endl;
    return 0;
}