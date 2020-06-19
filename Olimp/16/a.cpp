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

struct Treap {
    ll k;
    ll p;
    Treap* l = nullptr;
    Treap* r = nullptr;
};

void split(Treap* t, ll k, Treap*& l, Treap*& r) {
    if(t == nullptr) {
        l = r = nullptr;
    } else if (k < t->k) {
        split(t->l, k, l, t->l);
        r = t;
    } else {
        split(t->r, k, t->r, r);
        l = t;
    }
}

void insert(Treap*& t, Treap*& node) {
    if(t == nullptr) {
        t = node;
    } else if (node->p > t->p) {
        split(t, node->k, node->l, node->r);
        t = node;
    } else {
        insert(node->k < t->k ? t->l : t->r, node);
    }
}

void dfs(Treap* t) {
    if(t == nullptr)
        printf("null\n");
    else {
        printf("%lli %lli\n", t->k, t->p);
        dfs(t->l);
        dfs(t->r);
    }
}

int main() {
    int n;
    scanfI(n);
    Treap* treap = nullptr;
    for(int i = 0; i < n; i++){
        Treap* n = new Treap;
        scanf("%lli %lli", &(n->k), &(n->p));
        insert(treap,n);
    }
    dfs(treap);   
    return 0;
}