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
#define INF 2000000000
 
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

int n,m;

typedef struct Edge {
    int u,v,w;
} Edge;

typedef struct Priority {
    int dist, v;
} Priority;

bool operator< (const Priority& l, const Priority& r){
    return l.dist > r.dist;
}

void fordBelman(vector<Edge>& edges, int s){
    vector<int> dist(n,INF);
    // vector<int> parents(n,-1);
    dist[s]=0;

    for(int i = 1; i < n; ++i){
        bool changed = false;
        for(const Edge& e: edges){
            if(dist[e.v] > dist[e.u] + e.w){
                changed = true;
                dist[e.v] = dist[e.u] + e.w;
                //parents[e.v] = e.u;
            }
            if(dist[e.u] > dist[e.v] + e.w){
                changed = true;
                dist[e.u] = dist[e.v] + e.w;
                //parents[e.u] = e.v;
            }
        }
        if(!changed) {break;}
    }
}

void dejkstra(vector<vector<Edge> >& gr, int s){
    vector <int> dist(n, INF);
    vector <int> relaxed(n,0);
    dist[s] = 0;

    for(int i = 0; i < n; ++i){
        int u = -1;
        for(int j = 0; j < n; ++j){
            if(!relaxed[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }
        relaxed[u] = true;

        for(const Edge& e: gr[u]){
            if(dist[u] + e.w < dist[e.v]){
                dist[e.v] = dist[u] + e.w;
            }
        }
    }


    forI(n){
        if(dist[i] < INF)
            cout << dist[i] << ' ';
        else
            cout << -1 << ' ';
    }
    // someting
}

void dejkstraOnQueue(vector<vector<Edge> >& gr, int s){
    vector <int> dist(n, INF);
    vector <int> relaxed(n,0);
    priority_queue <Priority> pq;
    pq.push(Priority{0,s});
    dist[s] = 0;

    while(!pq.empty()){
        Priority u = pq.top();
        pq.pop();
        if(relaxed[u.v]){
            continue;
        }
        relaxed[u.v] = 1;

        for(const Edge& e: gr[u.v]){
            if(dist[e.v] > dist[u.v] + e.w){
                dist[e.v] = dist[u.v] + e.w;
                pq.push(Priority{dist[e.v],e.v});
            }
        }
    }

    // forI(n){
    //     int u = -1; // min vertex
        
    //     for(const Edge& e: gr[u]){
    //         if(dist[e.v] > dist[e.u] + e.w){
    //             dist[e.v] = dist[e.u] + e.w;
    //         }
    //     }
    // }

    forI(n){
        if(dist[i] < INF)
            cout << dist[i] << ' ';
        else
            cout << -1 << ' ';
    }

}

void floidYrshell(vector< vector <int> >& dist){
    
    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int s;
    cin >> n >> m >> s;
    s--;
    // vector <Edge> edges(n);
    // vector< vector <int> > dist(n, vector <int> (n, INF));
    vector<vector<Edge> > gr(n);
    Edge e;
    forI(m){
        scanf("%i %i %i", &e.u, &e.v, &e.w );
        e.u--;
        e.v--;
        gr[e.u].push_back(e);
        swap(e.v, e.u);
        gr[e.u].push_back(e);
    }
    dejkstraOnQueue(gr,s);
    return 0;
}