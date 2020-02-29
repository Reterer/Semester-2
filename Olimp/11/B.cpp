#include <iostream>
#include <vector>

#define INF 1000000000

using namespace std;

int main(){
    int n;
    cin >> n;
    vector <vector <int> > c(n);
    vector <vector <int> > dp(n);
    
    for(int i = 0; i < n; ++i){
        c[i].resize(n);
        dp[i].resize(1<<n, INF);
        for(int j = 0; j < n; ++j){
            cin >> c[i][j];
        }
    }
    
    for(int i = 0; i < n; ++i)
        dp[i][0] = 0;
    return 0;
}
