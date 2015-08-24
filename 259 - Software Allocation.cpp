//AC : 14vo intento
//Plataforma : Uva online Judge
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 40;
const int INF = 1000000000;

bool vis[MAXN];
int camino[MAXN];
int matcheo[MAXN];
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
            for (int j = 0; j < 38; j++){
                int v = j;
                if(res[u][v] > 0 && !vis[v] && v!=38)
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
    res[u][v] = p;
}

string cad;

void Init(int t_){
    mf = s = t = flujo_min = 0;
    for(int i=0;i<MAXN;i++)
        lista[i].clear();
    for(int i=0;i<MAXN;i++)
        fill(res[i] , res[i]+MAXN , 0);
    for(int i=1;i<=10;i++)
        AgregarArista( i , t_ , 1 );
    fill( matcheo , matcheo + MAXN , '_' - 'A' + 11 );
}

void Solve(int s_,int t_,int n,int &aux){
    int w = FlujoMaximo(s_ , t_ , n);
    for(int i=1;i<=10;i++){
        for(int j=11;j<37;j++)
            if(res[i][j])
                matcheo[i-1] = j;
    }
    if(w!=aux) printf("!\n");
    else{
        for(int i=0;i<=9;i++)
            printf("%c",matcheo[i]+'A'-11);
        printf("\n");
    }
    Init(t_);
    aux = 0;
}

int main(){
    int n = 38;
    int s_ = 0,t_ = 37,aux = 0;
    char letra;
    Init(t_);
    while(getline(cin,cad)){
        if(cad=="") Solve(s_,t_,n,aux);
        else{
            letra = cad[0];
            aux += cad[1] - 48;
            AgregarArista( s_ , letra - 'A' + 11, cad[1] - 48 );
            for(int i=3;i<cad.size() && cad[i]!=';';i++)
                AgregarArista( letra - 'A' + 11 , cad[i] - 48 + 1 , INF );
        }
    }
    Solve(s_,t_,n,aux);
    return 0;
}
