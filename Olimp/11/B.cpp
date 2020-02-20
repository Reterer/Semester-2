#include <iostream>
#include <vector>

using namespace std;

#define INF 1000000000

int solve (vector <vector <int> >& dp, vector <vector <int> >& coast) {
    int sizeMask = 1 << dp.size();
    int res = INF;

    for(int mask = 1; mask < sizeMask; ++mask){
        for(int curV = 0; curV < dp.size(); ++curV){
            int preMask = mask & ~(1 << curV);
            int min = INF;
            for(int preV = 0; preV < dp.size(); ++preV){
                if( (mask >> preV)%2 == 0 ) {continue;}
                if( dp[preV][preMask] + coast[preV][curV] < min ){
                    min = dp[preV][preMask] + coast[preV][curV];
                }
            }
            dp[curV][mask] = min;
        }
    }

    for(int i = 0; i < dp.size(); ++i){
        if(dp[i][sizeMask-1] < res)
            res = dp[i][sizeMask-1];
    }

    return res;
}

int main(){
    int n;
    cin >> n;
    int sizeMask = 1 << n;  
    vector < vector <int> > dp(n);
    vector < vector <int> > coast(n);
    
    for(int i = 0; i < n; ++i){
        coast[i].resize(n);
        dp[i].resize(sizeMask, INF);
        for(int j = 0; j < n; ++j){
            cin >> coast[i][j];
        }
    }

    dp[0][0] = 0;
    cout << solve(dp, coast);
    return 0;
}