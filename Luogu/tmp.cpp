#include<bits/stdc++.h>
using namespace std;

int f[1705];

int main(void){
    f[1]=1,f[2]=2,f[3]=3;
    for(int i=1;i<=45;++i){
        int a=ceil(sqrt(i)),b=floor(sqrt(i));
        f[i]=f[a]+f[b];
        printf("%d->%d\n",i,f[i]);
    }
    return 0;
}