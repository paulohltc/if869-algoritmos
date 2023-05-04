#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define br "\n"
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);
#define PB push_back

vector<bool> vis;
vector<vector<int>> G, Gt;
int n;
vector<int> order;
vector<vector<int>> components;
vector<int> component;

bool myCmp (const vector<int>& v1, const vector<int>& v2){
    return v1[0] < v2[0];
}

void dfs1(int v){
    vis[v] = true;
    for(int u : G[v]){
        if(!vis[u]){
            dfs1(u);
        }
    }
    order.PB(v);
}

void dfs2(int v){
    vis[v] = true;
    component.PB(v);
    for(int u : Gt[v]){
        if(!vis[u]) dfs2(u);
    }
}


int main(){
    io;
    int t; cin >> t;
    while(t--){
        components.clear();
        order.clear();
        cin >> n;
        G.clear();
        Gt.clear();
        G.resize(n);
        Gt.resize(n);
        char c;
        int __;
        int sz;
        for(int i = 0; i < n; i++){
            cin >> __ >> sz >> c;
            for(int j = 0; j < sz; j++){
                int x; cin >> x;
                G[i].push_back(x);
                Gt[x].push_back(i);
            }
        }
        vis.assign(n,false);
        for(int i = 0; i < n; i++){
            if(!vis[i]) dfs1(i);
        }
        vis.assign(n,false);
        reverse(order.begin(),order.end());

        for(int v: order){
            if(!vis[v]){
                dfs2(v);
                sort(component.begin(),component.end());
                components.PB(component);
                component.clear();
            }
        }
        sort(components.begin(),components.end(), myCmp);
        cout << components.size() << br;
        for(int i = 0; i < (int)components.size(); i++){
            for(int j = 0; j < components[i].size()-1; j++){
                cout << components[i][j] << " ";
            }
            cout << components[i][components[i].size()-1];
            cout << br;
        }
        cout << br;
    }
}