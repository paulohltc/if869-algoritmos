#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define br "\n"
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

ll mySum(ll &a, ll& b){
  return a+b;
}

ll myMin(ll &a, ll &b)
{
  return a < b ? a : b;
}

ll myMax(ll &a, ll &b){
  return a > b ? a : b;
}

ll seed;
struct Rng
{
  ll A = 1664525, C = 1013904223, R = pow(2, 32), rnd = -1;
  ll next()
  {
    if (rnd == -1)
    {
      rnd = seed;
    }
    else
    {
      rnd = (A * rnd + C) % R;
    }
    return rnd;
  }
};
map<string,ll(*)(ll &, ll &)> func = {
  {"MIN",&myMin},
  {"MAX",&myMax},
  {"SUM",&mySum}
};

class SparseTable{
  public:
  ll (*f)(ll &, ll &); // pointer to funcion
  int m,n;
  vector<vector<ll>> table;
  SparseTable(int size, string& op){
    f = func[op];
    n = size;
    m = floor(log2(n))+ 1;
    table.resize(m, vector<ll>(n,0));
  }

  void preprocess(vector<int>& firstRow){
    for(int i = 0; i < n; i++){
      table[0][i] = firstRow[i];
    }
    int k = 1;
    for(int i = 1; i < m; i++){
      for(int j = 0; j < n; j++){
        if(j + k < n){
          table[i][j] = f(table[i-1][j], table[i-1][j+k]);
        }
        else{
          table[i][j] = table[i-1][j];
        }
      }
      k *= 2;
    }
  }

  void debug(){
    for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
        cout << table[i][j] << "\t";
      }
      cout << br;
    }
  }


  ll range_query(int l, int r){
    ll ans = LONG_LONG_MIN;
    bool first = 1;
    while(l < r){
      int i = floor(log2(r-l));
      if(first){
        first = 0;
        ans = table[i][l];
      }
      else{
        ans = f(ans,table[i][l]);
      }
      l = l + (1 << i);
    }
    return ans;
  }

  ll update(int pos, ll val){
    table[0][pos] = val;
    int k = 1;
    for(int i = 1; i < m; i++){
      int l = max(pos - 2*k + 1,0);
      for(; l <= pos; l++){
        table[i][l] = f(table[i-1][l], table[i-1][l+k]);
      }
      k = 2*k;
    }
    return range_query(pos,n);
  }
};


int main()
{
  io;
  int n,o,q,u;
  string f;
  int caso = 0;
  while(cin >> seed >> n >> f >> o >> q >> u){
    SparseTable st = SparseTable(n,f);
    Rng RNG;
    int m = 4*n;
    cout << "caso " << caso << br;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
      nums[i] = RNG.next() % m;
    }
    st.preprocess(nums);
    while(o--){
      ll x = RNG.next();
      if(x % (q+u) < q){
        int l = RNG.next() % n;
        int r = l + 1 + (RNG.next() % (n-l));
        cout << st.range_query(l,r) << br;
      }
      else{
        int i = RNG.next() % n;
        ll v = RNG.next() % m;
        cout << st.update(i,v) << br;
      }
    }
    caso++;
    cout << br;
  }
}