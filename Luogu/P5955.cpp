#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=200000+5;
const double pi=acos(-1.0);

struct Node{
	int x,y;
	double angle;
	inline void Read(void){
		x=read(),y=read();
		angle=atan2(y,x);
		return;
	}
	inline bool operator<(const Node& a)const{
		return angle<a.angle;
	}
};

int n;
Node V[MAXN<<1];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		V[i].Read();
	sort(V+1,V+n+1);
	for(reg int i=1;i<=n;++i)
		V[n+i]=V[i],V[n+i].angle=V[i].angle+2*pi;
	reg int sumx=0,sumy=0;
	ll ans=0;
	for(reg int l=1,r=1;l<=n;++l){
		while(r<n+l&&V[r].angle-V[l].angle<pi){
			sumx+=V[r].x,sumy+=V[r].y;
			ans=max(ans,1ll*sumx*sumx+1ll*sumy*sumy);
			++r;
		}
		sumx-=V[l].x,sumy-=V[l].y;
		ans=max(ans,1ll*sumx*sumx+1ll*sumy*sumy);
	}
	printf("%lld\n",ans);
	return 0;
}
