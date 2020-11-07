/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)

const int nax = 505;

int grid[nax][nax], X[nax*nax], Y[nax*nax], L[nax*nax], R[nax*nax], n, K;
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};


bool ok(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> K;
    forn(i, K) {
        cin >> X[i] >> Y[i] >> L[i] >> R[i];
        --X[i], --Y[i];
    }
    
}
