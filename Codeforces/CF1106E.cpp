#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int MAXM=200+5;
const int MAXK=100000+5;

struct RedBag{
	int s,t,d,w;
	inline void Read(void){
		s=read(),t=read(),d=read(),w=read();
		return;
	}
	inline bool operator>(const RedBag& a)const{
		return w==a.w?d>a.d:w>a.w;
	}
	inline bool operator<(const RedBag& a)const{
		return w==a.w?d<a.d:w<a.w;
	}
};

inline bool cmp(const RedBag& a,const RedBag& b){
	return a.s<b.s;
}

int n,m,K;
RedBag R[MAXK];
int g[MAXN],h[MAXN];
ll f[MAXN][MAXM];
priority_queue<RedBag,vector<RedBag>,less<RedBag>/**/> Q;

int main(void){
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=K;++i)
		R[i].Read();
	sort(R+1,R+K+1,cmp);
	reg int ptr=1;
	for(reg int i=1;i<=n;++i){
		while(R[ptr].s<=i&&ptr<=K)
			Q.push(R[ptr++]);
		while(!Q.empty()&&Q.top().t<i)
			Q.pop();
		if(Q.empty())
			g[i]=i+1,h[i]=0;
		else
			g[i]=Q.top().d+1,h[i]=Q.top().w;
	}
	memset(f,0X3F,sizeof(f));
	g[0]=1,h[0]=0;
	f[0][0]=0;
	for(reg int i=0;i<=n;++i)
		for(reg int j=0;j<=m;++j){
			f[g[i]][j]=min(f[g[i]][j],f[i][j]+h[i]);
			if(j!=m)
				f[i+1][j+1]=min(f[i+1][j+1],f[i][j]);
		}
	ll ans=INF;
	for(reg int i=0;i<=m;++i)
		ans=min(ans,f[n+1][i]);
	printf("%lld\n",ans);
	return 0;
}