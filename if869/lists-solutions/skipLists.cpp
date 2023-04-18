#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define br "\n"
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

ll seed;
struct Rng{
  ll A = 1664525, C = 1013904223, R = pow(2, 32), rnd = -1;
  ll next(){
    if (rnd == -1) return rnd = seed;
    else return rnd = (A * rnd + C) % R;
  }
};
Rng RNG;
class Node{
    public:
    ll val;
    int H;
    vector<Node*> next;
    Node(ll num, int height){
        val = num;
        H = height;
        next.resize(H,NULL);
    }
    Node(int height){
      val = LONG_LONG_MIN;
      H = height;
      next.resize(H,NULL);
    }
};


class SkipList{
  public:
  Node* head;
  int height;
  SkipList(){
    height = 1;
    head = new Node(1);
  }

  ll random_height(){
    ll h = 1;
    while((RNG.next() % 100LL) < 50LL && h < height + 1){
      h++;
    }
    return h;
  }
  vector<Node*> precursors(ll key, ll& cnt){
    vector<Node*> P(height,NULL);
    Node* curr = head;
    cnt = 1;
    for(int l = height-1; l >= 0; l--){
      while(curr->next[l] != NULL && curr->next[l]->val < key){
        P[l] = curr;
        curr = curr->next[l];
        cnt++;
      }
      P[l] = curr;
    }
    return P;
  }

  pair<int,int> search(ll key){
    ll cnt = 0;
    vector<Node*> P = precursors(key,cnt);
    if(P[0]->next[0] != NULL && P[0]->next[0]->val == key){
      int h = P[0]->next[0]->H;
      return {cnt,h};
    }
    else{
      return {cnt,0};
    }
  }

  bool insert(ll key){
    ll cnt = 0;
    vector<Node*> P = precursors(key,cnt);
    if(P[0]->next[0] != NULL && P[0]->next[0]->val == key){
      return 0;
    }
    ll h = random_height();
    // cout << "h:" << h << " key:" << key << br;
    if(h > height){
      for(int i = height; i < h; i++){
        head->next.push_back(NULL);
        head->H++;
        P.push_back(head);
      }
      height = h;
    }
    Node* n = new Node(key,h); 
    for(int l = 0; l < h; l++){
      n->next[l] = P[l]->next[l];
      P[l]->next[l] = n;
    }
    return 1;
  }

  bool remove(ll key){
    ll cnt = 0;
    vector<Node*> P = precursors(key,cnt);
    if(P[0]->next[0] == NULL || P[0]->next[0]->val != key){
      return 0;
    }
    Node* n = P[0]->next[0];
    for(int l = 0; l < n->H; l++){
      P[l]->next[l] = n->next[l];
    }
    while(height > 1 && head->next[height-1] == NULL){
      height--;
    }
    return 1;
  }

};
ll U,B,N,F,I,D,P;
#define X first
#define Y second
int main(){
  io;
  cin >> seed;
  cin >> U >> B >> N >> F >> I >> D >> P;
  SkipList sl = SkipList();
  while(B--){ // burn-in
    ll num = RNG.next() % U;
    sl.insert(num);
  }
  for(int j = 0; j < N; j++){
    ll x =  RNG.next() % (F+I+D);
    ll y = RNG.next() % U;
    if(x < F){ // find
      if(j % P == 0){
        pair<int,int> ans = sl.search(y);
        cout << "F " << ans.X << " " << ans.Y << br;
      }
    }
    else if(x < (F+I)){ // insert
      bool b = sl.insert(y);
      if(j % P == 0){
        cout << "I " << b << br;
      }
    }
    else{ // del
      bool b = sl.remove(y);
      if(j % P == 0){
        cout << "D " << b << br; 
      }
    }
  }
}