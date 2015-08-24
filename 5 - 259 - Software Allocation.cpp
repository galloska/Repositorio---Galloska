//AC : 11vo intento
//Plataforma : Uva Online Judge
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int MAXN = 5005;
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
    res[u][v] = p;
}

map<string,int> check;
map<string,int> check2;
map<int,string> vuelve;
map<int,string> vuelve2;
vector< vector<string> > otro;
string cad;

void Init(int n){
    for(int i=0;i<n;i++){
        fill( res[i] , res[i] + n , 0 );
        lista[i].clear();
    }
    vuelve.clear();
    vuelve2.clear();
    check.clear();
    check2.clear();
    otro.clear();
}

int main(){
    int t,u = 1,total = 0 , o = 1 , casos = 0;
    scanf("%d\n",&t);
    while(t>0){
        if(getline(cin,cad)) casos = casos;
        else cad = "";

        if(cad=="" || cad==" "){
            if(casos) printf("\n");
            casos++;
            u--,o--;
            int peso = ( u - 1 ) / 2;
            //Desde la fuente a partidos con peso maximo
            for(int i=1;i<=o;i++)
                AgregarArista( 0 , i , peso );

            //De los partidos a las personas con peso 1
            for(int i=0;i<otro.size();i++)
                AgregarArista( check2[ otro[i][1] ] , i + o + u + 1 , 1 );

            //Desde las personas a los clubs con peso 1
            for(int i=0;i<otro.size();i++)
                for(int j=2;j<otro[i].size();j++){
                    AgregarArista( i + o + u + 1 , check[ otro[i][j] ] + o , 1 );
                    AgregarArista( check[ otro[i][j] ] + o , o + u + total + 1 , 1 );
                }

            int w = FlujoMaximo( 0 , o + u + total + 1 , o + u + total + 2 );
            if(w!=u) printf("Impossible.\n");
            else{
                for(int i=0;i<total;i++)
                    for(int j=1;j<=u;j++)
                        if(res[ j + o ][ i + o + u + 1  ])
                            printf("%s %s\n",vuelve[i + 1].c_str(),vuelve2[j].c_str());
            }
            Init(o + u + total + 2);
            u = o = 1;
            total = 0;
            t--;
            continue;
        }
        vector<string> aux;
        string cad2 = "";
        for(int i=0;cad[i]!='\0';i++){
            if(cad[i]==' '){
                aux.push_back(cad2);
                cad2 = "";
            }
            else cad2 += cad[i];
        }
        aux.push_back(cad2);
        otro.push_back(aux);

        vuelve[total + 1] = aux[0];
        //Mapeo de partidos politicos
        if(check2.find(aux[1])==check2.end())
            check2[aux[1]] = o++;
        //Mapeo de todos los clubs
        for(int i=2;i<aux.size();i++)
            if(check.find(aux[i])==check.end()){
                vuelve2[u] = aux[i];
                check[aux[i]] = u++;
            }

        total++;
    }
    return 0;
}
