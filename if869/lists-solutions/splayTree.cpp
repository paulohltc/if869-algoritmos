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
    Node* left;
    Node* right;
    Node* par;
    Node(ll num){
        val = num;
        left = NULL;
        right = NULL;
        par = NULL;
    }
    Node(ll num, Node* p){
      val = num;
      par = p;
    }
};


class SplayTree{
public:
  Node* root;
  SplayTree(){
    root = NULL;
  }

  void insert(ll val, ll& d){
    d = 0;
    if(!root){
      root = new Node(val);
      return;
    }
    Node* curr = root;
    while(curr){
      if(val < curr->val){
        if(curr->left){
          curr = curr->left;
          d++;
        }
        else{
          curr->left = new Node(val,curr);
          d++;
          return;
        }
      }
      else if(val > curr->val){
        if(curr->right){
          curr = curr->right; 
          d++;
        }
        else{
          curr->right = new Node(val,curr);
          d++;
          return;
        }  
      }
      else{
        d = -1;
        return;
      }
    }
  }

  Node* rotate_left(Node* x){
    Node* p; 
    Node* r;
    Node* rl;
    p = x->par;
    r = x->right;
    rl = r->left;
    x->right = rl;
    if(rl){
      rl->par = x;
    } 
    r->left = x;
    x->par = r;
    r->par = p;
    if(p && x == p->left){
      p->left = r;
    }
    else if(p && x == p->right){
      p->right = r;
    }
    return r;
  }

  Node* rotate_right(Node* x){
    Node* p; 
    Node* l;
    Node* lr;
    p = x->par;
    l = x->left;
    lr = l->right;
    x->left = lr;
    if(lr){
      lr->par = x;
    }
    l->right = x;
    x->par = l;
    l->par = p;
    if(p && x == p->right){
      p->right = l;
    } 
    else if(p && x == p->left){
      p->left = l;
    }
    return l;
  }

  Node* zig(Node* x){
    Node* p = x->par;
    if(p && x == p->left){
      return rotate_right(p);
    }
    else if(x == p->right){
      return rotate_left(p);
    }
    return NULL;
  }

  Node* zigzag(Node* x){
    Node* p = x->par;
    Node* g = p->par;
    if(p == g->left){
      if(x == p->left){
        g = rotate_right(g);
        return rotate_right(p);
      }
      else{
        p = rotate_left(p);
        return rotate_right(g);
      }
    }
    else{
      if(x == p->right){
        g = rotate_left(g);
        return rotate_left(p);
      }
      else{
        p = rotate_right(p);
        return rotate_left(g);
      }
    }
  }

  Node* splay(Node* x){
    while(x->par != NULL){
      Node* g = x->par->par;
      if(!g){
        x = zig(x);
      }
      else{
        x = zigzag(x);
      }
    }
    return x;
  }

  Node* BSTSearch(ll val, ll& d){
    Node* curr = root;
    while(curr){
      if(val < curr->val){
        if(curr->left){
          d++;
          curr = curr->left;
        }
        else{
          d = -1;
          return NULL;
        }
      }
      else if(val > curr->val){
        if(curr->right){
          d++;
          curr = curr->right;
        }
        else{
          d = -1;
          return NULL;
        }
      }
      else{
        return curr;
      }
    }
    return curr;
  }

  void qry(ll val, ll& d){
    d = 0;
    Node* x = BSTSearch(val,d);
    if(x){
      root = splay(x);
    }else{
      d = -1;
    }
  }
};


int main(){
  io;
  ll U,B,N,I,Q,P;
  cin >> seed >> U >> B >> N >> I >> Q >> P;
  SplayTree st = SplayTree();
  for(int i = 0; i < B; i++){
    ll _ = 0;
    ll k = RNG.next() %  U;
    st.insert(k,_);
  }

  for(int j = 0; j < N; j++){
    ll X = RNG.next();
    if(X % (I+Q) < I){ // ins
      ll k = RNG.next() % U;
      ll d = 0;
      st.insert(k,d);
      if(j % P == 0){
        cout << "I " << k << " " << d << br;
      }
    }
    else{ // qry
      ll k = RNG.next() % U;
      ll d = 0;
      st.qry(k,d);
      if(j % P == 0){
        cout << "Q " << k << " " << d << br;
      } 
    }
  }


}