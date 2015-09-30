//AC: 4to intento
//Plataforma: Liver archive 6436 - The Busiest City

#include <bits/stdc++.h>
#define lli long long int

using namespace std;

const int INF = 1e8;
const int MAXN = 20005;

int n,total;
lli hijos[MAXN];
vector<int> lista[MAXN];

void dfs(int u,int p){

    for(int i=0;i<lista[u].size();i++){
        int v = lista[u][i];
        if(p==v) continue;
        dfs( v, u );
        hijos[u] += hijos[v];
    }

    int sobran = n - 1 - hijos[u];
    int res = sobran * hijos[u];
    int aux = 0;
    
    for(int i=0;i<lista[u].size();i++){
        int v = lista[u][i];
        if(v==p) continue;
        int ramas = hijos[u] - hijos[v];
        aux += hijos[v] * ramas;
    }

    res += aux / 2;

    total = max( total , res );

    hijos[u] = hijos[u] + 1;
}

int main(){

    int t,a,b,centro,centro2;
    scanf("%d",&t);

    for(int z=1;z<=t;z++){

        scanf("%d",&n);

        for(int i=0;i<n;i++){
            lista[i].clear();
            hijos[i] = 0;
        }

        for(int i=0;i<n-1;i++){
            scanf("%d %d",&a,&b);
            a--,b--;
            lista[a].push_back(b);
            lista[b].push_back(a);
        }

        total = 0;
        dfs(0,-1);

        printf("Case #%d: %d\n",z,total);
    }

    return 0;
}
