/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        forn(i, n) {
            cin >> a[i];
        }
        int ans = 100;
        forn(s, 1<<n) {
            int x = 0, y = 0;
            forn(i, n) {
                if(s>>i&1) {
                    x += a[i];
                }
                else {
                    y += a[i];
                }
            }
            ans = min(ans, max(x, y));
        }

        
        cout << ans << "\n";
    }
}
