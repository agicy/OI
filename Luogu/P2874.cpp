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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e4+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

int n;
int x[MAXN],y[MAXN];
Node p[MAXN];
ll ans1=inf,ans2;

inline void getVal(reg int px,reg int py){
	reg ll sum=0;
	for(reg int i=1;i<=n;++i)
		sum+=abs(x[i]-px)+abs(y[i]-py);
	if(ans1>sum)
		ans1=sum,ans2=1;
	else if(ans1==sum)
		++ans2;
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		x[i]=read(),y[i]=read();
		p[i]=Node(x[i],y[i]);
	}
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	if(n&1){
		int px=x[(n+1)>>1],py=y[(n+1)>>1];
		getVal(px-1,py);
		getVal(px,py-1);
		getVal(px+1,py);
		getVal(px,py+1);
	}
	else{
		reg int px1=x[(n>>1)],px2=x[(n>>1)+1];
		reg int py1=y[(n>>1)],py2=y[(n>>1)+1];
		getVal(px1,py1);
		ans2=1ll*(px2-px1+1)*(py2-py1+1);
		for(reg int i=1;i<=n;++i)
			if(px1<=p[i].x&&p[i].x<=px2&&py1<=p[i].y&&p[i].y<=py2)
				--ans2;
	}
	printf("%lld %lld\n",ans1,ans2);
	return 0;
}