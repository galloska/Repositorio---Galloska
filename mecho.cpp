#include <bits/stdc++.h>
#define pii pair<int,int>

using namespace std;

const int MAXN = 805;
const int INF = 1e6;

int n;
queue<pii> q;
char mat[MAXN][MAXN];
int dist[MAXN][MAXN];
int dist2[MAXN][MAXN];
int mov[5] = {1,-1,0,0};
int mov2[5] = {0,0,1,-1};

bool valid(int i,int j){
	if(i==n || j==n || i<0 || j<0) return false;
	if(mat[i][j]=='T') return false;
	return true;
}

void bfs(){
	int i,j;
	pii nodo;
	while(!q.empty()){
		nodo = q.front();
		i = nodo.first , j = nodo.second;
		q.pop();
		for(int h=0;h<4;h++)
			if( valid( i + mov[h] , j + mov2[h] ) &&
			dist[i][j] + 1 < dist[ i + mov[h] ][ j + mov2[h] ]){
				dist[ i + mov[h] ][ j + mov2[h] ] = dist[i][j] + 1;
				q.push( pii(i + mov[h] , j + mov2[h]) );
			}
	}
}

void bfs2(pii nodo){
	int i,j;
	q.push(nodo);
	dist2[nodo.first][nodo.second] = 0;
	while(!q.empty()){
		nodo = q.front();
		i = nodo.first , j = nodo.second;
		q.pop();
		for(int h=0;h<4;h++)
			if( valid( i + mov[h] , j + mov2[h] ) &&
			dist2[i][j] + 1 < dist2[ i + mov[h] ][ j + mov2[h] ]){
				dist2[ i + mov[h] ][ j + mov2[h] ] = dist2[i][j]+1;
				q.push( pii(i + mov[h] , j + mov2[h]) );
			}
	}
}

int main(){
	int s , a , b , c , d;
	scanf("%d %d",&n,&s);

	for(int i=0;i<n;i++)
		scanf("\n%s",mat[i]);

	for(int i=0;i<n;i++){
		fill( dist[i] , dist[i] + MAXN , INF );
		fill( dist2[i] , dist2[i] + MAXN , INF );
	}

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			if(mat[i][j]=='H')
				q.push( pii(i,j) ) , dist[i][j] = 0;
			else if(mat[i][j]=='M')
				a = i , b = j;
			else if(mat[i][j]=='D')
				c = i , d = j;
		}

	bfs();

	bfs2(pii(a,b));

	printf("%d %d\n",( dist2[c][d] , dist[a][b] );
	return 0;
}