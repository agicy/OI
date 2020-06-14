#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

double n,m;

int main(void){
    while(scanf("%lf%lf",&n,&m)!=EOF){
        reg double ans=0,pos;
        for(reg double i=1;i<n;i+=1){
            pos=i/n*(n+m);
            ans+=fabs(pos-floor(pos+0.5))/(n+m);
        }
        printf("%.4f\n",ans*1e4);
    }
    return 0;
}