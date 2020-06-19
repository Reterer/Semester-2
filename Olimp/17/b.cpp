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

struct ans {
    ll sum; 
    int min, max;
};

struct DSU {
    vector <ll> parent;
    vector <ll> size;
    vector <ll> sum;
    vector <int> min_;
    vector <int> max_; 

    DSU (ll n){
        for(int i = 0; i < n; ++i){
            size.push_back(1);
            parent.push_back(i);
            sum.push_back(i+1);
            min_.push_back(i+1);
            max_.push_back(i+1);
        }
    }

    ll find(ll x){
        if(x == parent[x])
            return x;
        return parent[x] = find(parent[x]);
    }

    ans unite(ll x, ll y) {
        ll a = find(x);
        ll b = find(y);

        if(a != b) {
            if (size[a] < size[b])
                swap(a,b);
            parent[b] = a;
            size[a] += size[b];
            sum[a] += sum[b];
            min_[a] = min(min_[a], min_[b]);
            max_[a] = max(max_[a], max_[b]);
        }
        return {sum[a], min_[a], max_[a]};
    }
};



int main() {
    int n, m;
    scanf("%i %i", &n, &m);
    DSU dsu(n);
    int a, b;
    ans an;
    for(int i = 0; i < m; ++i){
        scanf("%i %i", &a, &b);
        a--; b--;
        an = dsu.unite(a,b);
        printf("%lli %i %i\n", an.sum, an.min, an.max);
    }
    return 0;
}