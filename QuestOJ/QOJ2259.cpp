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

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

int n;
Node p[MAXN];

inline bool cmpx(const Node& a,const Node& b){
	return a.x<b.x;
}

inline bool cmpy(const Node& a,const Node& b){
	return a.y<b.y;
}

inline bool cmpxy(const Node& a,const Node& b){
	return a.x==b.x?a.y<b.y:a.x<b.x;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int x,y;
		x=read(),y=read();
		p[i]=Node(x,y);
	}
	reg ll ans=0;
	sort(p+1,p+n+1,cmpx);
	p[n+1]=Node(inf,inf);
	for(reg int l=1,r;l<=n;l=r+1){
		r=l;
		while(r<=n&&p[r+1].x==p[l].x)
			++r;
		reg int sum=r-l+1;
		ans+=1ll*sum*(sum-1)/2;
	}
	sort(p+1,p+n+1,cmpy);
	p[n+1]=Node(inf,inf);
	for(reg int l=1,r;l<=n;l=r+1){
		r=l;
		while(r<=n&&p[r+1].y==p[l].y)
			++r;
		reg int sum=r-l+1;
		ans+=1ll*sum*(sum-1)/2;
	}
	sort(p+1,p+n+1,cmpxy);
	p[n+1]=Node(inf,inf);
	for(reg int l=1,r;l<=n;l=r+1){
		r=l;
		while(r<=n&&p[r+1].x==p[l].x&&p[r+1].y==p[l].y)
			++r;
		reg int sum=r-l+1;
		ans-=1ll*sum*(sum-1)/2;
	}
	printf("%lld\n",ans);
	return 0;
}