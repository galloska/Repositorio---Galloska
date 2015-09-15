//AC: Primer intento
//Plataforma: Uva Online Judge 11462

#include <stdio.h>

using namespace std;

const int MAXN = 105;

int cubeta[MAXN];

int main(){
    int n,a;
    while(scanf("%d",&n) && n){
        for(int i=1;i<=100;i++) cubeta[i] = 0;

        for(int i=0;i<n;i++){
            scanf("%d",&a);
            cubeta[a]++;
        }

        bool flag = false;
        for(int i=1;i<=100;i++)
            while(cubeta[i]){
                if(flag) printf(" ");
                printf("%d",i);
                flag = true;
                cubeta[i]--;
            }
        printf("\n");
    }
    return 0;
}
