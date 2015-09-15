//AC: Primer intento
//Plataforma: SPOJ
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 255;
const int INF = 1e8;

int dist[MAXN];
int cap[MAXN][MAXN];
int flujo[MAXN][MAXN];
vector<int> grafo[MAXN];

int FlujoBloqueante(int u, int t, int f) {
    if (u == t) return f; int fluido = 0;
    for (int i = 0; i < grafo[u].size(); ++i) {
        int v = grafo[u][i];
        if (dist[u] + 1 > dist[v]) continue;
        int fv = FlujoBloqueante(v, t,
            min(f - fluido, cap[u][v] - flujo[u][v]));
        flujo[u][v] += fv; flujo[v][u] -= fv;
        fluido += fv; if (fluido == f) break;
    }
    return fluido;
}

int Dinic(int s, int t, int n) {
    int flujo_maximo = dist[t] = 0;
    while (dist[t] < INF) {
        fill(dist, dist + n, INF);
        queue<int> q; q.push(s); dist[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < grafo[u].size(); ++i) {
                int v = grafo[u][i];
                if (flujo[u][v] == cap[u][v] ||
                    dist[v] <= dist[u] + 1) continue;
                dist[v] = dist[u] + 1, q.push(v);
            }
        }
        if (dist[t] < INF) flujo_maximo +=
            FlujoBloqueante(s, t, INF);
    }
    return flujo_maximo;
}

void AgregaArista(int u,int v,int p){
    grafo[u].push_back(v);
    grafo[v].push_back(u);
    cap[u][v] = p;
    cap[v][u] = p;
    flujo[v][u] = p;
    flujo[u][v] = 0;
}

int main(){

    int casos,n,s = 0,t = 250,x,y;
    scanf("%d",&casos);

    for(int u=1;u<=casos;u++){
        scanf("%d",&n);
        for(int i=0;i<MAXN;i++) grafo[i].clear();
        for(int i=0;i<MAXN;i++)
            for(int j=0;j<MAXN;j++){
                cap[i][j] = cap[j][i] = 0;
                flujo[i][j] = flujo[j][i] = 0;
            }

        for(int i=1;i<=120;i++){
            AgregaArista( i + 120 , t , 1 );
            AgregaArista( s , i , 1 );
        }

        for(int i=0;i<n;i++){
            scanf("%d %d",&x,&y);
            x++,y++;
            AgregaArista( x , y + 120 , 1 );
        }

        printf("%d\n",Dinic( s , t , MAXN ));
    }
    return 0;
}
