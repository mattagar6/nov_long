/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)

pair<int,int> expo(const vector<int>& a, int turn, int pos, long long rem) {
    if(rem == 0) {
        return make_pair(0, 0);
    }
    
    int n = a.size();
    pair<int,int> x = expo(a, turn^(pos+1==n)^1, (pos+1)%n, rem-1); // take an odd guy
    if(pos+1 != n) {
        swap(x.first, x.second);
    }
    x.first += a[pos] - (a[pos] % 2 == 0);
    pair<int,int> y = {-1, 1};
    if(a[pos] > 1) {
        y = expo(a, turn^(pos+1==n), (pos+1)%n, rem-1);
        if(pos+1 == n) {
            swap(y.first, y.second);
        }
        
        y.first += a[pos] - (a[pos] % 2);
    }
    if(x.first > y.first) {
        return x;
    }
    else {
        return x.second < y.second ? x : y;
    }
    
}

void tc() {
    int n;
    cin >> n;
    vector<int> a(n);
    int one_pos = n;
    forn(i, n) {
        cin >> a[i];
        if(a[i] == 1) {
            assert(one_pos == n);
            one_pos = i;
        }
    }
    
    
    int Q;
    cin >> Q;
    
    while(Q--) {
        long long R;
        cin >> R;
        cout << expo(a, 0, 0, R).first << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    // at most one 1
    
    int t;
    cin >> t;
    while(t--) {
        tc();
    }
}
