#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
    reg char ch=getchar();
    reg ll res=0;
    while(ch<'0'||'9'<ch)ch=getchar();
    while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
    return res;
}

const double eps=1e-3;

ll n,k;

int main(void){
    n=read(),k=read();
    double delta=(2*n-1)*(2*n-1)-8.0*k;
    if(delta<eps){
        puts("-1");
        return 0;
    }
    delta=sqrt(delta);
    double l=(2*n-1-delta)*0.5,r=(2*n-1+delta)*0.5;
    delta=1*1+8.0*k;
    if(delta<eps){
        puts("-1");
        return 0;
    }
    delta=sqrt(delta);
    l=max(l,(1-delta)/2.0),r=min(r,(1+delta)/2.0);
    l=max(l,0.0),r=min(r,1.0*n);
    ll ans=-1;
    for(reg int i=floor(l);i<=ceil(r);++i){
        if(1ll*i*(i-1)/2+1ll*i*(n-i)>=k&&k>=1ll*i*(i-1)/2+1ll*i*0)
            ans=max(ans,1ll*i*(i-1)/2+(n-1ll*i)*(n-1ll*i-1)/2);
    }
    printf("%lld\n",ans);
    return 0;
}