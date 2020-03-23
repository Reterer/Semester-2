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

struct SegmentTreeSt {
    vector <ll> data;
    vector <ll> update;
    int n;

    SegmentTreeSt(int _n) {
        n = _n;
        data.resize(4*n);
        update.resize(4*n);
    }

    void build (int v, int vl, int vr, vector <ll>& mass) {
        if (vl == vr) {
            data[v] = mass[vl];
            return;
        }
        int m = vl + (vr - vl)/2;
        build(2*v + 1, vl, m, mass);
        build(2*v + 2, m+1, vr, mass);
        data[v] = max(data[v*2+1], data[v*2+2]);
    }

    void push(int v, int vl, int vr) {
        if(update[v]){
            data[v] += update[v];
            if (vl != vr){
                update[2*v + 1] += update[v];
                update[2*v + 2] += update[v];
            }
            update[v] = 0;
        }
    }

    ll get(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if(vr < l || vl > r)
            return -LLINF;
        if(vl >= l && vr <= r)
            return data[v];

        int m = vl + (vr - vl)/2;
        return max(get(v*2 + 1, vl, m, l, r), get(v*2 + 2, m+1, vr, l, r));
    }

    void add(int v, int vl, int vr, int l, int r, ll val){
        push(v, vl, vr);
        if (r < vl || vr < l)
            return;
        if (l <= vl && vr <= r) {
            update[v] = val;
            push(v, vl, vr);
            return;
        }
        int m = vl + (vr - vl)/2;
        add(2*v + 1, vl, m, l, r, val);
        add(2*v + 2, m+1, vr, l, r, val);
        data[v] = max(data[2*v + 1], data[2*v + 2]);
    }

};

int main() {
    int n;
    ll a,b,c;
    scanfI(n);
    SegmentTreeSt tree(n);
    vector <ll> mass(n);
    for(int i = 0; i < n; ++i){
        scanfLL(mass[i]);
    }
    tree.build(0,0,n-1,mass);
    int k;
    scanfI(k);
    for(int i = 0; i < k; ++i){
        scanf("%lli %lli %lli", &a, &b, &c);
        a--;b--;
        tree.add(0,0,n-1,a,b,c);
        printf("%lli\n", tree.get(0,0, n-1, a,b));
    }
    return 0;
}