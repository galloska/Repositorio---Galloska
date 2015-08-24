//AC : 2do intento
//Plataforma : Uva Online Judge
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1050;
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

int FlujoMaximo(int s_,int t_,int n){
    s = s_;
    t = t_;
    return FlujoMaximo_(n);
}

void AgregarArista(int u,int v,int p){
    lista[u].push_back(v);
    lista[v].push_back(u);
    res[u][v] += p;
}

void Init(int n){
    for(int i=0;i<n;i++){
        fill( res[i] , res[i] + n , 0 );
        lista[i].clear();
    }
}

int main(){
    int n,m,a,c;
    while(1){
        scanf("%d %d",&c,&n);
        if(!n) return 0;

        Init( MAXN );
        int sum = 0;
        for(int i=1;i<=c;i++){
            scanf("%d",&a);
            sum += a;
            AgregarArista( 0 , i , a );
        }

        for(int i=1;i<=n;i++){
            scanf("%d",&m);
            while(m--){
                scanf("%d",&a);
                AgregarArista( a , i + c , INF );
            }
            AgregarArista( i + c , n + c + 1 , 1 );
        }
        int w = FlujoMaximo( 0 , n + c + 1 , n + c + 2 );
        if(w!=sum) printf("0\n");
        else{
            printf("1\n");
            for(int j=1;j<=c;j++){
                bool flag = false;
                for(int i=1;i<=n;i++)
                    if(res[i+c][j]){
                        if(flag) printf(" ");
                        flag = true;
                        printf("%d",i);
                    }
                printf("\n");
            }
        }
    }
    return 0;
}
