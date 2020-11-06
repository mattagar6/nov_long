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

const int nax = 300'005;

vector<int> g[nax];
vector<pair<int,int>> tour;
int p[nax], depth[nax], in[nax];
uint32_t w[nax], ans[nax], val[nax];

map<pair<int,int>,vector<int>> queries;
map<pair<int,int>, uint32_t> res;

void dfs(int u, uint32_t sofar) {
    static int T = 0;
    in[u] = T++;
    tour.emplace_back(depth[u], u);
    sofar += w[u]*w[u];
    val[u] = sofar;
    fore(v, g[u]) {
        if(v != p[u]) {
            p[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v, sofar);
            tour.emplace_back(depth[u], u);
            T++;
        }
    }
    
}

inline vector<int> get(int u, int STOP) {
    vector<int> a;
    while(u != STOP) {
        a.push_back(u);
        u = p[u];
    }
    reverse(a.begin(), a.end());
    return a;
}

int msb(int n) {
   return 31 - __builtin_clz(n);
}

template<typename T>
struct SparseTable {
   int n;
   vector<vector<T>> tab;
   void build(vector<T> a) {
      n = a.size();
      int B = msb(n) + 1;
      tab.resize(B);
      for(int b = 0; b < B; b++) {
         tab[b].resize(n);
         int len = 1<<b;
         for(int i = 0; i <= n-len; i++) {
            if(len == 1) {
               tab[b][i] = a[i];
            }
            else {
               tab[b][i] = min(tab[b-1][i], tab[b-1][i+len/2]);
            }
         }
      }
   }
   T get(int L, int R) const {
      int b = msb(R - L + 1);
      return min(tab[b][L], tab[b][R-(1<<b)+1]);
   }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(p, -1, sizeof p);
    
    int n, Q;
    cin >> n >> Q;
    forn(i, n) {
        cin >> w[i];
    }
    forn(i, n-1) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    dfs(0, 0);
    //debug() nav(tour);
    SparseTable<pair<int,int>> lca;
    lca.build(tour);
    
    vector<pair<int,int>> todo;
    forn(i, Q) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        if(in[a] > in[b]) {
            swap(a, b);
        }
        todo.emplace_back(a, b);
        queries[make_pair(a, b)].push_back(i);
    }
    //exit(0);
    sort(todo.begin(), todo.end(), [&](auto a, auto b) {
        return make_pair(-depth[a.first], a) < make_pair(-depth[b.first], b);
    });
    todo.resize(unique(todo.begin(), todo.end())-todo.begin());
    
    fore(q, todo) {
        int a, b;
        tie(a, b) = q;
        if(res.count(q)) {
            continue;
        }
        //#warning TODO get lca sparse table
        int LCA = lca.get(in[a], in[b]).second;
        //cerr << a << " " << b << " " << LCA << endl;
        vector<int> pa = get(a, LCA);
        vector<int> pb = get(b, LCA);
        
        int N = pa.size();
        uint32_t cur = val[LCA];
        
        forn(i, N) {
            int x = pa[i], y = pb[i];
            cur += w[x] * w[y];
            if(res.count(make_pair(x, y))) {
                res[{x, y}] = cur;
            }
        }
        
        res[q] = cur;
    }
    
    fore(pp, res) {
        fore(i, queries[pp.first]) {
            ans[i] = pp.second;
        }
    }
    
    forn(i, Q) {
        cout << ans[i] << "\n";
    }
}
