#include<bits/stdc++.h>

using namespace std;

const int MAXN = 25;

int n;
int num[MAXN];
int memo[1<<MAXN];
vector<int> pos;

int DP(int mask){
    if( mask == ( 1<<n ) - 1 ) return 1;
    if(memo[mask]!=-1) return memo[mask];

    for(int j=0;j<pos.size();j++){
        if( mask&pos[j] ) continue;
        if( DP( mask | pos[j] ) ) return  memo[mask] = 1;
    }

    return  memo[mask] = 0;
}

int main(){
    int t;
    scanf("%d",&t);

    while(t--){
        pos.clear();
        scanf("%d",&n);
        int total = 0;

        for(int i=0;i<n;i++){
            scanf("%d",&num[i]);
            total += num[i];
        }

        if(total%4){
            printf("no\n");
            continue;
        }
        total /= 4;

        int cont = 0;
        for(int i=1;i<(1<<n);i++){
            int sum = 0;
            for(int j=0;j<n;j++)
                if( i&(1<<j) )
                    sum += num[j];
            if(sum==total) pos.push_back( i );
        }

        fill( memo , memo + (1<<n) , -1 );
        if(DP( 0 )) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}
