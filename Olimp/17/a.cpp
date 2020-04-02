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
    vector <int> parent;
    vector <int> size;

    DSU (int n){
        parent.resize(n);
        size.resize(n, 1);
    
        for(int i = 0; i < n; ++i){
            parent[i] = i;
        }
    }

    int find(int x){
        if(x == parent[x])
            return x;
        return parent[x] = find(parent[x]);
    }

    int unite(int x, int y) {
        int a = find(x);
        int b = find(y);

        if(a != b) {
            if (size[a] < size[b])
                swap(a,b);
            parent[b] = a;
            size[a] += size[b];
        }
        return size[a];
    }
};


int main() {
    int n, m;
    scanf("%i %i", &n, &m);
    DSU dsu(n);
    int a, b;
    for(int i = 0; i < m; ++i){
        scanf("%i %i", &a, &b);
        a--; b--;
        printf("%i\n", dsu.unite(a,b));
    }
    return 0;
}