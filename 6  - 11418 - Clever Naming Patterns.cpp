//AC = Primer intento
//Plataforma = Uva Online Judge 11418

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int INF = 1e8;

char cad[MAXN];
int dist[MAXN];
int cap[MAXN][MAXN];
int flujo[MAXN][MAXN];
vector<int> grafo[MAXN];
vector<string> res[MAXN][MAXN];

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

    int casos,n,m,s = 0,t = 58;
    scanf("%d",&casos);

    for(int u=1;u<=casos;u++){
        scanf("%d",&n);
        for(int i=0;i<MAXN;i++) grafo[i].clear();
        for(int i=0;i<MAXN;i++)
            for(int j=0;j<MAXN;j++){
                cap[i][j] = cap[j][i] = 0;
                flujo[i][j] = flujo[j][i] = 0;
                res[i][j].clear();
            }

        for(int i=0;i<n;i++){
            scanf("%d",&m);
            for(int j=0;j<m;j++){
                scanf("\n%s",cad);
                cad[0] = toupper(cad[0]);
                if(cad[0] - 'A' < n){
                    //printf("%d -> %C\n",i,cad[0]);
                    for(int h=1;cad[h];h++) cad[h] = tolower(cad[h]);
                    string aux(cad);
                    res[i][ cad[0] - 'A' ].push_back( aux );
                    AgregaArista( s , cad[0] - 'A' + 1 , 1 );
                    AgregaArista( cad[0] - 'A' + 1 , i + 27 , 1 );
                    AgregaArista( i + 27 , t , 1);
                }
                for(int h=0;cad[h];h++)
                    cad[h] = '\0';
            }
        }

        /*for(int i=0;i<n;i++){
            for(int j=0;j<26;j++){
                if(!res[i][j].size()) continue;
                printf("%d -> %c\n",i,j+'A');
                for(int h=0;h<res[i][j].size();h++)
                    printf("%s , ",res[i][j][h].c_str());
                printf("\n");
            }
        }*/

        int flow = Dinic( s , t , 60 );
        printf("Case #%d:\n",u);
        for(int j=1;j<=n;j++)
            for(int i=0;i<n;i++)
                if( flujo[ j ][ i + 27 ] )
                    printf("%s\n",res[ i ][ j - 1 ][0].c_str());

    }
    return 0;
}
