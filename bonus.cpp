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

struct S {
    int x, y;
    string path;
    void pr() const {
        cout << x << " " << y << " " << path << "\n";
    }
};

const int nax = 505;
const int LIM = 64;
const int MAGIC = 2;

int grid[nax][nax], X[nax*nax], Y[nax*nax], L[nax*nax], R[nax*nax], n, K;
T par[nax][nax];
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};
const string dir = "ULRD";
set<int> done;
vector<S> ans;

vector<int> g[nax*nax];
vector<int> on_row[nax];

bool ok(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < n;
}

void BFS(int r, int c) {
    vector<T> q;
    set<T> seen;
    q.emplace_back(r, c);
    seen.emplace(r, c);
    int me = grid[r][c];
    for(int i = 0, d = 1; i < (int) q.size() && d <= R[me]; d++) {
        int sz = q.size();
        for(; i < sz; i++) {
            int row, col;
            tie(row, col) = q[i];
            if(grid[row][col] > 0 && grid[row][col] != me) {
                int you = grid[row][col];
                T DONE = {r, c};
                T cur = q[i];
                string path;
                
                while(cur != DONE) {
                    T prev = par[cur.first][cur.second];
                    grid[prev.first][prev.second] = -1;
                    bool found = 0;
                    forn(k, 4) {
                        if(prev.first+dr[k] == cur.first && prev.second+dc[k] == cur.second) {
                            path += dir[k];
                            found = 1;
                            break;
                        }
                    }
                    assert(found);
                    cur = prev;
                }
                reverse(path.begin(), path.end());
                ans.push_back(S{me, you, path});
                done.insert(me);
                done.insert(you);
                return;
            }
            forn(k, 4) {
                int nr = row + dr[k], nc = col + dc[k];
                if(!ok(nr, nc) || seen.count({nr, nc})) {
                    continue;
                }
                if(grid[nr][nc] == 0) {
                    q.emplace_back(nr, nc);
                    seen.emplace(nr, nc);
                    par[nr][nc] = q[i];
                }
                else if(grid[nr][nc] > 0 && !done.count({grid[nr][nc]})) {
                    int you = grid[nr][nc];
                    int low = max(L[you], L[me]), high = min(R[you], R[me]);
                    if(low <= d+1 && d+1 <= high) {
                        q.emplace_back(nr, nc);
                        seen.emplace(nr, nc);
                        par[nr][nc] = q[i];
                    }
                }
            }
        }
    }
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
    //forn(i, n) {
        //sort(on_row[i].begin(), on_row[i].end());
    //}
    
    forn(i, n) {
        forn(j, n) {
            if(grid[i][j] > 0 && !done.count(grid[i][j])) {
                //cerr << grid[i][j] << endl;
                BFS(i, j);
            }
        }
    }
    
    
    //for(int i = 0; i < n; i++) {
        //for(int j = 0; j < n; j++) {
            //if(!grid[i][j]) {
                //continue;
            //}
            //int me = grid[i][j];
            //for(int r = max(0, i - LIM); r < min(n, i + LIM+1); r++) {
                //fore(c, on_row[r]) {
                    //if(r == i && c == j) {
                        //continue;
                    //}
                    //int dist = (r - i) + abs(c - j);
                    //if(L[me] - MAGIC <= dist && dist <= R[me]) {
                        //g[me].push_back(grid[r][c]);
                    //}
                //}
            //}
        //}
    //}
    
    //for(int i = 1; i <= K; i++) {
        //assert(!g[i].empty());
        //sort(g[i].begin(), g[i].end());
    //}
    
    int cnt = ans.size();
    cerr << fixed << setprecision(2);
    cerr << "Score: " << pow((double) cnt / (K / 2), 4) << endl;
    
    #ifndef LOCAL
        cout << ans.size() << "\n";
        fore(s, ans) {
            s.pr();
        }
    #endif
    
    cerr << "DONE\n";
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000 << " [ms]" << std::endl;
}
