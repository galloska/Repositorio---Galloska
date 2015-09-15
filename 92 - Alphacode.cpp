//AC: Segundo intento
//Plataforma: SPOJ

#include <bits/stdc++.h>
#define lli long long int

using namespace std;

string cad;
lli memo[6005][30];

lli DP(int id,int prev){
    if(prev>26 || prev==0) return 0;
    if(id==cad.size()) return 1;
    if(memo[id][prev]!=-1) return memo[id][prev];

    return memo[id][prev] = DP( id + 1 , cad[id] - 48 ) + DP( id + 1 , prev * 10 + (cad[id] - 48) );
}

int main(){
    while(1){
        cin>>cad;
        if(cad=="0") return 0;
        for(int i=0;i<cad.size();i++)
            fill( memo[i] , memo[i] + 30 , -1 );
        cout<<DP( 1 , cad[0] - 48 )<<'\n';
    }
    return 0;
}
