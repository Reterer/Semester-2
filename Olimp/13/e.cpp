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


//lvl (n, -1)
void bfs(const graph& gr, vector <int> lvl, int v){
    queue <int> q;
    q.push(v);
    lvl[v] = 0;

    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(int u: gr[p]){
            if(lvl[u] != -1)
                continue;
            lvl[u] = lvl[p]+1;
            q.push(u);
        }
    }
}

vector <int> get_path(const graph& gr, int s, int f){
    vector <int> lvl(gr.size(),-1);
    bfs(gr, lvl, f);
    vector <int> path;
    path.push_back(s);
    while (path.back() != f){
        int lvlC = lvl[path.back()];
        lvlC--;
        for(int u: gr[path.back()]){
            if(lvl[u] == lvlC){
                path.push_back(u);
                break;
            }
        }
    }
    return path;
}

bool f = false;
vector <int> ans(0);

void dfs(const graph& gr, vector <int>& used, int v ,int p){
    if(used[v] == 1){
        // Мы в цикле!!
        used[v] = 2;
        f = true;
    }
    if(used[v])
        return;

    used[v] = 1;
    for(int i = 0; i < gr[v].size(); ++i){
        if(gr[v][i] != p)
            dfs(gr, used, gr[v][i], v);
        if(f){
            ans.push_back(v);
            if(used[v] == 2){
                f = false;
            }
            used[v] = 2;
            return;
        }
    }
    used[v] = 2;
}

int main() {
    int n;
    f = false;
    cin >> n;
    graph gr(n);
    forI(n){
        int u,v;
        scanf("%i %i", &u, &v);
        u--; v--;
        gr[u].push_back(v);
        gr[v].push_back(u); // Неорентированный граф
    }
    vector <int> used(n);
    dfs(gr, used, 0, -1);
    SORT(ans);
    forI(ans.size()){
        printf("%i ", ans[i]+1);
    }
    //Компоненты связанности
    // vector <int> used(n);
    // int component = 0;
    // forI(n){
    //     if(!used[i]){
    //         dfs(gr, used, i, -1);
    //         component++;
    //     }
    // }
    //----------------------

    return 0;
}