#include <iostream>
#include <vector>

#define INF 1000000000

using namespace std;
int ans = 0;

void solve(vector <vector <int> >& mass, vector <int>& used,int v){
    bool f = false;
    for(int i = 0; i < mass.size(); ++i){
        if(mass[v][i] && !used[i]){
            f = true;
            cout << i << ' ';
            used[i] = 1;
            solve(mass, used, i);
            used[i] = 0;
        }
    }
    if(!f){
        cout << endl;
        ans++;
    }
}

int main(){
    int n;
    cin >> n;
    vector < vector <int> > mass(n, vector <int> (n));
    vector <int> used(n);
    for(int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> mass[i][j];
        }
    }
    for(int i = 0; i < n; ++i){
        used[i] = 1;
        cout << i << ' ';
        solve(mass, used, i);
        used[i] = 0;
    }
    cout << ans << endl;
    return 0;
}
