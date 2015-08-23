//AC : Primer intento
//Plataforma : Live Archive 4473
#include <stdio.h>
#include <algorithm>

using namespace std;

int n,r,c;
int mat[105][105];
int copia[105][105];
int mov[5] = {1,-1,0,0};
int mov2[5] = {0,0,1,-1};

bool valid(int i,int j,int num){
    if(i<0 || j<0 || i>=r || j>=c) return false;
    if( num != mat[i][j] ) return false;

    return true;
}

void Propaga(){
    for(int i=0;i<r;i++)
        fill( copia[i] , copia[i] + c , -1 );
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            for(int h=0;h<4;h++)
                if( valid( i + mov[h] , j + mov2[h] , ( mat[i][j] + 1 ) % n ) )
                    copia[ i + mov[h] ][ j + mov2[h] ] = mat[i][j];

    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            if(copia[i][j]!=-1)
                mat[i][j] = copia[i][j];
}

int main(){
    int k;
    while(1){
        scanf("%d %d %d %d",&n,&r,&c,&k);
        if(!n) return 0;
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                scanf("%d",&mat[i][j]);

        while(k--) Propaga();

        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(j!=0) printf(" ");
                printf("%d",mat[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
