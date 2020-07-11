#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

const int MAXN=40000+5;
const int MAXM=40000+5;
const int MAXR=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Edge{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
	}
	inline bool operator<(const Edge& a)const{
		return x==a.x?y<a.y:x<a.x;
	}
	inline bool operator==(const Edge& a)const{
		return x==a.x&&y==a.y;
	}
};

int n,m,R;
int l[MAXN],r[MAXM];
Edge E[MAXR];

inline void Read(void){
	n=read(),m=read(),R=read();
	for(reg int i=1;i<=n;++i)
		l[i]=read();
	for(reg int i=1;i<=m;++i)
		r[i]=read();
	for(reg int i=1;i<=R;++i)
		E[i].Read();
	return;
}

int dp[2][MAXN];

inline void Work(void){
	int ans=-INF;
	sort(E+1,E+R+1);
	reg int len=unique(E+1,E+R+1)-(E+1);
	dp[0][E[1].x]=l[E[1].x]+r[E[1].y];
	dp[1][E[1].y]=dp[0][E[1].x];
	for(reg int i=2;i<=len;++i){
		reg int p=dp[0][E[i].x];
		reg int q=dp[1][E[i].y];
		if(p==0)
			dp[1][E[i].y]=max(dp[1][E[i].y],l[E[i].x]+r[E[i].y]);
		else
			dp[1][E[i].y]=max(dp[1][E[i].y],p+r[E[i].y]);
		if(q==0)
			dp[0][E[i].x]=max(dp[0][E[i].x],l[E[i].x]+r[E[i].y]);
		else
			dp[0][E[i].x]=max(dp[0][E[i].x],q+l[E[i].x]);
	}
	for(reg int i=1;i<=n;++i)
		ans=max(ans,dp[0][i]);
	for(reg int i=1;i<=m;++i)
		ans=max(ans,dp[1][i]);
	for(reg int i=1;i<=n;++i)
		ans=max(ans,l[i]);
	for(reg int i=1;i<=m;++i)
		ans=max(ans,r[i]);
	printf("%d\n",ans);
	return;
}
