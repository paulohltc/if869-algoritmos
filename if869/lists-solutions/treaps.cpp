#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define br "\n"
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

ll seed;
struct Rng{
  ll A = 1664525, C = 1013904223, R = 1LL<<32, rnd = -1;
  ll next(){
    if (rnd == -1) return rnd = seed;
    else return rnd = (A * rnd + C) % R;
  }
};
Rng RNG;


class Node{
    public:
    ll key;
    ll prty;
    Node* left;
    Node* right;
    Node* par;
    Node(ll key): key(key){
        left = NULL;
        right = NULL;
        par = NULL;
        prty = RNG.next();
    }
};


class Treap{
public:
  Node* root;
  Treap(){root = NULL;}
  void insert(ll key, ll& depth){
    Node* x = new Node(key);
    root = insert_helper(root, x, depth);
  }
  ll qry(ll key){
    if(!root){
      return -1;
    } 
    ll depth = 0;
    Node* curr = root;
    bool fnd = 0;
    while(!fnd && curr){
      if(key < curr->key){
        if(curr->left){
          depth++;
          curr = curr->left;
        }
        else{
          return -1;
        }
      }
      else if(key > curr->key){
        if(curr->right){
          depth++;
          curr = curr->right;
        }
        else{
          return -1;
        }
      }
      else{
        fnd = 1;
      }
    }
    return depth;
  }

  pair<Node*,Node*> split(Node* curr, ll key){
    if(!curr){
      return {NULL,NULL};
    }
    if(key == curr->key){
      return {curr->left, curr->right};
    }
    else if(key < curr->key){
      pair<Node*,Node*> ans = split(curr->left,key);
      Node* lt = ans.first;
      curr->left = ans.second;
      return {lt,curr};
    }
    else{
      pair<Node*,Node*> ans = split(curr->right,key);
      Node* gt = ans.second;
      curr->right = ans.first;
      return {curr,gt};
    }

  }
  Node* insert_helper(Node* curr, Node* x, ll& depth){
    if(!curr){
      return x;
    }
    if(x->prty > curr->prty){
      pair<Node*,Node*> ans = split(curr,x->key);
      x->left = ans.first;
      x->right = ans.second;
      return x;
    }
    else if(x->key < curr->key){
      depth++;
      curr->left = insert_helper(curr->left,x,depth);
      return curr;
    }
    else{
      depth++;
      curr->right = insert_helper(curr->right,x,depth);
      return curr;
    }
   }

   Node* merge(Node* rootx, Node* rooty){
    if(!rootx) return rooty;
    else if(!rooty) return rootx;
    else if(rootx->prty > rooty->prty){
      rootx->right = merge(rootx->right,rooty);
      return rootx;
    }
    else{
      rooty->left = merge(rootx,rooty->left);
      return rooty;
    }
   }

   void remove(ll key){
    root = remove_helper(root,key);
   }

   Node* remove_helper(Node* curr, ll x){
    if(!curr) return NULL;
    else if(x == curr->key){
      return merge(curr->left,curr->right);
    }
    else if(x < curr->key){
      curr->left = remove_helper(curr->left,x);\
      return curr;
    }
    else{
      curr->right = remove_helper(curr->right,x);
      return curr;
    }
   }

};


int main(){
  io;
  ll U,B,N,I,D,Q,P;
  cin >> seed >> U >> B >> N >> I >> D >> Q >> P;
  Treap trp = Treap();
  while(B--){
    ll K = RNG.next() % U;
    ll _ = 0;
    if(trp.qry(K) == -1){
      trp.insert(K,_);      
    }
  }
  for(int i = 0; i < N; i++){
    ll X = RNG.next() % (I+D+Q);
    if(X < I){ // ins
      ll K = RNG.next() % U;
      ll depth = 0;
      if(trp.qry(K) == -1){
        trp.insert(K,depth);      
      }else{
        depth = -1;
      }
      if(i % P == 0){
        cout << "I " << K << " " << depth << br;
      }
    }
    else if(X < (I+D)){ // del
      ll K = RNG.next() % U;
      ll depth = trp.qry(K);
      if(depth != -1){
        trp.remove(K);
      }
      if(i % P == 0){
        cout << "D " << K << " " << depth << br;
      }
    }
    else{ // qry
      ll K = RNG.next() % U;
      if(i % P == 0){
        ll depth = trp.qry(K);
        cout << "Q " << K << " " << depth << br;
      }
    }
  }


}