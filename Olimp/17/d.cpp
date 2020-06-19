#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <stdio.h>

#define ll long long
#define MOD 1000000007
#define INF 1000000007
#define LLINF 9000000000000000000
#define scanfI(a) scanf("%i",&a)
#define scanfLL(a) scanf("%lli",&a)
#define scanfLF(a) scanf("%lf",&a)
#define printfI(a) printf("%i\n",a)
#define printfLL(a) printf("%lli\n",a)
#define printfLF(a) printf("%lf\n",a)
 
#define SORT(a) sort(a.begin(),a.end())
#define forI(n) for(int i = 0; i < n; ++i)
#define forJ(n) for(int j = 0; j < n; ++j)
 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define graph vector < vector <int> >
using namespace std; 


struct DSU {
    vector <ll> parent;
    vector <ll> size;

    DSU (ll n){
        parent.resize(n);
        size.resize(n, 1);
    
        for(int i = 0; i < n; ++i){
            parent[i] = i;
        }
    }

    ll find(ll x){
        if(x == parent[x])
            return x;
        return parent[x] = find(parent[x]);
    }

    void unite(ll x, ll y) {
        ll a = find(x);
        ll b = find(y);
        if(a != b) {
            if (size[a] < size[b])
                swap(a,b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};


struct edge {
    ll a;
    ll b;
    ll l;

    bool operator < (edge b) {
        return l < b.l;
    }
};


int main() {
    int n,m;
    ll u,v,w;
    scanf("%i %i", &n, &m);
    vector <edge> gr(m);
    DSU dsu(n);
    for(int i = 0; i < m; ++i){
        scanf("%lli %lli", &u, &v);
        u--; v--;
        gr[i].a = u;
        gr[i].b = v;
    }
    
    vector <int> compo(m);
    int count_components = n;
    for(int i = m-1; i > -1; --i){
        compo[i] = count_components;
        u = gr[i].a;
        v = gr[i].b;
        if(dsu.find(u) != dsu.find(v))
            count_components--;
        dsu.unite(u,v);
    }

    for(int com : compo) {
        printf("%i\n", com);
    }
    return 0;
}