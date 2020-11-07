/*  
 *  Author: blondie 
 */
  
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define ford(i, n) for(int i = int(n)-1; i >= 0; i--)
#define fore(x, v) for(const auto& x : v)

namespace modular {
   const int mod = 1e9+7;
   // const int mod = 998244353;

   inline int add(int a, int b) {
      a += b;
      while(a >= mod) a -= mod;
      while(a < 0) a += mod;
      return a;
   }
   inline void add_self(int& a, int b) {
      a = add(a, b);
   }
   inline int mul(int a, int b) {
      return 1LL * a * b % mod;
   }
   inline void mul_self(int& a, int b) {
      a = mul(a, b);
   }
   inline int mpow(int a, int n) {
      int res = 1;
      while(n > 0) {
        if(n & 1) {
           res = mul(res, a);
        }
        a = mul(a, a);
        n >>= 1;
      }
      return res;
   }
   inline int divide(int a, int b) {
      assert(b != 0);
      return mul(a, mpow(b, mod-2));
   }

   const int mxN = 200*1000+5;
   int fact[mxN], finv[mxN];

   inline int binomial(int n, int k) {
      return mul(fact[n], mul(finv[n-k], finv[k]));
   }
   
   inline void init_fact() {
      fact[0] = finv[0] = 1;
      for(int i = 1; i < mxN; i++) {
         fact[i] = mul(i, fact[i-1]);
         finv[i] = mpow(fact[i], mod-2);
      }
   }
}

using namespace modular;

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
    vector<int> pre(n+1);
    for(int i = 0; i < n; i++) {
        pre[i+1] = add(pre[i], a[i] - (i < n-1 && a[i] % 2 == 1));
    }
    
    vector<int> taken_even(n);
    if(one_pos < n-1 && one_pos > 0) {
        for(int i = 0; i < n; i++) {
            if(i+1 == one_pos) {
                pre[i+1] = add(pre[i], (a[i] % 2 ? a[i] : a[i]-1));
            }
            else {
                pre[i+1] = add(pre[i], a[i] - (i < n-1 && a[i] % 2 == 1));
                if(i < n-1 && a[i] % 2 == 1) {
                    taken_even[i] = 1;
                }
            }
        }
    }
    
    int Q;
    cin >> Q;
    
    while(Q--) {
        long long R;
        cin >> R;
        if(one_pos >= n-1) {
            cout << add(add(mul((R / n) % mod, pre[n] - (a[n-1] % 2 == 0)), R >= n && a[n-1] % 2 == 0),
                        add(pre[R % n], (R % n > 0 && a[R % n - 1] % 2))) << "\n";
        }
        else if(one_pos == 0) {
            // not sure yet...
            cout << ((R+n-1)/n) % mod << "\n";
        }
        else {
            cout << add(add(mul((R / n) % mod, pre[n] - (a[n-1] % 2 == 0)), R >= n && a[n-1] % 2 == 0),
                        add(pre[R % n], (R % n > 0 && taken_even[R % n - 1]))) << "\n";
        }
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
