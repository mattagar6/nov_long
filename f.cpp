/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)

const int nax = 1005;
const int B = 20;
const int inf = 1e9+5;

int answer[nax][nax], a[nax], nxt[B][nax];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, Q, S;
    cin >> n >> Q >> S;
    assert(n < nax); // subtask 1 only :(
    forn(i, n) {
        cin >> a[i];
    }
    a[n] = inf;
    nxt[0][n] = n;
    stack<int> stk;
    stk.push(n);
    ford(i, n) {
        while(a[stk.top()] <= a[i]) {
            stk.pop();
        }
        nxt[0][i] = stk.top();
        stk.push(i);
    }

    for(int i = n; i >= 0; i--) {
        for(int j = 1; j < B; j++) {
            nxt[j][i] = nxt[j-1][nxt[j-1][i]];
        }
    }
    
    for(int R = n-1; R >= 0; R--) {
        int best = 0;
        for(int L = R; L >= 0; L--) {
            int i = L;
            int cur = 0;
            for(int b = B-1; b >= 0; b--) {
                if(nxt[b][i] <= R) {
                    cur += 1<<b;
                    i = nxt[b][i];
                }
            }
            best = max(best, cur+1);
            answer[L][R] = best;
        }
    }
    int last = 0;
    while(Q--) {
        int x, y;
        cin >> x >> y;
        int L = (x + S * last - 1) % n;
        int R = (y + S * last - 1) % n;
        if(L > R) {
            swap(L, R);
        }
        last = answer[L][R];
        cout << last << "\n";
    }
}
