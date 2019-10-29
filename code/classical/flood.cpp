/*
7 7
AXXXX..
X...X..
X.XXXXX
X.X.X.X
XXXXX.X
..X...X
..XXXXB

A B    A intersect B
5 5          1

*/
#include <iostream>
#include <vector>
using namespace std;

const int MAXS = 1000;

vector<vector<int>> DIR = {{1, 0}, {-1, 0} ,{0, 1} , {0, -1}};

char graph[MAXS+2][MAXS+2];

inline bool isIntersection(int r, int c){
    return (graph[r][c] == 'X' 
        && graph[r+1][c] == 'X' 
        && graph[r-1][c] == 'X' 
        && graph[r][c+1] == 'X' 
        && graph[r][c-1] == 'X');
}

int flood(int r, int c, char mark, int nrows, int ncols){
    if (graph[r][c] != '.') return 0;
    graph[r][c] = mark;
    int count = 1;
    if (r > 0)
        count += flood(r-1, c, mark, nrows, ncols);
    if (r < nrows-1)
        count += flood(r+1, c, mark, nrows, ncols);
    if (c > 0)
        count += flood(r, c-1, mark, nrows, ncols);
    if (c < ncols-1)
        count += flood(r, c+1, mark, nrows, ncols);
    return count;
}

void findstart(int&r, int& c, char mark, int n, int m){
    int x, y;
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) {
        if (graph[i][j] != mark) continue;
        for (auto &txy: DIR) {
            x = txy[0]; y = txy[1];
            if (graph[i+x][j+y] == '.' && graph[i-x][j-y] == '*') {
                r = i+x;
                c = j+y;
                return;
            }
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;

    int ax, ay, bx, by;
    int edges = 0;

    // extra side helper
    for (int j=0; j<m+2; j++)
        graph[0][j] = graph[n+1][j] = '.';
    for (int i=1; i<=n; i++) 
        graph[i][0] = graph[i][m+1] = '.';

    for (int i=1; i<=n; i++) for (int j=1; j<=m; j++){
        cin >> graph[i][j];
        if (graph[i][j] == 'A'){ // mark 'A' coordinate
            ax = i; ay = j;
        }else if (graph[i][j] == 'B'){ // mark 'B' coordinate
            bx = i; by = j;
        }
        if (graph[i][j] != '.') edges++;
    }
    
	// set intersections
    for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) 
        if (isIntersection(i,j)) graph[i][j] = 'I';

    // fill edge connected to 'A'
    int r=ax, c=ay;
    bool done = false;
    int x, y;
    while(!done) {
        graph[r][c] = 'A';
        done = true;
        for (auto &txy: DIR) { 
            x = txy[0]; y = txy[1];
            if (graph[r+x][c+y] == 'X' || graph[r+x][c+y] == 'I'){
                if (graph[r+x][c+y] == 'I') {
                    graph[r+x][c+y] = 'O';
                    r = r + 2*x;
                    c = c + 2*y;
                }else{
                    r = r + x;
                    c = c + y;
                }
                done = false;
                break;
            }
        }
    }
    
	// set remaining edge to 'B'
    for (int i=1; i<=n; i++) for (int j=1; j<=m; j++)
        if (graph[i][j] == 'X') graph[i][j] = 'B';
    
	// fill exterior '*' from (0,0)
    int exterior = flood(0, 0, '*', n+2, m+2);
    exterior -= 2*(n+m+2);
    
	// fill A area
    findstart(r, c, 'A', n, m);
    int anum = flood(r, c, 'a', n+2, m+2);
    // fill B area
    findstart(r, c, 'B', n, m);
    int bnum = flood(r, c, 'b', n+2, m+2);
    int abnum = n*m - edges - exterior - anum - bnum;
    
	cout << anum << ' ' << bnum << ' ' << abnum << endl;
    return 0;
}

