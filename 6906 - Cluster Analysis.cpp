//AC: Primer intento
//Plataforma: Live Archive

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

int num[MAXN];

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
    int t,n,k;
    scanf("%d",&t);

    for(int u=1;u<=t;u++){
        scanf("%d %d",&n,&k);

        graph.init(n);

        for(int i=0;i<n;i++)
            scanf("%d",&num[i]);

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if( abs( num[i] - num[j] ) <= k )
                    graph.join( i , j );

        printf("Case #%d: %d\n",u,graph.sets);
    }
    return 0;
}
