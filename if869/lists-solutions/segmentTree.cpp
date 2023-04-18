#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define br "\n"
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

ll mySum(ll &a, ll& b){return a + b;} 
ll myMin(ll &a, ll &b){return a < b ? a : b;}
ll myMax(ll &a, ll &b){return a > b ? a : b;}

map<string,ll(*)(ll &, ll &)> mpFunc = {{"MIN",&myMin},{"MAX",&myMax},{"SUM",&mySum}};
map<string,ll> mpNeutro = {{"MIN",LLONG_MAX}, {"MAX",-1},{"SUM",0}};

string F;
ll seed,N,W,Q,U,P,M;

struct Rng{
  ll A = 1664525, C = 1013904223, R = (1LL << 32), rnd = -1;
  ll next(){
    if (rnd == -1) rnd = seed;
    else rnd = (A * rnd + C) % R;
    return rnd;
  }
};
Rng RNG;

class SegTree{
    public:
    ll n;
    ll (*f)(ll &, ll &); // pointer to funcion
    ll neutro;
    vector<ll> T; // 1-indexado

    SegTree(ll size, const string& op, const vector<ll>& x){
      n = size;
      f = mpFunc[op];
      neutro = mpNeutro[op];
      build(x);        
    }
    void build(const vector<ll>& x){
      T.resize(2*n + 1,0);
      for(ll i = 0; i < n; i++) 
        T[i+n] = x[i]; // raizes
      for(ll i = n-1; i >= 1; i--)
        T[i] = f(T[2*i],T[2*i + 1]); // merge bottom up           
    }

    void update(ll pos, ll val){
      pos = pos+n;
      T[pos] = val;
      pos >>= 1;
      while(pos >= 1){
        T[pos] = f(T[2*pos],T[2*pos+1]);
        pos >>= 1;
      }
    }

    ll range_query(ll l, ll r){
      ll left = n+l, right = n+r;
      ll ans = neutro;
      while(left < right){
        if(left & 1){
          ans = f(ans,T[left]);
          left++;
        }
        if(right & 1){
          right--;
          ans = f(ans,T[right]);
        }
        left >>= 1;
        right >>= 1;
      }
      return ans;
    }

};


int main(){
  io;
  int caso = 0;
  while(cin >> seed >> N >> F >> W >> Q >> U >> P){
    M = 4*N;
    cout << "caso " << caso << br;
    caso++;
    vector<ll> nums(N);
    for(int i = 0; i < N; i++) nums[i] = RNG.next() % M;
    // cout << "NUMS" << br;
    // for(int i = 0; i < N; i++){
    //   cout << nums[i] << " ";
    // }
    // cout << br;
    SegTree seg = SegTree(N,F,nums);
  
    for(int j = 0; j < W; j++){
        ll x = RNG.next();
        if(x % (Q+U) < Q){
          ll L = RNG.next() % N;
          ll R = L + 1 + (RNG.next() % (N-L));
          ll ans = seg.range_query(L,R);
          if(j % P == 0) cout << ans << br;
        }
        else{
          ll I = RNG.next() % N;
          ll V = RNG.next() % M;
          seg.update(I,V);
          ll ans = seg.range_query(I,N);
          // cout << "RANGE I:N = " << ans << br;
          if(j % P == 0) cout << ans << br;
        }
    }
    cout << br;
    RNG.rnd = -1;
  }
}