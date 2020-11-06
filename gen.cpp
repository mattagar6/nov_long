/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)

const int nax = 300'005;

vector<int> g[nax], at[nax];
int D = 0;

void dfs(int u, int d) {
    at[d].push_back(u);
    D = max(D, d);
    fore(v, g[u]) {
        //cerr << "(" << u << ", " << v << ")\n";
        dfs(v, d+1);
    }
}

int r(int a, int b) {
    assert(a <= b);
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    srand(atoi(argv[1]));
    int n = r(2, 100*1000);
    int Q = r(2, 100*1000);
    cout << n << " " << Q << "\n";
    forn(i, n) {
        cout << r(1, 10) << " ";
    }
    cout << "\n";
    for(int i = 2; i <= n; i++) {
        int p = r(1, i-1);
        //int p = i-1;
        g[p].push_back(i);
        cout << p << " " << i << "\n";
    }
    dfs(1, 0);
    //cerr << D << endl;
    //exit(0);
    for(int i = 0; i < Q; i++) {
        int level = r(0, D);
        assert(!at[level].empty());
        int m = at[level].size();
        int a = r(0, m-1), b = r(0, m-1);
        cout << at[level][a] << " " << at[level][b] << "\n";
    }
}
