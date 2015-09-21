//AC: Segundo intento
//Plataforma: Live Archive
#include <bits/stdc++.h>
#define pii pair<int,int>

using namespace std;

const int MAXN = 20005;

int pareja[MAXN];

struct DisjointSet{
      int sets;
      int* parent;
      int* members;

      void init(int n){ // O(v)
            sets = n;
            parent = new int[n];
            members = new int[n];
            for(int i = 0; i < n; i++)
                  parent[i] = i, members[i] = 1;
      }

      int find(int a){ // O(1)
            if(a == parent[a]) return a;
            return parent[a] = find(parent[a]);
      }

      int setsize(int a){ // O(1)
            return members[find(a)];
      }

      bool joined(int a, int b){ // O(1)
            return find(a) == find(b);
      }

      void join(int a, int b){ // O(1)
            if(joined(a, b)) return;
            members[find(b)] += members[find(a)];
            parent[find(a)] = find(b);
            sets--;
      }
 
};

int main(){

    DisjointSet graph;
    int t,a,b,n,k;
    char opc;

    scanf("%d",&t);

    for(int u=1;u<=t;u++){

        scanf("%d %d",&n,&k);

        graph.init(n);
        fill( pareja , pareja + n , -1 );

        for(int i=0;i<n;i++){
            scanf("%d",&a);
            if(a==0 || a-1==i) continue;
            a--;
            pareja[i] = a;
        }

        vector<pii> query;
        vector<pii> otro;

        while(k--){
            scanf("\n%c",&opc);

            if(opc=='C'){
                scanf("%d",&a);
                //printf("%c %d\n",opc,a);
                a--;
                b = pareja[a];
                if(b==-1) continue;
                pareja[a] = -1;
                query.push_back( pii( a , -1 ) );
                otro.push_back( pii( a , b ) );
            }
            else{
                scanf("%d %d",&a,&b);
                //printf("%c %d %d\n",opc,a,b);
                a--,b--;
                query.push_back( pii( a , b ) );
            }
        }

        for(int i=0;i<n;i++)
            if(pareja[i]!=-1)
                graph.join( i , pareja[i] );

        vector<string> res;
        int j = otro.size() - 1;

        for(int i=query.size()-1;i>=0;i--){
            if(query[i].second!=-1){
                if( graph.joined( query[i].second , query[i].first ) )
                    res.push_back("YES\n");
                else res.push_back("NO\n");
            }
            else{
                graph.join( otro[j].first , otro[j].second );
                j--;
            }
        }

        printf("Case #%d:\n",u);
        for(int i=res.size()-1;i>=0;i--)
            printf("%s",res[i].c_str());
    }
    return 0;
}
