//AC: Primero intento
//Plataforma: Live Archive

#include <bits/stdc++.h>

using namespace std;

const int INF = 1e8;
const int MAXN = 1001;

int n;
int num[MAXN];
int memo[MAXN][11][51][4];
int valor[10] = { 0 , 4 , 8 , 11 };

int DP(int id,int sobran,int energia,int set){

    if(sobran<0) return INF;
    if(id==n) return 0;

    if(memo[id][sobran][energia][set]!=-1) return memo[id][sobran][energia][set];

    if(!sobran){
        if(energia<set)
            return memo[id][sobran][energia][set] = DP( id + 1 , 0 , 0 , 0 ) + num[id];
        if(valor[set]>num[id])
            return memo[id][sobran][energia][set] = DP( id + 1 , sobran , energia - set , set );
        return memo[id][sobran][energia][set] = DP( id + 1 , sobran , energia - set , set ) + ( num[id] - valor[set] );
    }

    int res;

    if(energia<set)
        res = DP( id + 1 , 0 , 0 , 0 ) + num[id];
    else if(valor[set]>num[id])
        res = DP( id + 1 , sobran , energia - set , set );
    else
        res = DP( id + 1 , sobran , energia - set , set ) + ( num[id] - valor[set] );

    for(int i=0;i<4;i++){
        if(set==i) continue;
        if(energia<i)
            res = min( res , DP( id + 1 , 0 , 0 , 0 ) + num[id] );
        else if(valor[i]>num[id])
            res = min( res , DP( id + 1 , sobran - 1 , energia - i , i ) );
        else
            res = min( res , DP( id + 1 , sobran - 1 , energia - i , i ) + ( num[id] - valor[i] ) );
    }

    return memo[id][sobran][energia][set] = res;
}

int main(){

    int t,k,e;
    scanf("%d",&t);

    for(int u=1;u<=t;u++){
        scanf("%d %d %d",&n,&k,&e);

        for(int i=0;i<n;i++)
            scanf("%d",&num[i]);

        for(int i=0;i<=n;i++)
            for(int j=0;j<=k;j++)
                for(int h=0;h<=e;h++)
                    for(int o=0;o<4;o++)
                        memo[i][j][h][o] = -1;

        printf("Case #%d: %d\n",u,DP( 0 , k , e , 0 ));
    }
    return 0;
}
