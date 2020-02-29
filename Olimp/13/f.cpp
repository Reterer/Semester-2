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

vector <int> out;
int cnt = 0;

void dfs(const graph& gr, vector <int>& used, int v ,int p){
    // if(used[v] == 1){
    //     // Мы в цикле!!
    // }
    if(used[v])
        return;
    out[v] = cnt++;
    used[v] = 1;
    for(int i = 0; i < gr[v].size(); ++i){
            dfs(gr, used, gr[v][i], v);
    }
    // used[v] = 2;
}

typedef struct {
    int x,y;
} point;

int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

int main() {
    int n,m;
    cin >> n >> m;
    vector <string> mass(n);
    for(int i = 0; i < n; ++i){
       cin >> mass[i];
    }
    int x,y;
    cin >> y >> x; 
    y--; x--;
    queue <point> q;
    vector <vector <int> > lvl(m, vector <int>(n,-1));
    q.push(point{x,y});
    lvl[x][y] = 0;
    while(!q.empty()){
        point p = q.front();
        q.pop();
        for(int i = 0; i < 4; ++i){
            if(p.x + dx[i] > -1 && p.x + dx[i] < m && p.y + dy[i] > -1 && p.y + dy[i] < n){
                if(lvl[p.x + dx[i]][p.y + dy[i]] != -1 || mass[p.y + dy[i]][p.x + dx[i]] == '#')
                    continue;
                lvl[p.x + dx[i]][p.y + dy[i]] = lvl[p.x][p.y]+1;
                q.push(point{p.x + dx[i],p.y + dy[i]});
            }
        }
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << lvl[j][i] << ' ';
        } cout << endl;
    }
    return 0;
}