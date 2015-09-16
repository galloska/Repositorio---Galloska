//AC: Cuarto intento
//Plataforma: SPOJ

//Note: Something new discovered. (Flow in Undirected graphs)

#include <bits/stdc++.h>
#define lli long long int
#define pii pair<lli,lli>

using namespace std;

const int MAXN = 5005;
const lli INF = 1e12;

pii num[MAXN];
lli dist[MAXN];
pii taxi[MAXN];
lli cap[MAXN][MAXN];
lli flujo[MAXN][MAXN];
vector<int> grafo[MAXN];

lli FlujoBloqueante(int u, int t, lli f) {
    if (u == t) return f; lli fluido = 0;
    for (int i = 0; i < grafo[u].size(); ++i) {
        int v = grafo[u][i];
        if (dist[u] + 1 > dist[v]) continue;
        lli fv = FlujoBloqueante(v, t,
            min(f - fluido, cap[u][v] - flujo[u][v]));
        flujo[u][v] += fv; flujo[v][u] -= fv;
        fluido += fv; if (fluido == f) break;
    }
    return fluido;
}

lli Dinic(int s, int t, int n) {
    lli flujo_maximo = dist[t] = 0;
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
    cap[u][v] += p;
    cap[v][u] += p;
    flujo[v][u] += p;
    flujo[u][v] = 0;
}

void AgregaAristaNo(int u,int v,int p){
    grafo[u].push_back(v);
    grafo[v].push_back(u);
    cap[u][v] += p;
    cap[v][u] += p;
    flujo[v][u] = 0;
    flujo[u][v] = 0;
}

int main(){

    int n,m,a,b;
    lli c;
    scanf("%d %d",&n,&m);
    while(m--){
        scanf("%d %d %lld",&a,&b,&c);
        if(a==b) continue;
        AgregaAristaNo( min(a,b) , max(a,b) , c );
    }
    printf("%lld\n",Dinic( 1 , n , n + 1 ));
    return 0;
}
