/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)

int K;

int solve(string s) {
    //cerr << s << endl;
    int n = s.size();
    vector<int> iron, magnets;
    forn(i, n) {
        if(s[i] == 'M') {
            magnets.push_back(i);
        }
        if(s[i] == 'I') {
            iron.push_back(i);
        }
    }
    if(magnets.empty() || iron.empty()) {
        return 0;
    }

    vector<int> pre(n+1);
    forn(i, n) {
        pre[i+1] = pre[i] + (s[i] == ':');
    }
    
    int N = iron.size();
    int M = magnets.size();
    int j = 0;
    
    vector<int> left(M), right(M);
    
    auto eval = [&](int l, int r) {
        if(l > r) {
            swap(l, r);
        }
        return K + 1 - (r - l) - (pre[r+1] - pre[l]);
    };
    
    forn(idx, M) {
        int i = magnets[idx];
        while(j < N && iron[j] < i && eval(i, iron[j]) <= 0) {
            j++;
        }
        left[idx] = j;
    }
    
    j = N-1;
    ford(idx, M) {
        int i = magnets[idx];
        while(j >= 0 && iron[j] > i && eval(i, iron[j]) <= 0) {
            j--;
        }
        right[idx] = j;
    }
    
    vector<pair<int,int>> ivs;
    forn(i, M) {
        if(left[i] <= right[i]) {
            ivs.emplace_back(left[i], right[i]);
        }
    }
    sort(ivs.begin(), ivs.end());
    
    int ans = 0;
    int l = 0;
    fore(iv, ivs) {
        if(l <= iv.second) {
            ans++;
            l++;
        }
        l = max(l, iv.first + 1);
    }
    return ans;
}

void tc() {
    int n;
    cin >> n >> K;
    string s = "X";
    {
        string tmp;
        cin >> tmp;
        s += tmp;
        s += 'X';
    }
    n = s.size();
    int ans = 0;
    int prev = -1;
    forn(i, n) {
        if(s[i] == 'X') {
            if(prev == -1) {
                prev = i;
            }
            else {
                ans += solve(s.substr(prev+1, i - prev - 1));
                prev = i;
            }
        }
    }
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--) {
        tc();
    }
}
