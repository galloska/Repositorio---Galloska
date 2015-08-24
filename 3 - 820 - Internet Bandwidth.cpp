//AC : 4to intento
//Plataforma: Uva Online Judge
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 105;
const int INF = 1000000000;

bool vis[MAXN];
int camino[MAXN];
int res[MAXN][MAXN];
int mf, s, t,flujo_min;
vector<int> lista[MAXN];

void AumentaCamino(int v, int minArista){
    if(v == s){
        flujo_min = minArista;
        return; 
    }
    else if(camino[v] != -1){
        AumentaCamino(camino[v], min(minArista, res[ camino[v] ][ v ]));
        res[ camino[v] ][ v ] -= flujo_min;
        res[ v ][ camino[v] ] += flujo_min;
    }
}

int FlujoMaximo_(int n){
    mf = 0; // Maximo Flujo
    while (1){
        flujo_min = 0;
        fill( vis , vis + n , false );
        fill( camino , camino + n , -1 );
        vis[s] = true;
        queue<int> q;
        q.push(s);

        while(!q.empty()){
            int u = q.front();
            q.pop();
            if (u == t) break;
            for (int j = 0; j < lista[u].size(); j++){
                int v = lista[u][j];
                if(res[u][v] > 0 && !vis[v])
                    vis[v] = true, q.push(v), camino[v] = u;
            }
        }

        AumentaCamino(t, INF);
        if (flujo_min == 0) break;
        mf += flujo_min;
    }
    return mf;
}

int FlujoMaximo(int n){
    return FlujoMaximo_(n);
}

void AgregarArista(int u,int v,int p){
    lista[u].push_back(v);
    lista[v].push_back(u);
    res[u][v] += p;
    res[v][u] += p;
}

void Init(int n){
    for(int i=0;i<n;i++){
        fill( res[i] , res[i] + n , 0 );
        lista[i].clear();
    }
}

int main(){
    int n,m,a,b,c,u=1;

    while(1){
        scanf("%d",&n);

        if(!n) return 0;
        Init(n);

        scanf("%d %d %d",&s,&t,&m);
        s--,t--;

        while(m--){
            scanf("%d %d %d",&a,&b,&c);
            a--,b--;
            AgregarArista( a , b , c );
        }
        
        printf("Network %d\n",u++);
        printf("The bandwidth is %d.\n", FlujoMaximo( n ) );
        printf("\n");
    }
    return 0;
}
