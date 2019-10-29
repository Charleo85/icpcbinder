//https://open.kattis.com/problems/thathanoi
// num of step to complete hanoi state otherwise output no
#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 50;
int loc[MAX+1];

bool count(int start, int dest, int work, int disk, long long moves, long long& ans)
{
    if (disk == 0)
        return true;
    else if (loc[disk] == dest) {
        if (!count(work, dest, start, disk-1, moves/2, ans))
            return false;
        ans += moves;
        return true;
    }
    else if (loc[disk] == start) {
        if (!count(start, work, dest, disk-1, moves/2, ans))
            return false;
        return true;
    }
    else
        return false;
}

int main()
{
    int n=0;

    long long moves = 1;
    bool valid = true;
    for(int i=0; i<3; i++) {
        int m;
        cin >> m;
        n += m;
        int prev = MAX+1;
        for(int j=0; j<m; j++) {
            int disk;
            cin >> disk;
            loc[disk] = i;
            moves *=2;
            if (disk > prev)
                valid = false;
            prev = disk;
        }
    }
    long long ans = 0;
    if (!valid || !count(0, 2, 1, n, moves/2, ans))      // moves = 2^n
        cout << "No" << endl;
    else
        cout << moves-1-ans << endl;
}
