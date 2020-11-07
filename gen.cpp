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
    int t = 1;
    cout << t << "\n";
    while(t--) {
        int n = r(1, 5);
        cout << n << "\n";
        set<int> seen;
        for(int i = 0; i < n; i++) {
            int x;
            do {
                x = r(1, 2*n);
            } while(seen.count(x));
            seen.insert(x);
            cout << x << " ";
        }
        cout << "\n";
        int Q = r(1, 5);
        cout << Q << "\n";
        for(int i = 0; i < Q; i++) {
            cout << r(1, 2*n) << "\n";
        }
    }
}
