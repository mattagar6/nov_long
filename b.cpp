/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)

const int nax = 4e6+1;

vector<int> primes;
bool ok[nax];

void tc() {
    int n;
    cin >> n;
    vector<int> b(n);
    forn(i, n) {
        cin >> b[i];
        --b[i];
    }
    vector<int> a(n);
    int j = 0;
    forn(i, n) {
        if(b[i] == i) {
            a[i] = primes[j++];
        }
    }
    forn(i, n) {
        if(b[i] != i) {
            a[i] = a[b[i]];
        }
    }
    forn(i, n) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    for(int i = 2; i < nax; i++) {
        if(!ok[i]) {
            primes.push_back(i);
            for(int j = 2*i; j < nax; j += i) {
                ok[j] = 1;
            }
        }
    }
    cerr << primes.size() << endl;
    
    int t;
    cin >> t;
    while(t--) {
        tc();
    }
}
