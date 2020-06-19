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

#define graph vector < string >
using namespace std; 
struct pos {
    int x,y;
};
ll was_set = 0;

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};

void dfs(graph &gr, int i, int j, char& ch, char mode){
    if(gr[i][j] == ch && mode == 0)
        return;
    gr[i][j] = ch;
    for(int k = 0; k < 4; k++){
        if(dx[k] + i < 0 || dx[k]+i >= gr.size() || dy[k] + j < 0 || dy[k] + j >= gr[0].size())
            continue;
        if(gr[dx[k] + i][dy[k] + j] == '#')
            continue;
        dfs(gr, dx[k] + i, dy[k] + j, ch, 0);
    }
}

int main() {
    int n,m;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    graph gr(n);
    for(int i = 0; i < n; i++){
        cin >> gr[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; ++j){
            if(gr[i][j] == '.' || gr[i][j] == '#')
                continue;
            // cout << gr[i][j] << ' ' << gr[i][j] - 97 << ' ' << (1<<(gr[i][j] - 97)) << endl;
            // cout << ((1<<(ll)(gr[i][j] - 97)) & was_set) << endl;
            if(((1<<(ll)(gr[i][j] - 97)) & was_set) == 0){
                was_set = was_set | (1<<(gr[i][j] - 97));
                dfs(gr, i, j, gr[i][j], 1);
            }
        }
    }

    for(int i = 0; i < n; ++i){
        cout << gr[i] << endl;
    }
    return 0;
}