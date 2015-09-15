//AC: Primer intento
//Plataforma: Uva Online Judge 11045

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
const int INF = 1e8;

char cad[MAXN];
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

void Inserta(int i,int t){
    if(cad[0]=='S')
        AgregaArista( i + 7 , 5 , 1 );
    else if(cad[0]=='M')
        AgregaArista( i + 7 , 4 , 1 );
    else if(cad[0]=='L')
        AgregaArista( i + 7 , 3 , 1 );
    else if(cad[0]=='X' && cad[1]=='L')
        AgregaArista( i + 7, 2 , 1 );
    else if(cad[0]=='X' && cad[1]=='X')
        AgregaArista( i + 7 , 1 , 1 );
    else
        AgregaArista( i + 7 , 6 , 1 );
}

int main(){

    int casos,n,m,s = 0,t = 40;
    scanf("%d",&casos);

    for(int u=1;u<=casos;u++){
        scanf("%d %d",&n,&m);
        for(int i=0;i<MAXN;i++) grafo[i].clear();
        for(int i=0;i<MAXN;i++)
            for(int j=0;j<MAXN;j++){
                cap[i][j] = cap[j][i] = 0;
                flujo[i][j] = flujo[j][i] = 0;
            }

        n /= 6;
        for(int i=1;i<=6;i++)
            AgregaArista( i , t , n );

        for(int i=0;i<m;i++)
            AgregaArista( s , i + 7 , 1 );

        for(int i=0;i<m;i++){
            scanf("\n%s",cad);
            Inserta(i,t);
            for(int j=0;cad[j];j++) cad[j] = '\0';
            scanf("\n%s",cad);
            Inserta(i,t);
            for(int j=0;cad[j];j++) cad[j] = '\0';
        }

        int flow = Dinic( s , t , MAXN );
        if(flow==m) printf("YES\n");
        else printf("NO\n");


    }
    return 0;
}
