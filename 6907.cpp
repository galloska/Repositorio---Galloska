#include <bits/stdc++.h>
#define pii pair<int,int>

using namespace std;

const int MAXN = 1005;

int in[MAXN];
int aux,nodo;
int reg[MAXN];
bool vis[MAXN];
int total[MAXN];
int number[MAXN];
map<pii,int> puentes;
vector<int> grafo[MAXN];
int numeracion, top_activo;
int low[MAXN], num[MAXN], activo[MAXN];

void PuntosArtPuentes_(int u, int p) {
    int hijos = 0;
    low[u] = num[u] = ++numeracion;
    for (int i = 0; i < grafo[u].size(); ++i) {
        int v = grafo[u][i];
        if (v == p) continue;
        if (!num[v]) {
            ++hijos;
            PuntosArtPuentes_(v, u);
            if (low[v] > num[u]) {
                total[ reg[u] ]++;
                puentes[ pii( min(u,v) , max(u,v) ) ] = 1;
            }
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], num[v]);
    }
}

void PuntosArtPuentes(int n) {
    numeracion = 0;
    fill(num, num + n, 0);
    fill(low, low + n, 0);
    fill( total , total + n , 0 );
    puentes.clear();
    for (int i = 0; i < n; ++i)
        if (!num[i]) PuntosArtPuentes_(i, -1);
}

void dfs(int u,int r){
    reg[u] = r;
    number[r]++;

    for(int i=0;i<grafo[u].size();i++){
        int v = grafo[u][i];
        if(reg[v]==-1)
            dfs(v,r);
    }
}

void dfs2(int u){
    vis[u] = true;
    nodo++;

    for(int i=0;i<grafo[u].size();i++){
        int v = grafo[u][i];
        aux++;
        if(!vis[v])
            dfs2(v);
    }
}

int main(){

    int t,a,b,n,m;

    scanf("%d",&t);

    for(int u=1;u<=t;u++){
        scanf("%d %d",&n,&m);

        for(int i=0;i<n;i++){
            in[i] = number[i] = 0;
            grafo[i].clear();
        }

        vector<pii> aristas;

        while(m--){
            scanf("%d %d",&a,&b);
            a--,b--;
            grafo[a].push_back(b);
            grafo[b].push_back(a);
            in[a]++;
            in[b]++;
            aristas.push_back( pii( a , b ) );
        }

        fill( reg , reg + n , -1 );
        int cont = 0;

        for(int i=0;i<n;i++)
            if(reg[i]==-1)
                dfs(i,cont++);

        PuntosArtPuentes(n);

        int res = 0;

        for(int i=0;i<cont;i++){
            if(total[i]==1 || number[i]==1) continue;

            bool flag = true;

            if(number[i]!=total[i]+1 || number[i]&1) flag = false;

            for(int j=0;j<n;j++)
                if(in[j]>2 && reg[j]==i)
                    flag = false;

            if(flag) res++;
        }

        for(int i=0;i<cont;i++){
            if(total[i]!=1) continue;

            for(int j=0;j<n;j++)
                grafo[j].clear();

            for(int j=0;j<aristas.size();j++){
                a = aristas[j].first;
                b = aristas[j].second;
                if(reg[a]==i && puentes.find( pii( min( a , b ) , max( a , b ) ) )==puentes.end() ){
                    grafo[a].push_back(b);
                    grafo[b].push_back(a);
                    //printf("%d -> %d\n",a,b);
                }
            }

            //printf("REGION %d:\n",i);
            fill( vis , vis + n , false );
            int uno = -1 , dos,ant=-1;
            bool flag = true;

            for(int j=0;j<n;j++){
                if(!vis[j] && reg[j]==i){
                    aux = nodo = 0;
                    dfs2(j);
                    //printf("%d %d\n",ant,nodo);
                    if(uno==-1) ant = nodo;
                    else if( nodo!=ant ) flag = false;
                    uno = nodo;
                    //printf("%d = %d %d\n",j,nodo,aux);
                    if( nodo*(nodo-1) != aux ) flag = false;
                }
            }

            if(flag) res++;
        }

        printf("Case #%d: %d\n",u,res);

    }

    return 0;
}
