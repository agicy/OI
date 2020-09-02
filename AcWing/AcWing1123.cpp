#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline double sqr(reg double x){
    return x*x;
}

int main(void){
    int x0,y0;
    scanf("%d%d",&x0,&y0);
    int x1,y1,x2,y2;
    reg double sum=0;
    while(scanf("%d%d%d%d",&x1,&y1,&x2,&y2)!=EOF)
        sum+=sqrt(sqr(x1-x2)+sqr(y1-y2));
    reg double ans=sum/10000.0;
    reg ll h=ans;
    printf("%lld:%02.0lf\n",h,(ans-h)*60.0);
    return 0;
}
