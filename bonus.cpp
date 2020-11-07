/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;


#define ris   return *this
#define tmplt template<class T
#define dbgo  debug& operator<<
tmplt > struct rge { T b, e; };
tmplt > rge<T> range(T i, T j) { return rge<T>{i, j}; }
struct debug {
#ifdef LOCAL
~debug(){cerr<<endl;}
tmplt > dbgo(T x){cerr<<boolalpha<<x;ris;}
tmplt, class C > dbgo(pair<T, C> x){ris<<"("<<x.first<<", "<<x.second<<")";}
tmplt > dbgo(rge<T> x){*this<<"[";for(auto it=x.b;it!=x.e;it++){*this<<", "+2*(it==x.b)<<*it;}ris<<"]";}
tmplt > dbgo(vector<T> x){ris<<range(x.begin(),x.end());}
#else
tmplt > dbgo(const T&){ris;}
#endif
};
#define nav(...) << "[ " << #__VA_ARGS__ ": " << (__VA_ARGS__) << " ] "

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)

using T = pair<int,int>;

const int nax = 505;
const int LIM = 64;

int grid[nax][nax], X[nax*nax], Y[nax*nax], L[nax*nax], R[nax*nax], n, K;
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

vector<int> g[nax*nax];
vector<int> on_row[nax];

bool ok(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    cin >> n >> K;
    for(int i = 1; i <= K; i++) {
        cin >> X[i] >> Y[i] >> L[i] >> R[i];
        --X[i], --Y[i];
        grid[X[i]][Y[i]] = i;
        on_row[X[i]].push_back(Y[i]);
    }
    forn(i, n) {
        sort(on_row[i].begin(), on_row[i].end());
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!grid[i][j]) {
                continue;
            }
            int me = grid[i][j];
            for(int r = max(0, i - LIM); r < min(n, i + LIM); r++) {
                fore(c, on_row[r]) {
                    if(c == j) {
                        continue;
                    }
                    if((r - i) + abs(c - j) <= R[me]) {
                        g[me].push_back(grid[r][c]);
                    }
                }
            }
        }
    }
    
    
    
    cerr << "DONE\n";
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000 << " [ms]" << std::endl;
}
