//AC: Septimo intento
//Plataforma: SPOJ

//Note: Take attention in the picture. The lenght of a mini square is 200 meters.

#include <bits/stdc++.h>
#define lli long long int
#define pii pair<lli,lli>

using namespace std;

const int MAXN = 605;
const int INF = 1e8;

pii num[MAXN];
int dist[MAXN];
pii taxi[MAXN];
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

lli Distancia(pii a,pii b){
    return abs( a.first - b.first ) + abs( a.second - b.second );
}

int main(){

    int casos,n,m;
    lli s,c;
    scanf("%d",&casos);

    for(int u=1;u<=casos;u++){
        scanf("%d %d %lld %lld",&n,&m,&s,&c);
        for(int i=0;i<MAXN;i++) grafo[i].clear();
        for(int i=0;i<MAXN;i++)
            for(int j=0;j<MAXN;j++){
                cap[i][j] = cap[j][i] = 0;
                flujo[i][j] = flujo[j][i] = 0;
            }

        for(int i=1;i<=n;i++)
            scanf("%lld %lld",&num[i].first,&num[i].second);

        for(int i=1;i<=m;i++)
            AgregaArista( 0 , i , 1 );

        for(int i=1;i<=m;i++){
            scanf("%lld %lld",&taxi[i].first,&taxi[i].second);
            for(int j=1;j<=n;j++){
                lli d = Distancia( num[j] , taxi[i] );
                if(d*200 <= s*c) AgregaArista( i , j + m , 1 );
            }
        }

        for(int i=1;i<=n;i++)
            AgregaArista( i + m , 601 , 1 );

        printf("%d\n",Dinic( 0 , 601 , MAXN ));

    }
    return 0;
}
